#include "args.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

// Forward declaration para validação ao final
static int validate(CmdArgs *args);

// === HANDLERS DE FLAG ===

typedef int (*FlagHandler)(int argc, char *argv[], int *i, CmdArgs *args);

typedef struct {
    const char *flag_name;
    FlagHandler handler;
} FlagEntry;

// Handler para --help / -h
int handle_help(int argc, char *argv[], int *i, CmdArgs *args) {
    (void)argc; (void)argv; (void)i;
    args->show_help = 1;
    return 1;
}

int handle_length(int argc, char *argv[], int *i, CmdArgs *args) {
    if (*i + 1 >= argc) {
        fprintf(stderr, "Error: Missing value for %s\n", argv[*i]);
        return -1;
    }
    int val = atoi(argv[*i + 1]);
    if (val < 8 || val > 50) {
        fprintf(stderr, "Error: Password length must be between 8 and 50.\n");
        return -1;
    }
    args->length = val;
    *i += 1;
    return 1;
}

int handle_profile(int argc, char *argv[], int *i, CmdArgs *args) {
    if (*i + 1 >= argc) {
        fprintf(stderr, "Error: Missing profile value for %s\n", argv[*i]);
        return -1;
    }
    const char *p = argv[*i + 1];
    if (strcmp(p, "easy-to-read") == 0)
        args->profile = PROFILE_EASY_TO_READ;
    else if (strcmp(p, "easy-to-speak") == 0)
        args->profile = PROFILE_EASY_TO_SPEAK;
    else if (strcmp(p, "hard") == 0)
        args->profile = PROFILE_HARD;
    else {
        fprintf(stderr, "Error: Invalid profile '%s'\n", p);
        return -1;
    }
    *i += 1;
    return 1;
}

#define DEFINE_BOOL_HANDLER(field) \
    int handle_##field(int argc, char *argv[], int *i, CmdArgs *args) { \
        (void)argc; (void)argv; (void)i; \
        args->field = 1; \
        return 1; \
    }

DEFINE_BOOL_HANDLER(uppercase)
DEFINE_BOOL_HANDLER(lowercase)
DEFINE_BOOL_HANDLER(numbers)
DEFINE_BOOL_HANDLER(symbols)
DEFINE_BOOL_HANDLER(ambiguity)
DEFINE_BOOL_HANDLER(accentuation)
DEFINE_BOOL_HANDLER(copy_to_clipboard)
DEFINE_BOOL_HANDLER(quiet)

// =========== TABELA DE FLAGS ===========

static const FlagEntry flag_table[] = {
    { "--help", handle_help },                              { "-h", handle_help },
    { "--length", handle_length },                          { "-l", handle_length },
    { "--profile", handle_profile },                        { "-p", handle_profile },
    { "--uppercase", handle_uppercase },                    { "-u", handle_uppercase },
    { "--lowercase", handle_lowercase },                    { "-lo", handle_lowercase },
    { "--numbers", handle_numbers },                        { "-n", handle_numbers },
    { "--symbols", handle_symbols },                        { "-s", handle_symbols },
    { "--ambiguity", handle_ambiguity },                    { "-a", handle_ambiguity },
    { "--accentuation", handle_accentuation },              { "-ac", handle_accentuation },
    { "--copy-to-clipboard", handle_copy_to_clipboard },    { "-c", handle_copy_to_clipboard },
    { "--quiet", handle_quiet },                            { "-q", handle_quiet },
    { NULL, NULL }
};

// =========== PARSER ===========

int parse_args(int argc, char *argv[], CmdArgs *args) {
    // Defaults: unset ou 0
    args->length = -1;
    args->profile = PROFILE_UNSET;
    args->uppercase = -1;
    args->lowercase = -1;
    args->numbers = -1;
    args->symbols = -1;
    args->ambiguity = -1;
    args->accentuation = -1;
    args->copy_to_clipboard = 0;
    args->show_help = 0;
    args->quiet = 0;

    for (int i = 1; i < argc; ++i) {
        bool matched = false;
        for (const FlagEntry *entry = flag_table; entry->flag_name != NULL; ++entry) {
            if (strcmp(argv[i], entry->flag_name) == 0) {
                int res = entry->handler(argc, argv, &i, args);
                if (res < 0) return -1; // erro no handler
                matched = true;
                break;
            }
        }
        if (!matched) {
            if (!args->quiet) // não imprime nada em quiet mode
                fprintf(stderr, "Error: Unknown argument '%s'\n", argv[i]);
            return -1;
        }
        if (args->show_help) return 1;
    }

    return validate(args);
}

// =========== VALIDAÇÃO FINAL ===========

static int validate(CmdArgs *args) {
    // --length default = 12 se não passado
    if (args->length == -1) args->length = 12;

    int has_manual_flags = 
        (args->uppercase == 1 || args->lowercase == 1 ||
         args->numbers == 1 || args->symbols == 1);

    if (args->profile != PROFILE_UNSET && has_manual_flags) {
        if (!args->quiet)
            fprintf(stderr, "Error: Specify a profile OR manual charset options, not both!\n");
        return -1;
    }
    if (args->profile == PROFILE_UNSET && !has_manual_flags) {
        if (!args->quiet)
            fprintf(stderr, "Error: No profile or charset option specified!\n");
        return -1;
    }
    return 0;
}

// =========== USAGE ===========

void print_usage() {
    printf(
        "Usage: passgen-cli [OPTIONS]\n"
        "  --help, -h                    Show this help message\n"
        "  --length <N>, -l <N>          Set password length (8-50)\n"
        "  --profile <name>, -p <name>   Set profile: easy-to-read | easy-to-speak | hard\n"
        "  --uppercase, -u               Include uppercase letters\n"
        "  --lowercase, -lo              Include lowercase letters\n"
        "  --numbers, -n                 Include numbers\n"
        "  --symbols, -s                 Include symbols\n"
        "  --ambiguity, -a               Include ambiguous chars\n"
        "  --accentuation, -ac           Include accented chars\n"
        "  --copy-to-clipboard, -c       Copy password to clipboard\n"
        "  --quiet, -q                   Quiet mode (no banners, only password)\n"
        "\n"
        "Notes:\n"
        "  - Use a profile OR manual charset flags, not both.\n"
        "  - At least one profile or charset flag must be provided.\n"
    );
}
