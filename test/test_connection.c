#include "../include/connection.h"
#include "unity/unity.h"
#include <arpa/inet.h>
#include <unistd.h>

void setUp(void) {}
void tearDown(void) {}

void test_createTCPIpv4Socket_should_return_valid_socket_fd() {
  int sockfd = createTCPIpv4Socket();
  TEST_ASSERT_GREATER_OR_EQUAL(0, sockfd);
  close(sockfd);
}

void test_createTCPIpv4Address_should_set_ip_and_port() {
  char *ip = "127.0.0.1";
  int port = 8080;
  struct sockaddr_in addr = createTCPIpv4Address(ip, port);

  TEST_ASSERT_EQUAL(AF_INET, addr.sin_family);
  TEST_ASSERT_EQUAL(htons(port), addr.sin_port);

  struct in_addr expected;
  inet_pton(AF_INET, ip, &expected);
  TEST_ASSERT_EQUAL_MEMORY(&expected, &addr.sin_addr, sizeof(struct in_addr));
}

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_createTCPIpv4Socket_should_return_valid_socket_fd);
  RUN_TEST(test_createTCPIpv4Address_should_set_ip_and_port);
  return UNITY_END();
}
