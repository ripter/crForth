#include <string.h>
#include "raylib.h"

#include "crForth.h"

// Initializes a ForthWord structure
// Name is copied into the structure, so the caller can free the original string. The copy will be freed by FreeWordMetadata.
// isImmediate is a flag to indicate if the word is immediate
// data is an optional string buffer used by the word, can be NULL if not needed. Will be freed by FreeWordMetadata.
ForthWord InitWordMetadata(const char *name, xt_func_ptr func, bool isImmediate, char *data) {
  ForthWord meta;
  // Allocate memory for the name and copy it
  size_t nameLength = TextLength(name) + 1; // +1 for the null terminator
  meta.name = (char *)MemAlloc(nameLength);
  if (meta.name == NULL) {
    // Handle allocation failure
  } else {
    strcpy(meta.name, name);
  }
  meta.func = func;
  meta.isImmediate = isImmediate;
  meta.data = data;
  meta.dataBufferLength = data == NULL ? 0 : TextLength(data);
  return meta;
}

// Free a ForthWord structure
void FreeWordMetadata(ForthWord *meta) {
  if (meta == NULL) {
    return;
  }
  if (meta->data != NULL) {
    MemFree(meta->data);
    meta->data = NULL;
  }
  if (meta->name != NULL) {
    MemFree(meta->name);
    meta->name = NULL;
  }
}

// Append a string to the data buffer of a ForthWord structure
// The data buffer is allocated/expanded as needed to fit the new data.
// meta: The ForthWord to append the data to.
// data: The string to append to the data buffer.
void AppendStringToWordData(ForthWord *meta, const char *data) {
  if (meta->data == NULL) {
    // Allocate initial buffer with size MAX_WORD_LENGTH
    meta->dataBufferLength = MAX_WORD_LENGTH;
    meta->data = (char *)MemAlloc(meta->dataBufferLength);
    if (meta->data == NULL) {
      // Handle allocation failure
      return;
    }
    // Initialize the buffer with an empty string
    meta->data[0] = '\0';
  }

  // Calculate the lengths
  size_t currentLength = TextLength(meta->data);
  size_t dataLength = TextLength(data);
  size_t spaceNeeded = (currentLength > 0) ? 1 : 0; // Space between words if needed
  size_t newLength = currentLength + spaceNeeded + dataLength + 1; // +1 for null terminator

  // Check if we need to expand the buffer
  if (newLength > meta->dataBufferLength) {
    // Expand the buffer by increments of MAX_WORD_LENGTH until it's large enough.
    size_t newBufferSize = meta->dataBufferLength;
    while (newBufferSize < newLength) {
      newBufferSize += MAX_WORD_LENGTH;
    }

    char *newData = (char *)MemRealloc(meta->data, newBufferSize);
    if (newData == NULL) {
      TraceLog(LOG_WARNING, "Failed to reallocate memory for word data");
      return;
    }
    meta->data = newData;
    meta->dataBufferLength = newBufferSize;
  }

  // Append a space if needed
  if (spaceNeeded) {
    strcat(meta->data, " ");
  }

  // Append the new data to the existing data safely
  strcat(meta->data, data);
}
