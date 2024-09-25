#ifndef DICTIONARY_H
#define DICTIONARY_H

#include "./libs/klib/khash.h"
#include "./crForth.h"
#include "./WordMetadata.h"


// Create a khash map with string keys and function pointer values
KHASH_MAP_INIT_STR(dict, WordMetadata)

// Dictionary type definition
typedef struct {
  khash_t(dict) * map; // Hash map for storing keys and function pointers
  const char *lastKey; // Keep track of the last key added
} Dictionary;

// Function prototypes
void InitDictionary(Dictionary *dict);
void FreeDictionary(Dictionary *dict);
bool AddItemToDictionary(Dictionary *dict, const char *key, WordMetadata meta);
bool RemoveItemFromDictionary(Dictionary *dict, const char *key);
bool HasItemInDictionary(Dictionary *dict, const char *key);
WordMetadata* GetItemFromDictionary(Dictionary *dict, const char *key);
bool SetItemInDictionary(Dictionary *dict, const char *key, WordMetadata meta);
void GetKeysInDictionary(Dictionary *dict);
WordMetadata* GetLastItemFromDictionary(Dictionary *dict);

#endif // DICTIONARY_H
