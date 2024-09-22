#ifndef CRFORTH_H
#define CRFORTH_H

#define MAX_WORD_LENGTH 100 // This does NOT include space for the null terminator.

char* GetNext(FILE* input);
bool IsWhitespace(char c);

#endif // CRFORTH_H
