#ifndef STRINGS_H
#define STRINGS_H

typedef enum {
    STR_BANNER,
    STR_ERROR_ALLOC,
    STR_ERROR_GENERATE,
    STR_ERROR_INVALID_PROFILE,
    STR_ERROR_DUPLICATE_FLAGS,
    STR_ERROR_NO_PROFILE_OR_FLAGS,
    STR_USAGE,
    STR_ERROR_ARGS_MISSING_VALUE_FOR_ARG,
    STR_ERROR_ARGS_PASSWORD_LENGTH,
    STR_ERROR_ARGS_MISSING_PROFILE_VALUE_FOR_ARG,
    STR_ERROR_ARGS_INVALID_PROFILE_VALUE,
    STR__COUNT
} StringKey;

typedef enum {
    LANG_EN,
    LANG_PT
} Language;

// Retorna o texto de acordo com o idioma e a chave
const char* get_string(Language lang, StringKey key);

#endif // STRINGS_H
