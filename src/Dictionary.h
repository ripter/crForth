#ifndef DICTIONARY_H
#define DICTIONARY_H

#include "./libs/klib/khash.h"
#include "./crForth.h"


// Create a khash map with string keys and function pointer values
KHASH_MAP_INIT_STR(dict, xt_func_ptr)

// Dictionary type definition
typedef struct {
  khash_t(dict) * map; // Hash map for storing keys and function pointers
  const char *lastKey; // Keep track of the last key added
} Dictionary;

// Function prototypes
void InitDictionary(Dictionary *dict);
void FreeDictionary(Dictionary *dict);
bool AddItemToDictionary(Dictionary *dict, const char *key, xt_func_ptr func);
bool RemoveItemFromDictionary(Dictionary *dict, const char *key);
bool HasItemInDictionary(Dictionary *dict, const char *key);
xt_func_ptr GetItemFromDictionary(Dictionary *dict, const char *key);
bool SetItemInDictionary(Dictionary *dict, const char *key, xt_func_ptr func);
void GetKeysInDictionary(Dictionary *dict);
xt_func_ptr GetLastItemFromDictionary(Dictionary *dict);

#endif // DICTIONARY_H
