CC = gcc
CFLAGS = -Wall -Wextra -Iinclude
LDFLAGS = -lpthread

# Directories
SRC_DIR = src
BUILD_DIR = build
TEST_DIR = test
INCLUDE_DIR = include

SRC_FILES := $(filter-out $(SRC_DIR)/client.c $(SRC_DIR)/server.c, $(wildcard $(SRC_DIR)/*.c))
OBJ_FILES := $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC_FILES))

# Special targets
CLIENT_BIN = $(BUILD_DIR)/client
SERVER_BIN = $(BUILD_DIR)/server
CLIENT_OBJ = $(BUILD_DIR)/client.o
SERVER_OBJ = $(BUILD_DIR)/server.o

UNITY_SRC := $(TEST_DIR)/unity/unity.c

TEST_SRC := $(wildcard $(TEST_DIR)/test_*.c)
TEST_BINS := $(patsubst $(TEST_DIR)/%.c, $(BUILD_DIR)/%, $(TEST_SRC))

# Phony targets
.PHONY: all clean test docs

# Default target
all: $(CLIENT_BIN) $(SERVER_BIN)

# Test target
test: $(TEST_BINS)
	@for test in $(TEST_BINS); do \
		echo "Running $$test"; \
		./$$test; \
	done

docs: 
	doxygen Doxyfile

# Create build directory
$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(CLIENT_BIN): $(CLIENT_OBJ) $(OBJ_FILES) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(SERVER_BIN): $(SERVER_OBJ) $(OBJ_FILES) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(BUILD_DIR)/test_%: $(TEST_DIR)/test_%.c $(UNITY_SRC) $(SRC_FILES) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

clean:
	rm -rf $(BUILD_DIR)

