#include "generator.h"
#include <stdlib.h>
#include <time.h>
#include <stddef.h>
#include <string.h>

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

int generate_password(int length, const Profile *profile, int use_ambiguous, int use_accented, char *out) {
    if (length <= 0 || !out || !profile) return ERROR_OCCURRED;

    size_t charset_buffer_size = calculate_charset_size(profile, use_ambiguous, use_accented);
    if (charset_buffer_size <= 1) return ERROR_OCCURRED;

    char *charset = (char *)malloc(charset_buffer_size);
    if (!charset) return ERROR_OCCURRED;

    build_charset(profile, use_ambiguous, use_accented, charset, charset_buffer_size);

    size_t charset_len = strlen(charset);
    if (charset_len == 0) {
        free(charset);
        return ERROR_OCCURRED;
    }

    srand((unsigned int)time(NULL));

    for (int i = 0; i < length; ++i) {
        out[i] = charset[rand() % charset_len];
    }
    out[length] = '\0';

    free(charset);
    return SUCCESS;
}