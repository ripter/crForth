#include <stdio.h>
#include <string.h>

#include "raylib.h"
#include "./libs/klib/khash.h"

#include "Dictionary.h"
#include "crForth.h"


void InitDictionary(Dictionary *dict) {
  dict->map = kh_init(dict); // Initialize the khash dictionary
}

void FreeDictionary(Dictionary *dict) {
  if (dict->map) {
    kh_destroy(dict, dict->map); // Destroy the khash map
  }
}

// Add a new key-function pair to the dictionary
bool AddItem(Dictionary *dict, const char *key, xt_func_ptr func) {
  int ret;
  khint_t k = kh_put(dict, dict->map, key, &ret); // Insert key
  if (ret == -1)
    return 0;                    // Insertion failed
  kh_value(dict->map, k) = func; // Set the function pointer as the value
  return true;                   // Success
}

// Remove an item from the dictionary
bool RemoveItem(Dictionary *dict, const char *key) {
  khint_t k = kh_get(dict, dict->map, key); // Find key
  if (k != kh_end(dict->map)) {
    kh_del(dict, dict->map, k); // Remove the key-value pair
    return true;                // Success
  }
  return false; // Key not found
}

// Check if a key exists in the dictionary
bool HasItem(Dictionary *dict, const char *key) {
  khint_t k = kh_get(dict, dict->map, key); // Find key
  return k != kh_end(dict->map);
}

// Get a function pointer associated with a key
xt_func_ptr GetItem(Dictionary *dict, const char *key) {
  khint_t k = kh_get(dict, dict->map, key); // Find key
  if (k != kh_end(dict->map)) {
    return kh_value(dict->map, k); // Return the function pointer
  }
  return NULL; // Key not found
}

// Set a new function pointer for an existing key
bool SetItem(Dictionary *dict, const char *key, xt_func_ptr func) {
  khint_t k = kh_get(dict, dict->map, key); // Find key
  if (k != kh_end(dict->map)) {
    kh_value(dict->map, k) = func; // Set new function pointer
    return true;                      // Success
  }
  return false; // Key not found
}

// Print all the keys in the dictionary
void GetKeys(Dictionary *dict) {
  khint_t k;
  for (k = kh_begin(dict->map); k != kh_end(dict->map); ++k) {
    if (kh_exist(dict->map, k)) {
      printf("Key: %s\n", kh_key(dict->map, k));
    }
  }
}
