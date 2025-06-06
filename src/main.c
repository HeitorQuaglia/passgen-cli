#include "generator.h"
#include "profile.h"
#include "args.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

void print_usage();

int main(int argc, char *argv[]) {
   CmdArgs args;
    int parse_result = parse_args(argc, argv, &args);
    if (parse_result == 1) {
        print_usage();
        return 0;
    }
    if (parse_result == -1) {
        print_usage();
        return 1;
    }

    const Profile *profile = get_default_profile(args.profile);

    printf("Password will be generated with length: %d\n", args.length);
    printf("Selected profile: %s\n",
        args.profile == PROFILE_EASY_TO_READ ? "easy-to-read" :
        args.profile == PROFILE_EASY_TO_SPEAK ? "easy-to-speak" : "hard"
    );
    printf("Profile config - Uppercase: %d, Lowercase: %d, Numbers: %d, Symbols: %d\n",
        profile->uppercase, profile->lowercase, profile->numbers, profile->symbols);

    char *password = malloc(args.length + 1);
    if (!password) {
        fprintf(stderr, "Error: Failed to allocate memory.\n");
        return 1;
    }

    if (generate_password(args.length, password) == 0) {
        printf("Generated password: %s\n", password);
    } else {
        fprintf(stderr, "Error: Failed to generate password.\n");
    }

    free(password);

    return 0;
}

void print_usage() {
    printf("Uso: passgen-cli [OPÇÕES]\n");
    printf("  --help           Mostra esta mensagem de ajuda\n");
    printf("  --length <N>     Comprimento da senha (8 a 50)\n");
    printf("\n");
    printf("Exemplo: passgen-cli --length 16\n");
}