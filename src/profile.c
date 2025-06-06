#include "profile.h"
#include <string.h>
#include <stddef.h>

const Profile DEFAULT_PROFILES[] = {
    // structure:
    // uppercase, lowercase, numbers, symbols, ambiguity, accentuation

    // PROFILE_EASY_TO_READ
    {1, 1, 1, 0, 0, 0}, 
    // PROFILE_EASY_TO_SPEAK
    {1, 1, 0, 0, 0, 0},
    // PROFILE_HARD
    {1, 1, 1, 1, 1, 0}

};

const Profile* get_default_profile(ProfileTitle title) {
    if (title >= PROFILE_EASY_TO_READ && title <= PROFILE_HARD) {
        return &DEFAULT_PROFILES[title];
    }
    return NULL; // inválido
}

ProfileTitle parse_profile_title(const char *title) {
    if (strcmp(title, "easy-to-read") == 0) {
        return PROFILE_EASY_TO_READ;
    } else if (strcmp(title, "easy-to-speak") == 0) {
        return PROFILE_EASY_TO_SPEAK;
    } else if (strcmp(title, "hard") == 0) {
        return PROFILE_HARD;
    }
    return -1; // inválido
}