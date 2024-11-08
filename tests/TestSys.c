#include <stdio.h>

#include "minunit.h"
#include "Test.h"

MU_TEST(colon_should_put_colonsys_on_stack) {
  INIT_TEST_STATE();
  // Test creating an empty string
  OPEN_STREAM(": foobar");
  DoForth(&state);
  CLOSE_STREAM();
  // Check the control stack for the ColonSys struct.
  Cell cellResult = CellStackPop(&state.controlStack);
  mu_assert_double_eq(CELL_TYPE_COLON_SYS, cellResult.type);
  // ColonSys should have the newly created word.
  ColonSys *colonSys = (ColonSys *)cellResult.value;
  mu_assert_string_eq("foobar", GetStringValue(colonSys->name));
  FREE_TEST_STATE();
}

MU_TEST(semicolon_should_consume_colonsys) {
  INIT_TEST_STATE();
  OPEN_STREAM(": foobar 10 ;");
  DoForth(&state);
  CLOSE_STREAM();
  mu_assert_double_eq(0, CellStackSize(&state.returnStack));
  FREE_TEST_STATE();
}

MU_TEST(semicolon_along_should_not_break) {
  INIT_TEST_STATE();
  OPEN_STREAM(";");
  DoForth(&state);
  CLOSE_STREAM();
  mu_assert_double_eq(0, CellStackSize(&state.returnStack));
  FREE_TEST_STATE();
}

MU_TEST(colonNONAME_should_create_xt_and_colonsys) {
  INIT_TEST_STATE();
  OPEN_STREAM(":NONAME 10 9 + ; execute");
  DoForth(&state);
  CLOSE_STREAM();
  Cell cellResult = CellStackPop(&state.dataStack);
  mu_assert_double_eq(19 , cellResult.value);
  FREE_TEST_STATE();
}


MU_TEST_SUITE(sys_tests) {
  MU_RUN_TEST(colon_should_put_colonsys_on_stack);
  MU_RUN_TEST(semicolon_should_consume_colonsys);
  MU_RUN_TEST(semicolon_along_should_not_break);
  MU_RUN_TEST(colonNONAME_should_create_xt_and_colonsys);
}


//
// Run all the Tests
int TestSys(void) {
  MU_RUN_SUITE(sys_tests);

  MU_REPORT();
  return MU_EXIT_CODE;
}
