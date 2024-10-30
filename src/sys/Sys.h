#ifndef SYS_H
#define SYS_H

#include "../Stack.h"
#include "../String.h"

//
// DoSys
// A struct to hold the loop control parameters.
typedef struct {
  cell_t limit;    // The limit of the loop, the loop will run until the index is equal to or greater than the limit.
  cell_t index;    // The current index of the loop.
  bool isNested;   // True if this is a nested loop.
  String *loopSrc; // The source code for the loop body.
} DoSys;

DoSys *CreateDoSys(void);



typedef struct {
  cell_t flag;
} IfSys;


#endif // SYS_H
