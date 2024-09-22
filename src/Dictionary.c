#include <stdio.h>
#include <string.h>
#include "raylib.h"
#include "./libs/klib/khash.h"

#include "crForth.h"
#include "Dictionary.h"


// Create a new dictionary of string -> function pointers
Dictionary* CreateDictionary(void) {
    Dictionary* dict = (Dictionary*)MemAlloc(sizeof(Dictionary));
    dict->map = kh_init(dict);  // Initialize the khash dictionary
    return dict;
}

// Free the dictionary (using Raylib's MemFree)
void FreeDictionary(Dictionary* dict) {
    if (dict) {
        kh_destroy(dict, dict->map);  // Destroy the khash map
        MemFree(dict);  // Free the dictionary memory
    }
}

// Add a new key-function pair to the dictionary
int AddItem(Dictionary* dict, const char* key, xt_func_ptr func) {
    int ret;
    khint_t k = kh_put(dict, dict->map, key, &ret);  // Insert key
    if (ret == -1) return 0;  // Insertion failed
    kh_value(dict->map, k) = func;  // Set the function pointer as the value
    return 1;  // Success
}

// Remove an item from the dictionary
int RemoveItem(Dictionary* dict, const char* key) {
    khint_t k = kh_get(dict, dict->map, key);  // Find key
    if (k != kh_end(dict->map)) {
        kh_del(dict, dict->map, k);  // Remove the key-value pair
        return 1;  // Success
    }
    return 0;  // Key not found
}

// Check if a key exists in the dictionary
int HasItem(Dictionary* dict, const char* key) {
    khint_t k = kh_get(dict, dict->map, key);  // Find key
    return k != kh_end(dict->map);  // Return 1 if found, 0 otherwise
}

// Get a function pointer associated with a key
xt_func_ptr GetItem(Dictionary* dict, const char* key) {
    khint_t k = kh_get(dict, dict->map, key);  // Find key
    if (k != kh_end(dict->map)) {
        return kh_value(dict->map, k);  // Return the function pointer
    }
    return NULL;  // Key not found
}

// Set a new function pointer for an existing key
int SetItem(Dictionary* dict, const char* key, xt_func_ptr func) {
    khint_t k = kh_get(dict, dict->map, key);  // Find key
    if (k != kh_end(dict->map)) {
        kh_value(dict->map, k) = func;  // Set new function pointer
        return 1;  // Success
    }
    return 0;  // Key not found
}

// Print all the keys in the dictionary
void GetKeys(Dictionary* dict) {
    khint_t k;
    for (k = kh_begin(dict->map); k != kh_end(dict->map); ++k) {
        if (kh_exist(dict->map, k)) {
            printf("Key: %s\n", kh_key(dict->map, k));
        }
    }
}

// Test functions for function pointers
void testFunction1(void) {
    printf("Test Function 1 executed!\n");
}

void testFunction2(void) {
    printf("Test Function 2 executed!\n");
}

/*
// Main function to demonstrate the usage of the dictionary
int main(void) {
    // Create a new dictionary
    Dictionary* dict = NewDictionary();

    // Add items to the dictionary
    AddItem(dict, "func1", testFunction1);
    AddItem(dict, "func2", testFunction2);

    // Check if a key exists
    if (HasItem(dict, "func1")) {
        printf("func1 exists in the dictionary.\n");
    }

    // Get and call a function from the dictionary
    xt_func_ptr func = GetItem(dict, "func1");
    if (func) func();  // Calls testFunction1

    // Print all the keys in the dictionary
    GetKeys(dict);

    // Set a new function for an existing key
    SetItem(dict, "func1", testFunction2);

    // Get and call the updated function from the dictionary
    func = GetItem(dict, "func1");
    if (func) func();  // Calls testFunction2

    // Remove an item from the dictionary
    RemoveItem(dict, "func2");

    // Free the dictionary
    FreeDictionary(dict);

    return 0;
}
*/

