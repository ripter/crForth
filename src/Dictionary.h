#ifndef DICTIONARY_H
#define DICTIONARY_H

#include "./libs/klib/khash.h"
#include "ForthWord.h"

// Create a khash map with string keys and function pointer values
KHASH_MAP_INIT_STR(dict, ForthWord)

// Dictionary type definition
typedef struct {
  khash_t(dict) * map; // Hash map for storing keys and function pointers
  const char *lastKey; // Keep track of the last key added
} Dictionary;

// Function prototypes
void InitDictionary(Dictionary *dict);
void FreeDictionary(Dictionary *dict);
bool AddItemToDictionary(Dictionary *dict, const char *key, ForthWord meta);
bool AddWordToDictionary(Dictionary *dict, ForthWord wordMeta);
bool RemoveItemFromDictionary(Dictionary *dict, const char *key);
bool HasItemInDictionary(Dictionary *dict, const char *key);
ForthWord* GetItemFromDictionary(Dictionary *dict, const char *key);
bool SetItemInDictionary(Dictionary *dict, const char *key, ForthWord meta);
void GetKeysInDictionary(Dictionary *dict);
ForthWord* GetLastItemFromDictionary(Dictionary *dict);

#endif // DICTIONARY_H
