#ifndef DICTIONARY_H
#define DICTIONARY_H

#include "./libs/klib/khash.h"
#include "./crForth.h"


// Create a khash map with string keys and function pointer values
KHASH_MAP_INIT_STR(dict, xt_func_ptr)

// Dictionary type definition
typedef struct {
  khash_t(dict) * map; // Hash map for storing keys and function pointers
} Dictionary;

// Function prototypes
void InitDictionary(Dictionary *dict);
void FreeDictionary(Dictionary *dict);
bool AddItem(Dictionary *dict, const char *key, xt_func_ptr func);
bool RemoveItem(Dictionary *dict, const char *key);
bool HasItem(Dictionary *dict, const char *key);
xt_func_ptr GetItem(Dictionary *dict, const char *key);
bool SetItem(Dictionary *dict, const char *key, xt_func_ptr func);
void GetKeys(Dictionary *dict);

#endif // DICTIONARY_H
