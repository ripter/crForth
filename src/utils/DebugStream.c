#include <stdio.h>
#include <stdlib.h>

// Function to debug the stream and print current position, length, and remaining content
void DebugStream(FILE *stream) {
  printf("\n\n********** DebugStream **********\n");

  // Save the current position
  size_t current_pos = ftell(stream);
  if (current_pos == (size_t)-1L) {
    perror("ftell failed");
    return;
  }

  // Move to the end to determine the total length
  if (fseek(stream, 0, SEEK_END) != 0) {
    perror("fseek to end failed");
    return;
  }
  size_t total_length = ftell(stream);
  if (total_length == (size_t)-1L) {
    perror("ftell for total length failed");
    return;
  }

  // Move back to the original position
  if (fseek(stream, 0, SEEK_SET) != 0) {
    perror("fseek to start failed");
    return;
  }

  // Calculate and print current position and total length
  printf("Current position: %ld\n", current_pos);
  printf("Total length: %ld\n\n", total_length);

  // Allocate buffer for the entire content and read it
  char *buffer = malloc(total_length + 1); // +1 for null terminator
  if (!buffer) {
    perror("Memory allocation failed");
    return;
  }

  if (fread(buffer, 1, total_length, stream) != total_length) {
    perror("Error reading entire content");
    free(buffer);
    return;
  }
  buffer[total_length] = '\0'; // Null-terminate the string

  // Print the entire content with a special character marking the current
  // position
  printf("Full stream content with current position marker:\n\n");
  for (size_t i = 0; i < total_length; ++i) {
    if (i == current_pos) {
      printf("^"); // Mark current position
    }
    printf("%c", buffer[i]);
  }
  if (current_pos == total_length) {
    printf("^"); // Mark position if it's at the end of the stream
  }
  printf("\n");

  // Free the buffer
  free(buffer);

  // Restore the original position
  if (fseek(stream, current_pos, SEEK_SET) != 0) {
    perror("fseek to restore position failed");
  }

  printf("\n^^^^^^^^^^ DebugStream ^^^^^^^^^^\n\n");
}
