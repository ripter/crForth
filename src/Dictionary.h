#ifndef DICTIONARY_H
#define DICTIONARY_H

#include "./libs/klib/khash.h"

// Define the type for the function pointers (void func(void))
typedef void (*func_ptr_t)(void);

// Create a khash map with string keys and function pointer values
KHASH_MAP_INIT_STR(dict, func_ptr_t)

// Dictionary type definition
typedef struct {
  khash_t(dict) * map; // Hash map for storing keys and function pointers
} Dictionary;

// Function prototypes
Dictionary *NewDictionary(void);
void FreeDictionary(Dictionary *dict);
int AddItem(Dictionary *dict, const char *key, func_ptr_t func);
int RemoveItem(Dictionary *dict, const char *key);
int HasItem(Dictionary *dict, const char *key);
func_ptr_t GetItem(Dictionary *dict, const char *key);
int SetItem(Dictionary *dict, const char *key, func_ptr_t func);
void GetKeys(Dictionary *dict);

#endif // DICTIONARY_H
