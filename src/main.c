#include <stdio.h>
#include <stdlib.h>
#include "args.h"
#include "profile.h"
#include "generator.h"
#include "lang.h"

int main(int argc, char *argv[]) {
    initialize_language();
    CmdArgs args;
    int res = parse_args(argc, argv, &args);

    if (res == SHOW_HELP) {
        if (!args.quiet) print_usage();
        return 0;
    }
    if (res == -1) {
        if (!args.quiet) print_usage();
        return 1;
    }

    Profile custom_profile;
    const Profile *profile = NULL;

    if (args.profile != PROFILE_UNSET) {
        profile = get_default_profile(args.profile);
    } else {
        custom_profile.uppercase    = args.uppercase    == 1 ? 1 : 0;
        custom_profile.lowercase    = args.lowercase    == 1 ? 1 : 0;
        custom_profile.numbers      = args.numbers      == 1 ? 1 : 0;
        custom_profile.symbols      = args.symbols      == 1 ? 1 : 0;
        custom_profile.ambiguity    = args.ambiguity    == 1 ? 1 : 0;
        custom_profile.accentuation = args.accentuation == 1 ? 1 : 0;
        profile = &custom_profile;
    }

    char *password = malloc(args.length + 1);
    if (!password) {
        if (!args.quiet) fprintf(stderr, "Error: Failed to allocate memory.\n");
        return 1;
    }

    if (generate_password(args.length, profile, profile->ambiguity, profile->accentuation, password) == 0) {
        printf("%s\n", password);
    } else {
        if (!args.quiet) fprintf(stderr, "Error: Failed to generate password.\n");
        free(password);
        return 1;
    }

    free(password);
    return 0;
}