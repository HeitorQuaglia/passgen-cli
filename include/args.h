#ifndef ARGS_H
#define ARGS_H

#include "profile.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    int length;
    ProfileTitle profile;
    int show_help;
} CmdArgs;

int parse_args(int argc, char *argv[], CmdArgs *args);

#ifdef __cplusplus
}
#endif
#endif // ARGS_H