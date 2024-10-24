#include <string.h>
#include "raylib.h"

#include "minunit.h"
#include "Test.h"
#include "../src/crForth.h"
#include "../src/core/CoreWords.h"


MU_TEST(non_existent_word_lookup) {
  KernelState state = {0};
  InitKernelState(&state);
  AddCoreWords(&state);

  // Attempt to fetch a word that doesn't exist in the dictionary
  ForthWord *word = GetItemFromDictionary(&state.dict, "nonexistent");

  // Ensure the word is not found (returns NULL)
  mu_assert(word == NULL, "Non-existent word lookup should return NULL");

  FreeKernelState(&state);
}

MU_TEST(create_add_dictionary_item) {
  KernelState state = {0};
  InitKernelState(&state);
  AddCoreWords(&state);

  OPEN_STREAM("create bizfuz");
  DoForth(&state);
  CLOSE_STREAM();

  mu_assert(HasItemInDictionary(&state.dict, "bizfuz") == true, "Dictionary should have 'bizfuz'");

  FreeKernelState(&state);
}

MU_TEST(create_creates_variable) {
  KernelState state = {0};
  InitKernelState(&state);
  AddCoreWords(&state);

  OPEN_STREAM("create foobar foobar");
  DoForth(&state);
  CLOSE_STREAM();

  // The address to the data buffer should be on the stack.
  Cell result = CellStackPop(&state.dataStack);
  // Find the memory address of the new word.
  ForthWord *newWord = GetItemFromDictionary(&state.dict, "foobar");

  mu_assert_double_eq((cell_t)&newWord->data, result.value);
  FreeKernelState(&state);
}

MU_TEST(create_empty_stack) {
  KernelState state = {0};
  InitKernelState(&state);
  AddCoreWords(&state);

  OPEN_STREAM("create testvar");
  DoForth(&state);
  CLOSE_STREAM();

  // Ensure that the data stack is empty after creating a word
  mu_assert(CellStackSize(&state.dataStack) == 0,
            "Data stack should be empty after CREATE");

  FreeKernelState(&state);
}

MU_TEST(create_multiple_words) {
  KernelState state = {0};
  InitKernelState(&state);
  AddCoreWords(&state);

  OPEN_STREAM("create word1 create word2 create word3");
  DoForth(&state);
  CLOSE_STREAM();

  mu_assert(HasItemInDictionary(&state.dict, "word1") == true,
            "Dictionary should have 'word1'");
  mu_assert(HasItemInDictionary(&state.dict, "word2") == true,
            "Dictionary should have 'word2'");
  mu_assert(HasItemInDictionary(&state.dict, "word3") == true,
            "Dictionary should have 'word3'");

  FreeKernelState(&state);
}

MU_TEST(create_and_does) {
  KernelState state = {0};
  InitKernelState(&state);
  AddCoreWords(&state);

  // Create a new word that pushes 42 to the stack
  // Then run that word to ensure it behaves as expected
  OPEN_STREAM("create doesword does> 10 9 + ; doesword");
  DoForth(&state);
  CLOSE_STREAM();

  // It should push the word "address" to the stack
  // Then it should push the value 42 to the stack
  Cell result = CellStackPop(&state.dataStack);
  Cell addr = CellStackPop(&state.dataStack);
  mu_assert_int_eq(result.value, 19 );
  mu_assert_string_eq("doesword", (char *)addr.value );

  FreeKernelState(&state);
}

//
// Run all the Tests
//
bool TestVariables(void) {

  // MU_RUN_TEST(non_existent_word_lookup);
  // MU_RUN_TEST(create_add_dictionary_item);
  // MU_RUN_TEST(create_creates_variable);
  // MU_RUN_TEST(create_empty_stack);
  // MU_RUN_TEST(create_multiple_words);
  // MU_RUN_TEST(create_and_does);

  MU_REPORT();
  return MU_EXIT_CODE;
}
