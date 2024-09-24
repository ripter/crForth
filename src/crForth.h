#ifndef CRFORTH_H
#define CRFORTH_H

#include <stdio.h>
#include <stdbool.h>

#define APP_VERSION "0.0.1-dev"

#define MAX_WORD_LENGTH 256 // This does NOT include space for the null terminator.


// Define the type for the cell, the basic data type for the stack.
typedef intptr_t cell_t;

// Define the function pointer type for word execution functions.
// Parameters:
//  - The first parameter is a pointer to the current KernelState, allowing the function to access and modify the system state.
//  - The second parameter is either NULL or a pointer to the word to process, happens when word is called from the return stack.
// Return value:
//  - The return value is ignored unless the word creates a branch, in which case it returns the next word to execute.
// Examples:
//  - A simple word, like "+", will be executed as: `(void)Add(&state, NULL);`
//  - A branching word, like "branch", will be executed as: `word = Branch(&state, word);`
typedef char* (*xt_func_ptr)(void *, char* word);



#endif // CRFORTH_H
