#include <string.h>
#include "raylib.h"

#include "crForth.h"
#include "WordMetadata.h"


WordMetadata* InitWordMeta(xt_func_ptr func, bool isImmediate, const char *data) {
    WordMetadata *meta = MemAlloc(sizeof(WordMetadata)); // Allocate memory for the struct
    if (!meta) return NULL; // Handle allocation failure
    
    meta->func = func;
    meta->isImmediate = isImmediate;

    // Duplicate the 'data' string to ensure it's safely copied
    if (data) {
        meta->data = strdup(data);
        if (!meta->data) {
            MemFree(meta); // Clean up if string allocation fails
            return NULL;
        }
    } else {
        meta->data = NULL;
    }

    return meta;
}

void FreeWordMeta(WordMetadata *meta) {
    if (meta) {
        if (meta->data) {
            MemFree(meta->data); // Free the dynamically allocated string
        }
        MemFree(meta); // Free the struct itself
    }
}

