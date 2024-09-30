#ifndef WORDMETADATA_H
#define WORDMETADATA_H

#include <stdbool.h>

// Define the type for Word Execution Functions
// typedef void (*xt_func_ptr)(KernelState *, WordMetadata *wordMeta);
typedef void (*xt_func_ptr)(void *, void *);

// Metadata for a word in the dictionary
typedef struct {
  const char* name;     // Name of the word
  xt_func_ptr func;     // Function pointer to run when the word is executed
  bool isImmediate;     // Flag to indicate if the word is immediate
  char* data;           // Data used by the function
  int dataBufferLength; // Length of the data buffer
} WordMetadata;


WordMetadata InitWordMetadata(const char *name, xt_func_ptr func, bool isImmediate, char *data);
void FreeWordMetadata(WordMetadata *meta);

void AppendStringToWordData(WordMetadata *meta, const char *data);

#endif // WORDMETADATA_H
