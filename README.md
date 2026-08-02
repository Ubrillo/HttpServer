# C++ HTTP Server

A lightweight HTTP server built from scratch in C++ using raw POSIX sockets, with no external networking libraries. It serves static HTML pages and handles multiple clients concurrently using a thread-per-connection model.

## Features

- Custom HTTP request parsing (method, path, headers)
- Static file serving with correct `Content-Type`, `Content-Length`, and 404 handling
- Concurrent client handling via `std::thread` (one thread per connection)
- Route-to-file mapping through a simple router
- Executable-relative path resolution, so the server runs correctly regardless of the working directory it's launched from

## Architecture

### Request flow

1. `Server::start()` creates a TCP socket, binds it, and listens for incoming connections.
2. Each accepted connection is handed off to `Server::handleClient()` on its own detached thread, so the main loop can immediately go back to accepting the next client.
3. `handleClient()` reads the raw request, parses it with `HttpParser`, and looks up the requested path in `Router`.
4. The router returns a file path, which is read from disk and returned as the HTTP response body, with the appropriate status and headers.

### Design decisions

**Thread-per-connection over a single-threaded loop.** Each client connection runs in its own detached `std::thread`, so a slow or long-lived connection can't block other clients from being accepted and served. This was verified by artificially delaying request handling and confirming multiple concurrent clients completed in parallel rather than queuing sequentially.

**Routes are read-only after startup.** All routes are registered once in `routerConfig()` before the server starts accepting connections. Since no thread ever writes to the router after that point, concurrent reads from multiple client threads are safe without additional locking.

**File paths are resolved relative to the executable, not the working directory.** The server reads its own path via `/proc/self/exe` and resolves static file paths from there, so it behaves consistently whether it's launched from the project root, from within `src/`, or from any other directory.

## Project structure

```
.
├── src/
│   ├── server.cpp       # Socket setup, accept loop, client handling
│   ├── server.h
│   ├── httpParser.cpp      # Raw request parsing
│   ├── httpParser.h
│   └── router.cpp           # Path-to-file routing
│   ├── httpParser.h 
└── public/
    ├── index.html
    ├── about.html
    └── contact.html
```

## Building

Requires a C++17-compatible compiler.

```bash
g++ -std=c++17 -pthread src/server.cpp -o server
```

The `-pthread` flag is required on Linux for `std::thread` support.

## Running

```bash
./server
```

By default the server listens on port `1234`. Visit `http://localhost:1234/` in a browser, or test with `curl`:

```bash
curl http://localhost:1234/about
```

## Current routes

| Path | Serves |
|---|---|
| `/` | `public/index.html` |
| `/about` | `public/about.html` |
| `/contact` | `public/contact.html` |

Requests to any other path return a `404 Not Found`.

## Known limitations / next steps

- **Fixed route list** — routes currently map one-to-one to specific files rather than serving arbitrary files from `public/` (e.g. CSS or JS assets). Generalizing this into a proper static file handler is a planned next step.
- **Unbounded thread spawning** — each connection spawns a new OS thread with no upper limit, which could exhaust system resources under heavy or malicious load. A bounded thread pool is a natural follow-up.
- **Single-buffer request reads** — the request buffer is fixed at 1024 bytes; larger requests (e.g. POST bodies) would currently be truncated.
- **HTTP/1.1 subset only** — no support for keep-alive connections, chunked transfer encoding, or request bodies beyond basic parsing.

## What this project demonstrates

- Low-level socket programming with POSIX APIs (`socket`, `bind`, `listen`, `accept`)
- Manual HTTP protocol handling without a framework
- Concurrent programming with `std::thread`
- Debugging real-world issues around working directories, path resolution, and race conditions in a networked C++ application
