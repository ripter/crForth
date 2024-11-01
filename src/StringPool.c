#include "StringPool.h"

String *stringPool[STRING_POOL_SIZE];
size_t poolIndex = 0;

// Gets a string from the pool with the given value.
String *GetStringFromPool(const char *value) {
  String *str = stringPool[poolIndex];
  if (!str) {
    // If no string exists in the pool at this position, create a new one
    str = CreateString(value);
    stringPool[poolIndex] = str;
  } else {
    // Clear the existing string
    str->l = 0; // Reset the length to 0 to indicate an empty string
    if (str->s) {
      str->s[0] = '\0'; // Ensure the buffer starts fresh
    }
    kputs(value, str); // Add the new value
  }
  // Move to the next pool slot in a circular manner
  poolIndex = (poolIndex + 1) % STRING_POOL_SIZE;
  return str;
}
