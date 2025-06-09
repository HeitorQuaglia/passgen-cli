#include <stdlib.h>
#include <stddef.h>
#include <limits.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>

#ifdef __linux__
#include <sys/random.h>
#endif


#define ERROR_OCCURRED -1
#define SUCCESS 0

static void safe_strncat(char *dst, const char *src, size_t max_buf, size_t *current_len) {
    size_t len = strlen(src);
    size_t room = max_buf - *current_len - 1;
    if (room == 0) return;

    if (len > room) len = room;
    strncat(dst, src, len);
    *current_len += len;
    dst[*current_len] = '\0';
}

static size_t calculate_charset_size(const Profile *profile, int use_ambiguous, int use_accented) {
    size_t total_size = 0;
    for (CharsetType t = 0; t < CHARSET_TOTAL; ++t) {
        const CharSet *cs = get_charset(t);
        if (!cs) continue;

        int include = 0;
        switch (t) {
            case CHARSET_UPPERCASE: include = profile->uppercase; break;
            case CHARSET_LOWERCASE: include = profile->lowercase; break;
            case CHARSET_NUMBERS:   include = profile->numbers;   break;
            case CHARSET_SYMBOLS:   include = profile->symbols;   break;
            default: break;
        }

        if (include) {
            if (cs->base && cs->base[0] != '\0')
                total_size += strlen(cs->base);
            if (use_ambiguous && cs->ambiguous && cs->ambiguous[0] != '\0')
                total_size += strlen(cs->ambiguous);
            if (use_accented && cs->accented && cs->accented[0] != '\0')
                total_size += strlen(cs->accented);
        }
    }
    return total_size + 1;
}

static void build_charset(const Profile *profile, int use_ambiguous, int use_accented, char *charset_buf, size_t max_buf) {
    charset_buf[0] = '\0';
    size_t current_len = 0;

    for (CharsetType t = 0; t < CHARSET_TOTAL; ++t) {
        const CharSet *cs = get_charset(t);
        if (!cs) continue;

        int include = 0;
        switch (t) {
            case CHARSET_UPPERCASE: include = profile->uppercase; break;
            case CHARSET_LOWERCASE: include = profile->lowercase; break;
            case CHARSET_NUMBERS:   include = profile->numbers;   break;
            case CHARSET_SYMBOLS:   include = profile->symbols;   break;
            default: break;
        }
        if (include) {
            if (cs->base && cs->base[0] != '\0')
                safe_strncat(charset_buf, cs->base, max_buf, &current_len);
            if (use_ambiguous && cs->ambiguous && cs->ambiguous[0] != '\0')
                safe_strncat(charset_buf, cs->ambiguous, max_buf, &current_len);
            if (use_accented && cs->accented && cs->accented[0] != '\0')
                safe_strncat(charset_buf, cs->accented, max_buf, &current_len);
        }
        if (current_len + 1 >= max_buf) break;
    }
}

static int fill_random_bytes(unsigned char *buf, size_t n) {
#ifdef __linux__
    size_t total = 0;
    while (total < n) {
        ssize_t res = getrandom(buf + total, n - total, 0);
        if (res < 0) {
            if (errno == EINTR) continue;
            break;
        }
        total += res;
    }
    if (total == n) return SUCCESS;
#endif
    int fd = open("/dev/urandom", O_RDONLY);
    if (fd < 0) return ERROR_OCCURRED;
    size_t total = 0;
    while (total < n) {
        ssize_t rd = read(fd, buf + total, n - total);
        if (rd <= 0) {
            close(fd);
            return ERROR_OCCURRED;
        }
        total += rd;
    }
    close(fd);
    return SUCCESS;
}

int generate_password(int length, const Profile *profile, int use_ambiguous, int use_accented, char *out) {
    if (length <= 0 || !out || !profile) return ERROR_OCCURRED;

    size_t buf_size = calculate_charset_size(profile, use_ambiguous, use_accented);
    if (buf_size <= 1) return ERROR_OCCURRED;

    char *charset = malloc(buf_size);
    if (!charset) return ERROR_OCCURRED;

    build_charset(profile, use_ambiguous, use_accented, charset, buf_size);
    size_t charset_len = strlen(charset);
    if (charset_len == 0) {
        free(charset);
        return ERROR_OCCURRED;
    }

    size_t range = (size_t)UCHAR_MAX + 1;                 
    size_t limit = range - (range % charset_len);         

    for (int i = 0; i < length; ++i) {
        unsigned char byte;
        do {
            if (fill_random_bytes(&byte, 1) != 0) {
                free(charset);
                return ERROR_OCCURRED;
            }
        } while ((size_t)byte >= limit);

        out[i] = charset[byte % charset_len];
    }
    out[length] = '\0';

    free(charset);
    return SUCCESS;
}