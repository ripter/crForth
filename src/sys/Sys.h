#ifndef SYS_H
#define SYS_H

#include "../Stack.h"
#include "../String.h"

//
// Colon-Sys
// A struct for definitions.
typedef struct {
  String *name; // The name of the definition.
  String *src;  // The source code for the definition.
  FILE *stream; // The stream for the definition.
} ColonSys;

// Function to create a ColonSys, src is not owned by the ColonSys.
ColonSys *CreateColonSys(const char* newName, String *src);
// Function to free the ColonSys, does not free the src string.
void FreeColonSys(ColonSys *colonSys);


//
// NestSys
typedef struct {
  String *src; // The source code for the nest.
} NestSys;


//
// Do-Sys
// A struct to hold the loop control parameters.
typedef struct {
  CellValue limit; // The limit of the loop, the loop will run until the index is equal to or greater than the limit.
  CellValue index; // The current index of the loop.
  bool isNested;   // True if this is a nested loop.
  String *src;     // The source code for the loop body. When the loop runs, this code will be executed.
  FILE *stream;    // The stream for the definition.
} DoSys;

DoSys *CreateDoSys(void);
void FreeDoSys(DoSys *doSys);



//
// OrigSys
// A struct used by words like IF, ELSE, REPEAT, WHILE, etc.
typedef struct {
  bool flag;
  bool isNested;
  String *src;    // Source code as a Forth String
  FILE *stream;   // The stream for the definition.
} OrigSys;

OrigSys *CreateOrigSys(void);
void FreeOrigSys(OrigSys *origSys);


#endif // SYS_H
