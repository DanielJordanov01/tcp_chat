# TCP Chat Server & Client in C

This project implements a basic multi-threaded TCP chat system in C using sockets and POSIX threads (`pthread`). It includes both a **server** and a **client** that communicate over IPv4. The server can handle multiple clients and broadcasts messages to all connected clients.

## ⚠️ Disclaimer

The aim for this project is for me to explore socket programming and memory management in C. It's highly likely
I've done both poorly.

## 🛠 Features

- Multi-client chat server using threads
- Threaded client that listens and sends messages simultaneously
- Uses raw sockets and manual memory management

## 📁 Folder Structure

```
tcp-chat/
├── include/            # Header files (.h)
│
├── src/                # Source files (.c)
│
├── build/              # Compiled output (binary + .o files) [auto-created]
│
├── docs/               # Documentation on functions [auto-created]
│
├── Makefile            # Build script
├── Doxyfile            # Documentation configuration
├── .gitignore          # Git ignore rules
└── README.md           # Project overview
```

---

## ⚙️ Build Instructions

### 🧱 Requirements

- GCC or Clang
- POSIX-compliant OS (Linux, macOS)
- `make` (optional, but easier)

### 🔧 Build with Make

```bash
make
```

This will compile all source files and place the output in the `build/` directory:

- `build/server`
- `build/client`

To clean up build artifacts:

```bash
make clean
```

---

## 🧪 Run Instructions

### 1. Start the Server

```bash
./build/server
```

The server listens on `127.0.0.1:2000` and accepts incoming connections.

### 2. Start One or More Clients (in separate terminals)

```bash
./build/client
```

- The client will ask for your name.
- Then it lets you type and send messages.
- Type `exit` to disconnect.

All messages are broadcasted to every other connected client.

---

## 📝 Example

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

## 📌 Notes

- IP address in `client.c` is currently hardcoded to `127.0.0.1`.
- Port is `2000` by default — you can change it in the source code.
- Memory is manually allocated/freed — be careful to avoid leaks or race conditions.

---

## 🔗 Resources

- https://www.youtube.com/watch?v=KEiur5aZnIM
