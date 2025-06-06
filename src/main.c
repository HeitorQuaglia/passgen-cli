#include <stdio.h>
#include <string.h>

void print_usage() {
    printf("Uso: passgen-cli [OPÇÕES]\n");
    printf("  --help      Mostra esta mensagem de ajuda\n");
    printf("\n");
    printf("Em breve: geração de senha, seleção de perfil, etc.\n");
}

int main(int argc, char *argv[]) {
    if (argc == 2 && (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0)) {
        print_usage();
        return 0;
    }

    printf("passgen-cli: gerador de senhas em C\n");
    printf("Use --help para mais informações.\n");
    return 0;
}
