#ifndef CHARSET_H
#define CHARSET_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    const char *base;
    const char *ambiguous;
    const char *accented;
} CharSet;

typedef enum {
    CHARSET_UPPERCASE,
    CHARSET_LOWERCASE,
    CHARSET_NUMBERS,
    CHARSET_SYMBOLS,
    CHARSET_TOTAL
} CharsetType;

#ifdef __cplusplus
}
#endif

#endif // CHARSET_H
