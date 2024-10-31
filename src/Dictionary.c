#include <stdio.h>
#include <string.h>

#include "raylib.h"
#include "./libs/klib/khash.h"

#include "Dictionary.h"
#include "crForth.h"
// #include "core/CoreWords.h"



void InitDictionary(Dictionary *dict) {
  dict->map = kh_init(dict); // Initialize the khash dictionary
  // Add a scratch buffer to the dictionary
  // ForthWord scratch = CreateForthWord(SCRATCH_BUFFER_NAME, (xt_func_ptr)Variable, false, NULL);
  // AddWordToDictionary(dict, scratch); 
}

void FreeDictionary(Dictionary *dict) {
  if (dict->map) {
    khint_t k;
    for (k = kh_begin(dict->map); k != kh_end(dict->map); ++k) {
      if (kh_exist(dict->map, k)) {
        ForthWord *metadata = &kh_value(dict->map, k);
        FreeForthWord(metadata);   // Free the ForthWord
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
    FreeForthWord(meta);         // Free the ForthWord using the helper function
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

// Set a new ForthWord for an existing key
bool SetItemInDictionary(Dictionary *dict, const char *key, ForthWord wordMeta) {
  khint_t k = kh_get(dict, dict->map, key); // Find key
  if (k != kh_end(dict->map)) {
    ForthWord *old_meta = &kh_value(dict->map, k);
    FreeForthWord(old_meta); // Free the old value

    kh_value(dict->map, k) = wordMeta; // Store the new value
    return true;                       // Success
  }
  return false; // Key not found
}

// Rename a key in the dictionary
bool RenameItemInDictionary(Dictionary *dict, const char *oldKey, const char *newKey) {
  int ret;
  khiter_t k;

  // Check if the old key exists
  k = kh_get(dict, dict->map, oldKey);
  if (k == kh_end(dict->map)) {
    return false; // Old key not found
  }

  // Get the value associated with the old key
  ForthWord value = kh_value(dict->map, k);
  // Create a new value with the updated internal name
  ForthWord newValue = CreateForthWord(newKey, value.func, value.isImmediate, GetStringValue(value.data));

  // Add the new key with the value
  k = kh_put(dict, dict->map, newKey, &ret);
  if (ret == -1) {
    return false; // Failed to insert new key
  }
  kh_value(dict->map, k) = newValue;

  // Remove the old key
  k = kh_get(dict, dict->map, oldKey);
  kh_del(dict, dict->map, k);

  return true; // Rename was successful
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

// Returns the last item added to the dictionary
ForthWord* GetLastItemFromDictionary(Dictionary *dict) {
  if (dict->lastKey != NULL) {
    return GetItemFromDictionary(dict, dict->lastKey);
  }
  return NULL; // No last item exists
}

