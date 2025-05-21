#include "../include/config.h"
#include "unity/unity.h"

void setUp(void) {}
void tearDown(void) {}

void test_parseArgs_valid_input(void) {
  char *argv[] = {"program", "127.0.0.1", "8080"};
  Config result = parseArgs(3, argv);

  TEST_ASSERT_EQUAL_STRING("127.0.0.1", result.ip);
  TEST_ASSERT_EQUAL_INT(8080, result.port);
  TEST_ASSERT_TRUE(result.valid);
}

void test_parseArgs_invalid_input(void) {
  char *argv[] = {"program"};
  Config result = parseArgs(1, argv);

  TEST_ASSERT_FALSE(result.valid);
}

void test_parseArgs_invalid_port(void) {
  char *argv[] = {"program", "127.0.0.1", "Port"};
  Config result = parseArgs(3, argv);

  TEST_ASSERT_FALSE(result.valid);
}

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_parseArgs_valid_input);
  RUN_TEST(test_parseArgs_invalid_input);
  RUN_TEST(test_parseArgs_invalid_port);
  return UNITY_END();
}
