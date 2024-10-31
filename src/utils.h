#ifndef UTILS_H
#define UTILS_H

bool IsNullTerminatedString(const char *ptr, int maxLength);
bool ConvertWordToNumber(const char* word, CellValue* numPtr);
bool IsNumber(const char* word);
bool IsWhitespace(char c);

#endif // UTILS_H
