CC = gcc
CFLAGS = -Wall -Wextra -Iinclude
SRC_DIR = src
BUILD_DIR = build
TEST_DIR = test

CLIENT_SRC = $(SRC_DIR)/client.c
SERVER_SRC = $(SRC_DIR)/server.c
UTIL_SRC = $(SRC_DIR)/util.c
TESTS := $(TEST_DIR)/test_util
UNITY_SRC := $(TEST_DIR)/unity/unity.c

CLIENT_OBJ = $(BUILD_DIR)/client.o
SERVER_OBJ = $(BUILD_DIR)/server.o
UTIL_OBJ = $(BUILD_DIR)/util.o

CLIENT_BIN = $(BUILD_DIR)/client
SERVER_BIN = $(BUILD_DIR)/server

.PHONY: all clean

all: $(CLIENT_BIN) $(SERVER_BIN)

.PHONY: test
test: build/tests

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

# Build client binary
$(CLIENT_BIN): $(CLIENT_OBJ) $(UTIL_OBJ) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $^ -o $@ -lpthread

# Build server binary
$(SERVER_BIN): $(SERVER_OBJ) $(UTIL_OBJ) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $^ -o $@ -lpthread

# Compile client object
$(CLIENT_OBJ): $(CLIENT_SRC) | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Compile server object
$(SERVER_OBJ): $(SERVER_SRC) | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Compile util object
$(UTIL_OBJ): $(UTIL_SRC) | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build directory
clean:
	rm -rf $(BUILD_DIR)

# Run tests
build/tests: $(TESTS).c $(SRC_DIR)/util.c $(UNITY_SRC)
	$(CC) -o build/test_util $^
	./build/test_util
