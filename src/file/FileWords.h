#ifndef FILEWORDS_H
#define FILEWORDS_H
//
// C implementations of the FILE words.
// https://forth-standard.org/standard/file

#include "../crForth.h"

// Adds all of the file words to the dictionary.
void AddFileWords(KernelState *state);

// ( addr u -- )
void Included(KernelState *state);



#endif // FILEWORDS_H
