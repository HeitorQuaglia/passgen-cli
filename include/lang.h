#ifndef LANG_H
#define LANG_H

#include "strings.h" // For Language enum

#ifdef __cplusplus
extern "C" {
#endif

// Global variable to store the current language
extern Language current_lang;

// Function to initialize the language settings
void initialize_language(void);

// Function to get the current language
Language get_current_language(void);

#ifdef __cplusplus
}
#endif

#endif // LANG_H
