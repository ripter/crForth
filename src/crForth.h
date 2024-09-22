#ifndef CRFORTH_H
#define CRFORTH_H

#define APP_VERSION "0.0.1-dev"

#define MAX_WORD_LENGTH 256 // This does NOT include space for the null terminator.


// typedef struct {
//   Dictionary *dict;
//   void *dataStack;
//   void *returnSack;
// } ThreadState;

char* GetNext(FILE* input);
bool IsWhitespace(char c);

#endif // CRFORTH_H
