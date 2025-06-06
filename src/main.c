#include "generator.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

void print_usage() {
    printf("Uso: passgen-cli [OPÇÕES]\n");
    printf("  --help           Mostra esta mensagem de ajuda\n");
    printf("  --length <N>     Comprimento da senha (8 a 50)\n");
    printf("\n");
    printf("Exemplo: passgen-cli --length 16\n");
}

int parse_length(int argc, char *argv[]) {
    for (int i = 1; i < argc - 1; ++i) {
        if (strcmp(argv[i], "--length") == 0) {
            // Verifica se o próximo argumento existe e é número
            char *len_str = argv[i + 1];
            for (char *p = len_str; *p; ++p) {
                if (!isdigit(*p)) {
                    printf("Erro: comprimento da senha deve ser um número!\n");
                    exit(1);
                }
            }
            int len = atoi(len_str);
            if (len < 8 || len > 50) {
                printf("Erro: comprimento deve estar entre 8 e 50.\n");
                exit(1);
            }
            return len;
        }
    }
    return 12;
}

int main(int argc, char *argv[]) {
    if (argc == 2 && (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0)) {
        print_usage();
        return 0;
    }

    int length = parse_length(argc, argv);
    printf("Password will be generated with length: %d\n", length);

    char *password = malloc(length + 1);
    if (!password) {
        fprintf(stderr, "Error: Failed to allocate memory.\n");
        return 1;
    }

    if (generate_password(length, password) == 0) {
        printf("Generated password: %s\n", password);
    } else {
        fprintf(stderr, "Error: Failed to generate password.\n");
    }

    free(password);

    return 0;
}
