#include "../crForth.h"

// ( "<spaces>name" -- )
// Skip leading space delimiters. Parse name delimited by a space. Append the name to the current definition.
// name is not checked for existence in the dictionary.
// This enables adding any word, even immediate words, to the compile string.
// https://forth-standard.org/standard/core/POSTPONE
void Postpone(KernelState *state) {
  // Consume the next word, which is "name".
  char wordBuffer[MAX_WORD_LENGTH];
  GetNextWord(state->inputStream, wordBuffer, MAX_WORD_LENGTH);

  // Append the word to the current definition.
  wordMeta = GetLastItemFromDictionary(&state->dict);
  AppendStringToWordData(wordMeta, wordBuffer);
}
