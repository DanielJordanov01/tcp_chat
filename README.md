# TCP Chat Server & Client in C

This project implements a basic multi-threaded TCP chat system in C using sockets and POSIX threads (`pthread`). It includes both a **server** and a **client** that communicate over IPv4. The server can handle multiple clients and broadcasts messages to all connected clients.

## 🛠️ Features

- Multi-client chat server using threads
- Threaded client that listens and sends messages simultaneously
- Uses raw sockets and manual memory management
- Clean separation of utilities (in `util.c`)

## 📁 Project Structure

```
.
├── client.c          # TCP client that connects to the server
├── server.c          # TCP server that accepts multiple clients
├── util.c            # Helper functions for sockets and addresses
├── util.h            # Header file for util.c
├── Makefile          # To compile the project easily (optional but recommended)
```

---

## 🚀 Build Instructions

### 🧱 Requirements

- GCC or Clang
- POSIX-compliant OS (Linux, macOS)
- `make` (optional, but easier)

### 🔧 Build (Manually)

```bash
gcc -o server server.c util.c -lpthread
gcc -o client client.c util.c -lpthread
```

Or use a simple `Makefile`:

```make
all:
	gcc -o server server.c util.c -lpthread
	gcc -o client client.c util.c -lpthread
```

---

## 🦚 Run Instructions

### 1. Start the Server

```bash
./server
```

The server listens on `127.0.0.1:2000` and accepts incoming connections.

### 2. Start One or More Clients (in separate terminals)

```bash
./client
```

- The client will ask for your name.
- Then it lets you type and send messages.
- Type `exit` to disconnect.

All messages are broadcasted to every other connected client.

---

## 📌 Example

**Client A:**

```
Please enter your name
Alice
Type what to send(type exit to exit)...
Hello!
```

**Client B (sees this):**

```
Alice: Hello!
```

---

## 📄 Notes

- IP address in `client.c` is currently hardcoded to `127.0.0.1`.
- Port is `2000` by default — you can change it in the source code.
- Memory is manually allocated/freed — be careful to avoid leaks or race conditions.

---

## ✅ TODOs / Improvements

- Add support for usernames on the server side
- Graceful handling of disconnected clients
- Improve error reporting and edge-case handling
- Optional: add logging or timestamps

---

## 🔗 Resources

- https://www.youtube.com/watch?v=KEiur5aZnIM

---
