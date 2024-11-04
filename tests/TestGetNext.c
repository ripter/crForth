#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "raylib.h"

#include "minunit.h"
#include "Test.h"
#include "../src/crForth.h"

#ifdef OPEN_STREAM
  #undef OPEN_STREAM
#endif
#define OPEN_STREAM(input)                                                     \
  FILE *inputStream = fmemopen(input, TextLength(input), "r");

#ifdef CLOSE_STREAM
  #undef CLOSE_STREAM
#endif
#define CLOSE_STREAM()                                                         \
  fclose(inputStream);                                                         \

#define SILENCE_STDERR()                                                       \
  FILE *original_stderr = stderr;                                              \
  stderr = fopen("/dev/null", "w");

#define RESTORE_STDERR()                                                       \
  fclose(stderr);                                                              \
  stderr = original_stderr;

char wordBuffer[MAX_WORD_LENGTH];

MU_TEST(basic_string_1) {
  char* testValue = "Hello, World!";
  char* expected = "hello,";
  OPEN_STREAM(testValue);
  GetNextWord(inputStream, wordBuffer, MAX_WORD_LENGTH); ;
  CLOSE_STREAM();
	mu_assert_string_eq(wordBuffer, expected);
}

MU_TEST(basic_string_2) {
  char* testValue = ": FIRST_COLON ;";
  char* expected = ":";
  OPEN_STREAM(testValue);
  GetNextWord(inputStream, wordBuffer, MAX_WORD_LENGTH); ;
  CLOSE_STREAM();
	mu_assert_string_eq(wordBuffer, expected);
}

MU_TEST(leading_whitespace) {
  char* testValue = " 3";
  char* expected = "3";
  OPEN_STREAM(testValue);
  GetNextWord(inputStream, wordBuffer, MAX_WORD_LENGTH); ;
  CLOSE_STREAM();
	mu_assert_string_eq(wordBuffer, expected);
}

MU_TEST(word_too_long) {
  char* testValue = "Loremipsumdolorsitamet,consecteturadipiscingelit.Maurisfaucibusmagnaidnibhultricestempor.Donecvellectussem.Fuscevellacusetodiodapibusvehiculanecegetenim.Vivamusbibendum,arcuetdictumdictum,tellusliberoposuereipsum,velvehiculaliberotortoratipsum.Crasconsecteturcursusiaculis.Integerutsemvitaelacusiaculismollis.Vestibulumjustotellus,pellentesqueideleifendac,pretiumnecvelit.Fuscefacilisisligulaeunislpulvinarporttitor.Nuncduirisus,egestasnecaliquetin,auctornonsapien.Maurissitametjustoinnisiconvallisaliquamnoninorci.Namluctustellusacsollicitudinfaucibus.Maurisetestatorcimattisinterdum.Quisquesollicitudinposueredolor.Sedtinciduntnisiacerosfringilla,sedcursusnullalacinia.Nullavehiculapharetranisiinlacinia.Suspendisseefficitur,ligulautsodalesmolestie,eratauguevolutpatmaurissitametblanditeratorciatligula.Donecscelerisquearcuetornareluctus.Integerneclobortiseros.Integeregetcongueaugue.Duispharetraacquamnonegestas.Maecenasullamcorpercongueelituthendrerit.Praesentsednibhetvelitconsequatsollicitudin.Quisqueconsecteturlacusatsapienvarius,attinciduntnuncrhoncus.Nullafacilisi.Integeretinterdumnibh,atbibendumorci.Sedsedloremeumaurispulvinarportaneccommodourna.Praesentvenenatisaccumsanipsumnecgravida.Proinportarhoncusligulavitaevehicula.Aeneancondimentum,urnaidullamcorperfermentum,nibhleomattisaugue,atconvallismetuspurusvelarcu.Phaselluscongueportaest,necmaximuslectusscelerisquenon.Sedmaximusodiositametpellentesquesuscipit.Fusceduitortor,posuereintristiqueid,cursusintortor.Suspendisseportaegetsapiensitametdapibus.Fusceinfeuittartellus.Vivamussaviverrasapien.Nuncemalesuadafelis.Seddictumloremaliquettempusultrices.Aliquamvestibulumpulvinarpharetra.Suspendissedictummetusaclacustempus,posueremaximusturpisrutrum.Praesent.";
  SILENCE_STDERR(); 
  OPEN_STREAM(testValue);
  bool expected = GetNextWord(inputStream, wordBuffer, MAX_WORD_LENGTH); ;
  CLOSE_STREAM();
  RESTORE_STDERR();
  mu_assert(expected == false, "Fail to get word when word is too long");
}

