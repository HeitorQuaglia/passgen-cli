#ifndef ARGS_H
#define ARGS_H

#include "profile.h"

#ifdef __cplusplus
extern "C" {
#endif

static int SHOW_HELP = 1;
static int RESUME_GENERATION = 0;
static int ERROR_OCCURRED = -1;

typedef struct {
    int length;
    ProfileTitle profile;
    int uppercase;
    int lowercase;
    int numbers;
    int symbols;
    int ambiguity;
    int accentuation;
    int copy_to_clipboard;
    int show_help;
    int quiet;
} CmdArgs;

int parse_args(int argc, char *argv[], CmdArgs *args);

void print_usage();

#ifdef __cplusplus
}
#endif
#endif // ARGS_H
