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

#ifdef __cplusplus
}
#endif

#endif // CHARSET_H
