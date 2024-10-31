#ifndef DICTIONARY_H
#define DICTIONARY_H

#include "./libs/klib/khash.h"
#include "ForthWord.h"

#define SCRATCH_BUFFER_NAME  "__scratch_buffer__"

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
bool AddWordToDictionary(Dictionary *dict, ForthWord wordMeta);
bool HasItemInDictionary(Dictionary *dict, const char *key);
bool RemoveItemFromDictionary(Dictionary *dict, const char *key);
bool RenameItemInDictionary(Dictionary *dict, const char *oldKey, const char *newKey);
bool SetItemInDictionary(Dictionary *dict, const char *key, ForthWord meta);
ForthWord* GetItemFromDictionary(Dictionary *dict, const char *key);
ForthWord* GetLastItemFromDictionary(Dictionary *dict);
void GetKeysInDictionary(Dictionary *dict);


#endif // DICTIONARY_H
