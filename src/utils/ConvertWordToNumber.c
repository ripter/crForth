#include <stdlib.h>
#include <errno.h>
#include <inttypes.h>
#include <stdbool.h>

#include "../crForth.h"

// Converts a word to a number, storing the result in numPtr.
// Returns true if the conversion was successful, false otherwise.
bool ConvertWordToNumber(const char* word, cell_t* numPtr) {
    char* endptr;
    errno = 0; // Reset errno before conversion

    // Use strtoll for signed 64-bit integers
    long long int num = strtoll(word, &endptr, 10);

    // Check for conversion errors
    if (errno != 0) {
        // An error occurred during conversion (overflow, underflow, etc.)
        return false;
    }

    if (endptr == word) {
        // No digits were found
        return false;
    }

    // Check for any remaining non-numeric characters
    if (*endptr != '\0') {
        return false;
    }

    // Successful conversion
    *numPtr = (cell_t)num;
    return true;
}
