CC = gcc
CFLAGS = -Wall -Wextra -pthread
BUILD_DIR = build

# Source files
UTIL_SRC = util.c
SERVER_SRC = server.c
CLIENT_SRC = client.c

# Object and binary targets
UTIL_OBJ = $(BUILD_DIR)/util.o
SERVER_OBJ = $(BUILD_DIR)/server.o
CLIENT_OBJ = $(BUILD_DIR)/client.o

SERVER_BIN = $(BUILD_DIR)/server
CLIENT_BIN = $(BUILD_DIR)/client

all: $(BUILD_DIR) $(SERVER_BIN) $(CLIENT_BIN)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(SERVER_BIN): $(SERVER_OBJ) $(UTIL_OBJ)
	$(CC) $(CFLAGS) -o $@ $^

$(CLIENT_BIN): $(CLIENT_OBJ) $(UTIL_OBJ)
	$(CC) $(CFLAGS) -o $@ $^

$(BUILD_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean
