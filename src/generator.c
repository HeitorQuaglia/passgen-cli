#include "generator.h"
#include <stdlib.h>
#include <time.h>
#include <stddef.h>

int generate_password(int length, char *out) {
    if (length <= 0 || !out) return -1;

    const char *letters = "abcdefghijklmnopqrstuvwxyz";
    int num_letters = 26;

    srand((unsigned int)time(NULL));

    for (int i = 0; i < length; ++i) {
        out[i] = letters[rand() % num_letters];
    }
    out[length] = '\0';
    return 0;
}