#include <stdbool.h>
#include <ctype.h>
#include <string.h>

// Returns true if the word is a number
bool IsNumber(const char* word) {
    // Check if the word is empty
    if (word == NULL || *word == '\0') {
        return false;
    }

    // Check if the first character is a sign (+ or -)
    if (*word == '+' || *word == '-') {
        word++;  // Move to the next character
    }

    // Ensure at least one digit after the optional sign
    if (*word == '\0') {
        return false;
    }

    // Check if the rest of the word contains only digits
    while (*word) {
        if (!isdigit((unsigned char)*word)) {
            return false;
        }
        word++;
    }

    return true;
}

