#include "app/client_manager.h"
#include "unity/unity.h"

void setUp(void) {}
void tearDown(void) {}

void test_init_empty_manager() {
  ClientManager manager;
  initClientManager(&manager);

  TEST_ASSERT_EQUAL_INT(0, getClientCount(&manager));
}

void test_add_new_client() {
  ClientManager manager;
  initClientManager(&manager);

  AcceptedSocket socket = {.acceptedSocketFD = 4};
  addClient(&manager, socket);

  TEST_ASSERT_EQUAL_INT(1, getClientCount(&manager));
}

void test_get_client_by_id() {
  ClientManager manager;
  initClientManager(&manager);

  AcceptedSocket socket = {.acceptedSocketFD = 4};
  addClient(&manager, socket);

  Client *clientById = getClientByID(&manager, 1);

  TEST_ASSERT_EQUAL_INT(1, clientById->id);
  TEST_ASSERT_EQUAL_INT(4, clientById->socket.acceptedSocketFD);
}

void test_remove_client_by_fd() {
  ClientManager manager;
  initClientManager(&manager);

  AcceptedSocket socket = {.acceptedSocketFD = 4};
  addClient(&manager, socket);

  TEST_ASSERT_EQUAL_INT(1, removeClientByFD(&manager, 4));
  TEST_ASSERT_EQUAL_INT(0, getClientCount(&manager));
}

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_init_empty_manager);
  RUN_TEST(test_add_new_client);
  RUN_TEST(test_get_client_by_id);
  RUN_TEST(test_remove_client_by_fd);
  return UNITY_END();
}
