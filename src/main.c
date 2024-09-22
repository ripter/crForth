#include <stdio.h>
#include "raylib.h"

#include "crForth.h"
#include "Dictionary.h"
#include "ThreadState.h"
#include "core/CoreWords.h"


//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void) { 
  Dictionary* dict = CreateDictionary();

  // Add the + word to the dictionary
  AddItem(dict, "+", (xt_func_ptr)Add);
  

  printf("crForth %s\n", APP_VERSION);
  char* nextWord = GetNext(stdin);
  printf("%s\n", nextWord);

  FreeDictionary(dict);
  return 0; 
}
