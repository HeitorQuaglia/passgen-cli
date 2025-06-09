#include "strings.h"

static const char* STRINGS_EN[STR__COUNT] = {
    [STR_BANNER] = "passgen-cli: password generator in C",
    [STR_ERROR_ALLOC] = "Error: Failed to allocate memory.",
    [STR_ERROR_GENERATE] = "Error: Failed to generate password.",
    [STR_ERROR_INVALID_PROFILE] = "Error: Invalid profile specified.",
    [STR_ERROR_DUPLICATE_FLAGS] = "Error: Specify a profile OR charset options, not both.",
    [STR_ERROR_NO_PROFILE_OR_FLAGS] = "Error: No profile or charset option specified.",
    [STR_USAGE] =
        "Usage: passgen-cli [OPTIONS]\n"
        "  --help, -h               Show this help message\n"
        "  --length <N>, -l <N>     Set password length (8-50)\n"
        "  --profile <name>, -p <name>   Set profile: easy-to-read | easy-to-speak | hard\n"
        "  --uppercase, -u          Include uppercase letters\n"
        "  --lowercase              Include lowercase letters\n"
        "  --numbers, -n            Include numbers\n"
        "  --symbols, -s            Include symbols\n"
        "  --ambiguity, -a          Include ambiguous chars\n"
        "  --accentuation           Include accented chars\n"
        "  --copy-to-clipboard      Copy password to clipboard\n"
        "  --quiet, -q              Quiet mode (no banners, only password)\n"
        "\n"
        "Notes:\n"
        "  - Use a profile OR manual charset flags, not both.\n"
        "  - At least one profile or charset flag must be provided.\n",
    // New keys for args.c
    [STR_ERROR_ARGS_MISSING_VALUE_FOR_ARG] = "Error: Missing value for %s\n",
    [STR_ERROR_ARGS_PASSWORD_LENGTH] = "Error: Password length must be between 8 and 50.\n",
    [STR_ERROR_ARGS_MISSING_PROFILE_VALUE_FOR_ARG] = "Error: Missing profile value for %s\n",
    [STR_ERROR_ARGS_INVALID_PROFILE_VALUE] = "Error: Invalid profile '%s'\n",
};

static const char* STRINGS_PT[STR__COUNT] = {
    [STR_BANNER] = "passgen-cli: gerador de senhas em C",
    [STR_ERROR_ALLOC] = "Erro: Falha ao alocar memória.",
    [STR_ERROR_GENERATE] = "Erro: Falha ao gerar senha.",
    [STR_ERROR_INVALID_PROFILE] = "Erro: Perfil inválido.",
    [STR_ERROR_DUPLICATE_FLAGS] = "Erro: Informe um perfil OU opções de charset, não ambos.",
    [STR_ERROR_NO_PROFILE_OR_FLAGS] = "Erro: Nenhum perfil ou opção de charset especificada.",
    [STR_USAGE] =
        "Uso: passgen-cli [OPÇÕES]\n"
        "  --help, -h               Mostra esta mensagem de ajuda\n"
        "  --length <N>, -l <N>     Define o comprimento da senha (8-50)\n"
        "  --profile <nome>, -p <nome>   Define o perfil: easy-to-read | easy-to-speak | hard\n"
        "  --uppercase, -u          Incluir letras maiúsculas\n"
        "  --lowercase              Incluir letras minúsculas\n"
        "  --numbers, -n            Incluir números\n"
        "  --symbols, -s            Incluir símbolos\n"
        "  --ambiguity, -a          Incluir caracteres ambíguos\n"
        "  --accentuation           Incluir acentuação\n"
        "  --copy-to-clipboard      Copiar senha para a área de transferência\n"
        "  --quiet, -q              Modo silencioso (só imprime a senha)\n"
        "\n"
        "Notas:\n"
        "  - Use um perfil OU flags manuais de charset, não ambos.\n"
        "  - Pelo menos um perfil ou opção de charset deve ser fornecido.\n",
    // New keys for args.c
    [STR_ERROR_ARGS_MISSING_VALUE_FOR_ARG] = "Erro: Valor ausente para %s\n",
    [STR_ERROR_ARGS_PASSWORD_LENGTH] = "Erro: O comprimento da senha deve estar entre 8 e 50.\n",
    [STR_ERROR_ARGS_MISSING_PROFILE_VALUE_FOR_ARG] = "Erro: Valor de perfil ausente para %s\n",
    [STR_ERROR_ARGS_INVALID_PROFILE_VALUE] = "Erro: Perfil inválido '%s'\n",
};

const char* get_string(Language lang, StringKey key) {
    if (lang == LANG_PT)
        return STRINGS_PT[key];
    else
        return STRINGS_EN[key];
}
