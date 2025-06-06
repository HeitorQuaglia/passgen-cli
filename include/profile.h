#ifndef PROFILE_H
#define PROFILE_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    PROFILE_UNSET = -1,
    PROFILE_EASY_TO_READ,
    PROFILE_EASY_TO_SPEAK,
    PROFILE_HARD
} ProfileTitle;

typedef struct {
    int uppercase;
    int lowercase;
    int numbers;
    int symbols;
    int ambiguity;
    int accentuation;
} Profile;

const Profile* get_default_profile(ProfileTitle title);

ProfileTitle parse_profile_title(const char *title);

#ifdef __cplusplus
}
#endif

#endif // PROFILE_H
