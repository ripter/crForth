#ifndef FORTHWORD_H
#define FORTHWORD_H

#include <stdbool.h>

// Define the type for Word Execution Functions
// Due to include order, we can't use KernelState here, so we use void* instead.
// The WordMetadata is provided for convenience since the system already fetched it.
// Real type looks like this:
//  typedef void (*xt_func_ptr)(KernelState *, WordMetadata *wordMeta);
typedef void (*xt_func_ptr)(void *);

// Metadata for a word in the dictionary
typedef struct {
  char* name;           // Name of the word
  xt_func_ptr func;     // Function pointer to run when the word is executed
  bool isImmediate;     // Flag to indicate if the word is immediate
  char* data;           // Data used by the function
  size_t dataBufferLength; // Length of the data buffer
} ForthWord;


ForthWord InitWordMetadata(const char *name, xt_func_ptr func, bool isImmediate, char *data);
void FreeWordMetadata(ForthWord *meta);

void AppendStringToWordData(ForthWord *meta, const char *data);

#endif // FORTHWORD_H
