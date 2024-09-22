#ifndef DICTIONARY_H
#define DICTIONARY_H

#include "./libs/klib/khash.h"

// Define the type for the function pointers (void func(void))
typedef void (*xt_func_ptr)(void *);

// Create a khash map with string keys and function pointer values
KHASH_MAP_INIT_STR(dict, xt_func_ptr)

// Dictionary type definition
typedef struct {
  khash_t(dict) * map; // Hash map for storing keys and function pointers
} Dictionary;

// Function prototypes
Dictionary *CreateDictionary(void);
void FreeDictionary(Dictionary *dict);
int AddItem(Dictionary *dict, const char *key, xt_func_ptr func);
int RemoveItem(Dictionary *dict, const char *key);
int HasItem(Dictionary *dict, const char *key);
xt_func_ptr GetItem(Dictionary *dict, const char *key);
int SetItem(Dictionary *dict, const char *key, xt_func_ptr func);
void GetKeys(Dictionary *dict);

#endif // DICTIONARY_H
