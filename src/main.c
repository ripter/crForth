#include <stdio.h>
#include "raylib.h"

#include "crForth.h"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void) { 
  char* nextWord = GetNext();
  printf("%s", nextWord);
  return 0; 
}
