#ifndef GENERATOR_H
#define GENERATOR_H
#include "profile.h"
#include "charset.h"
#ifdef __cplusplus

extern "C" {
#endif

int generate_password(int length, const Profile *profile, int use_ambiguous, int use_accented, char *out);

#ifdef __cplusplus
}
#endif

#endif // GENERATOR_H