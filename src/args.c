#include "args.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int parse_args(int argc, char *argv[], CmdArgs *args) {
    args->length = 0;
    args->profile = PROFILE_EASY_TO_READ; // perfil padrão válido
    args->show_help = 0;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0) {
            args->show_help = 1;
        } else if (strcmp(argv[i], "--length") == 0 || strcmp(argv[i], "-l") == 0) {
            if (i + 1 < argc) {
                args->length = atoi(argv[++i]);
            } else {
                fprintf(stderr, "Error: --length requires a value.\n");
                return -1;
            }
        } else if (strcmp(argv[i], "--profile") == 0 || strcmp(argv[i], "-p") == 0) {
            if (i + 1 < argc) {
                ++i;
                if (strcmp(argv[i], "easy-to-read") == 0) {
                    args->profile = PROFILE_EASY_TO_READ;
                } else if (strcmp(argv[i], "easy-to-speak") == 0) {
                    args->profile = PROFILE_EASY_TO_SPEAK;
                } else if (strcmp(argv[i], "hard") == 0) {
                    args->profile = PROFILE_HARD;
                } else {
                    fprintf(stderr, "Error: Unknown profile '%s'.\n", argv[i]);
                    return -1;
                }
            } else {
                fprintf(stderr, "Error: --profile requires a value.\n");
                return -1;
            }
        } else {
            fprintf(stderr, "Error: Unknown argument '%s'.\n", argv[i]);
            return -1;
        }
    }

    return 0;
}