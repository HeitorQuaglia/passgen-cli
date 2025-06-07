#include "charset.h"
#include <stddef.h>

static const CharSet DEFAULT_CHARSETS[CHARSET_TOTAL] = {
    // CHARSET_UPPERCASE
    { "ABCDEFGHJKLMNPQRSTUVWXYZ", "IO", "ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖØÙÚÛÜÝŸ" },
    // CHARSET_LOWERCASE
    { "abcdefghijkmnpqrstuvwxyz", "lo", "àáâãäåæçèéêëìíîïðñòóôõöøùúûüýÿ" },
    // CHARSET_NUMBERS
    { "23456789", "01", "" },
    // CHARSET_SYMBOLS
    { "!@#$%^&*?;", "`~-_=+[{\\|:,<.>/", "" }
};

const CharSet* get_charset(CharsetType type) {
    if (type >= 0 && type < CHARSET_TOTAL) {
        return &DEFAULT_CHARSETS[type];
    }
    return NULL;
}
