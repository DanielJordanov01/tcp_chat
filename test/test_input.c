#include "../include/input.h"
#include "unity/unity.h"
#include <stdio.h>
#include <stdlib.h>

void setUp(void) {}
void tearDown(void) {}

void test_readUserInput_reads_input_correctly(void) {
  FILE *input = tmpfile();
  fprintf(input, "hello world\n");
  rewind(input);

  UserInput result = readUserInput("Enter message", input);

  TEST_ASSERT_NOT_NULL(result.value);
  TEST_ASSERT_EQUAL_STRING("hello world", result.value);
  TEST_ASSERT_TRUE(result.count > 0);

  free(result.value);
  fclose(input);
}

void test_readUserInput_handles_empty_input(void) {
  FILE *input = tmpfile();
  fprintf(input, "\n");
  rewind(input);

  UserInput result = readUserInput("Prompt", input);

  TEST_ASSERT_NOT_NULL(result.value);
  TEST_ASSERT_EQUAL_STRING("", result.value);

  free(result.value);
  fclose(input);
}

void test_readUserInput_handles_eof(void) {
  FILE *input = tmpfile();
  rewind(input);

  UserInput result = readUserInput("Prompt", input);

  TEST_ASSERT_NULL(result.value);
  TEST_ASSERT_EQUAL(0, result.size);
  TEST_ASSERT_EQUAL(0, result.count);

  fclose(input);
}

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_readUserInput_reads_input_correctly);
  RUN_TEST(test_readUserInput_handles_empty_input);
  RUN_TEST(test_readUserInput_handles_eof);
  return UNITY_END();
}
