#include <stdio.h>
#include <stdlib.h>
#include "args.h"
#include "profile.h"
#include "generator.h"
#include "lang.h"

int main(int argc, char *argv[]) {
    initialize_language(); // Initialize language at the beginning
    CmdArgs args;
    int res = parse_args(argc, argv, &args);

    // Handle help or error
    if (res == SHOW_HELP) {
        if (!args.quiet) print_usage();
        return 0;
    }
    if (res == -1) {
        if (!args.quiet) print_usage();
        return 1;
    }

    // ===========================
    // Escolha do perfil ou charset manual
    // ===========================

    const Profile *profile = NULL;
    
    if (args.profile != PROFILE_UNSET) {
        profile = get_default_profile(args.profile);
    } else {
        // Montar profile custom com as flags manuais
        Profile custom_profile = {
            .uppercase = args.uppercase == 1 ? 1 : 0,
            .lowercase = args.lowercase == 1 ? 1 : 0,
            .numbers = args.numbers == 1 ? 1 : 0,
            .symbols = args.symbols == 1 ? 1 : 0,
            .ambiguity = args.ambiguity == 1 ? 1 : 0,
            .accentuation = args.accentuation == 1 ? 1 : 0
        };
        profile = &custom_profile;
    }

    // ===========================
    // Gerar senha
    // ===========================
    char *password = malloc(args.length + 1);
    if (!password) {
        if (!args.quiet) fprintf(stderr, "Error: Failed to allocate memory.\n");
        return 1;
    }

    // Por enquanto só exemplo: usando apenas lowercase
    // (Depois: implemente no generator.c o uso do profile)
    if (generate_password(args.length, password) == 0) {
        printf("%s\n", password);
    } else {
        if (!args.quiet) fprintf(stderr, "Error: Failed to generate password.\n");
        free(password);
        return 1;
    }

    free(password);
    return 0;
}