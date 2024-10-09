#include <stdbool.h>
#include <stddef.h>

bool IsNullTerminatedString(const char *ptr, int maxLength) {
    if (ptr == NULL) {
        return false;  // If the pointer itself is NULL, it's not a valid string
    }

    for (int i = 0; i < maxLength; i++) {
        if (ptr[i] == '\0') {
            return true;  // Found null terminator within the given maxLength
        }
    }

    return false;  // No null terminator found within the maxLength
}
