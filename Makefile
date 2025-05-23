CC = gcc
CFLAGS = -Wall -Wextra -Iinclude -Iinclude/net -Iinclude/app -Iinclude/core
LDFLAGS = -lpthread

# Directories
SRC_DIR = src
BUILD_DIR = build
TEST_DIR = test
INCLUDE_DIR = include

# Recursive find for .c files, exclude main programs
SRC_FILES := $(shell find $(SRC_DIR) -name '*.c' ! -name 'client.c' ! -name 'server.c')
OBJ_FILES := $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC_FILES))

# Special targets
CLIENT_BIN = $(BUILD_DIR)/client
SERVER_BIN = $(BUILD_DIR)/server
CLIENT_SRC = $(SRC_DIR)/main/client.c
SERVER_SRC = $(SRC_DIR)/main/server.c
CLIENT_OBJ = $(BUILD_DIR)/main/client.o
SERVER_OBJ = $(BUILD_DIR)/main/server.o

UNITY_SRC := $(TEST_DIR)/unity/unity.c
TEST_SRC := $(wildcard $(TEST_DIR)/test_*.c)
TEST_BINS := $(patsubst $(TEST_DIR)/%.c, $(BUILD_DIR)/%, $(TEST_SRC))

# Phony targets
.PHONY: all clean test docs

# Default target
all: $(CLIENT_BIN) $(SERVER_BIN)

test: $(TEST_BINS)
	@for test in $(TEST_BINS); do \
		echo "Running $$test"; \
		./$$test; \
	done

docs: 
	doxygen Doxyfile

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

# Build rule for all .o files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Link binaries
$(CLIENT_BIN): $(CLIENT_OBJ) $(OBJ_FILES)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(SERVER_BIN): $(SERVER_OBJ) $(OBJ_FILES)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

# Build tests
$(BUILD_DIR)/test_%: $(TEST_DIR)/test_%.c $(UNITY_SRC) $(SRC_FILES) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

clean:
	rm -rf $(BUILD_DIR)
