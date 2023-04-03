
# C++ Socket.io Server

This project aims to create a [Socket.IO](https://socket.io/) server in pure C++.

Javascript is purely for testing.

Only tested on Windows (Cygwin).
Uses POSIX Sockets API
## Run Locally

Clone the project

```bash
  git clone https://github.com/andrew-bork/socket-io-server-cpp
```

Go to the project directory

```bash
  cd socket-io-server-cpp
```

Build

```bash
  make
```

Start the server

```bash
  ./output/main
```

Test with a node.js client

```bash
  node test-client/client.js
```