MU_TEST(tab_delimited_words) {
  char* testValue = "@home\tword";
  char* expected = "@home";
  OPEN_STREAM(testValue);
  GetNextWord(inputStream, wordBuffer, MAX_WORD_LENGTH); ;
  CLOSE_STREAM();
  mu_assert_string_eq(wordBuffer, expected);
}

MU_TEST(multiple_words_newline) {
  char* testValue = ",\nsecond";
  char* expected = ",";
  OPEN_STREAM(testValue);
  GetNextWord(inputStream, wordBuffer, MAX_WORD_LENGTH); ;
  CLOSE_STREAM();
  mu_assert_string_eq(wordBuffer, expected);
}

MU_TEST(empty_string) {
  // char* testValue = " \n\t";
  // char* expected = NULL;
  OPEN_STREAM(" \n\t");
  bool expected = GetNextWord(inputStream, wordBuffer, MAX_WORD_LENGTH); ;
  CLOSE_STREAM();

  mu_assert(expected == false, "Returns false for empty string");
  // RESTORE_STDERR();
  // mu_assert_string_eq(expected, wordBuffer);
  // mu_assert(wordBuffer == expected, "Expected NULL for empty string");
}

MU_TEST(trailing_whitespace) {
  char* testValue = "Hello   ";
  char* expected = "hello";
  OPEN_STREAM(testValue);
  GetNextWord(inputStream, wordBuffer, MAX_WORD_LENGTH); ;
  CLOSE_STREAM();
  mu_assert_string_eq(wordBuffer, expected);
}

MU_TEST(prog_simple_1) {
  char* testValue = "2 3 4 + + .";
  OPEN_STREAM(testValue);
  // should be able to get each word in the program
  GetNextWord(inputStream, wordBuffer, MAX_WORD_LENGTH); ;
  mu_assert_string_eq(wordBuffer, "2");

  GetNextWord(inputStream, wordBuffer, MAX_WORD_LENGTH); ;
  mu_assert_string_eq(wordBuffer, "3");

  GetNextWord(inputStream, wordBuffer, MAX_WORD_LENGTH); ;
  mu_assert_string_eq(wordBuffer, "4");

  GetNextWord(inputStream, wordBuffer, MAX_WORD_LENGTH); ;
  mu_assert_string_eq(wordBuffer, "+");
  GetNextWord(inputStream, wordBuffer, MAX_WORD_LENGTH); ;
  mu_assert_string_eq(wordBuffer, "+");

  GetNextWord(inputStream, wordBuffer, MAX_WORD_LENGTH); ;
  mu_assert_string_eq(wordBuffer, ".");
  CLOSE_STREAM();
}


//
// Run all the Tests
//
int TestGetNext(void) {

  MU_RUN_TEST(empty_string);
  MU_RUN_TEST(basic_string_1);
  MU_RUN_TEST(basic_string_2);
  MU_RUN_TEST(leading_whitespace);
  MU_RUN_TEST(word_too_long);
  MU_RUN_TEST(tab_delimited_words);
  MU_RUN_TEST(multiple_words_newline);
  MU_RUN_TEST(trailing_whitespace);
  MU_RUN_TEST(prog_simple_1);
  

  MU_REPORT();
  return MU_EXIT_CODE;
}
