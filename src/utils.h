#ifndef UTILS_H
#define UTILS_H

bool IsNullTerminatedString(const char *ptr, int maxLength);
bool ConvertWordToNumber(const char* word, CellValue* numPtr);
bool IsNumber(const char* word);
bool IsWhitespace(char c);

// Debugging function to print the current position, length, and remaining content of a stream.
void DebugStream(FILE *stream);

#endif // UTILS_H
