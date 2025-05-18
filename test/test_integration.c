#include "unity/unity.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

void setUp(void) {}
void tearDown(void) {}

pid_t runProcess(char *executableName) {
  pid_t pid = fork();
  char path[100];
  sprintf(path, "./build/%s", executableName);

  if (pid == 0) {
    execl(path, executableName, NULL);
    exit(1);
  }

  return pid;
}

void cleanup(pid_t pids[]) {
  int n = sizeof(pids) / sizeof(pids[0]);

  for (int i = 0; i < n; i++) {
    kill(pids[i], SIGTERM);
    waitpid(pids[i], NULL, 0);
  }
}

void test_client_server_communication() {
  pid_t server_pid = runProcess("server");
  sleep(1);

  pid_t client_pid = runProcess("client");
  sleep(3);

  pid_t client_pid_2 = runProcess("client");
  sleep(3);

  pid_t pids[] = {client_pid_2, client_pid, server_pid};
  cleanup(pids);

  TEST_ASSERT_TRUE(1);
}

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_client_server_communication);
  return UNITY_END();
}
