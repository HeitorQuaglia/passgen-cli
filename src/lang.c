#include "lang.h"
#include "strings.h"
#include <stdlib.h> // For getenv
#include <string.h> // For strcmp

// Definition of the global variable
Language current_lang = LANG_EN; // Default to English

void initialize_language(void) {
    // Example: Determine language from environment variable
    // This is a simple example; a real application might use locale settings
    const char* lang_env = getenv("LANG");
    if (lang_env != NULL) {
        if (strncmp(lang_env, "pt", 2) == 0) {
            current_lang = LANG_PT;
        }
        // Add more language checks as needed
    }
    // If no specific language is found, it defaults to LANG_EN
}

Language get_current_language(void) {
    return current_lang;
}
