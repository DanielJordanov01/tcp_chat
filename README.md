# TCP Chat Server & Client in C

This project implements a basic multi-threaded TCP chat system in C using sockets and POSIX threads (`pthread`). It includes both a **server** and a **client** that communicate over IPv4. The server can handle multiple clients and broadcasts messages to all connected clients.

---

## ⚠️ Disclaimer

The aim of this project is for me to explore socket programming and memory management in C. It's highly likely
I've done both poorly.

---

## 🛠 Features

- Multi-client chat server using threads
- Threaded client that listens and sends messages simultaneously
- Uses raw sockets and manual memory management

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
./build/server 127.0.0.1 2000
```

The server listens on `127.0.0.1:2000` and accepts incoming connections.

### 2. Start One or More Clients (in separate terminals)

```bash
./build/client 127.0.0.1 2000
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

## 🔗 Resources

- https://www.youtube.com/watch?v=KEiur5aZnIM
