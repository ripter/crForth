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
    khint_t k;
    for (k = kh_begin(dict->map); k != kh_end(dict->map); ++k) {
      if (kh_exist(dict->map, k)) {
        ForthWord *metadata = &kh_value(dict->map, k);
        FreeWordMetadata(metadata);   // Free the ForthWord
      }
    }
    kh_destroy(dict, dict->map); // Destroy the khash map
  }
}

// Add a new key-ForthWord pair to the dictionary
bool AddWordToDictionary(Dictionary *dict, ForthWord wordMeta) {
  int ret;
  khint_t k = kh_put(dict, dict->map, wordMeta.name, &ret); // Insert key
  if (ret == -1) {
    return false; // Insertion failed
  }

  kh_value(dict->map, k) = wordMeta;  // Store the value
  dict->lastKey = wordMeta.name;      // Track the last added key
  return true;                        // Success
}


// Remove an item from the dictionary
bool RemoveItemFromDictionary(Dictionary *dict, const char *key) {
  khint_t k = kh_get(dict, dict->map, key); // Find key
  if (k != kh_end(dict->map)) {
    ForthWord *meta = &kh_value(dict->map, k);
    FreeWordMetadata(meta);         // Free the ForthWord using the helper function
    kh_del(dict, dict->map, k); // Remove the key-value pair from the map
    return true;                // Success
  }
  return false; // Key not found
}

// Check if a key exists in the dictionary
bool HasItemInDictionary(Dictionary *dict, const char *key) {
  khint_t k = kh_get(dict, dict->map, key); // Find key
  return k != kh_end(dict->map);
}

// Get a function pointer associated with a key
ForthWord* GetItemFromDictionary(Dictionary *dict, const char *key) {
  khint_t k = kh_get(dict, dict->map, key); // Find key
  if (k != kh_end(dict->map)) {
    return &kh_value(dict->map, k); // Return the meta
  }
  return NULL; // Key not found
}

// Set a new WordMetadata for an existing key
bool SetItemInDictionary(Dictionary *dict, const char *key, ForthWord wordMeta) {
  khint_t k = kh_get(dict, dict->map, key); // Find key
  if (k != kh_end(dict->map)) {
    ForthWord *old_meta = &kh_value(dict->map, k);
    FreeWordMetadata(old_meta); // Free the old value

    kh_value(dict->map, k) = wordMeta; // Store the new value
    return true;                       // Success
  }
  return false; // Key not found
}


// Print all the keys in the dictionary
void GetKeysInDictionary(Dictionary *dict) {
  khint_t k;
  for (k = kh_begin(dict->map); k != kh_end(dict->map); ++k) {
    if (kh_exist(dict->map, k)) {
      printf("Key: %s\n", kh_key(dict->map, k));
    }
  }
}

ForthWord* GetLastItemFromDictionary(Dictionary *dict) {
  if (dict->lastKey != NULL) {
    return GetItemFromDictionary(dict, dict->lastKey);
  }
  return NULL; // No last item exists
}
