#ifndef WORDMETADATA_H
#define WORDMETADATA_H

#include <stdbool.h>
#include "./crForth.h"

// Metadata for a word in the dictionary
//  - func: The function pointer to run when the word is executed.
//  - isImmediate: A flag to indicate if the word is immediate.
//  - data: string of data used by the func. Used to hold "compiled" code.
typedef struct {
  xt_func_ptr func;
  bool isImmediate;
  char* data;
} WordMetadata;

WordMetadata* InitWordMeta(xt_func_ptr func, bool isImmediate, const char *data);
void FreeWordMeta(WordMetadata *meta);

#endif // WORDMETADATA_H
