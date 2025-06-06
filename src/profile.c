#include "profile.h"

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
