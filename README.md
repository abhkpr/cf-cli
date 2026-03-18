# cf-cli

A minimal terminal client for Codeforces built in C++.

This project is an attempt to interact with Codeforces directly from the terminal, similar to tools like GitHub CLI, but focused on competitive programming workflows.

---

## Motivation

Most competitive programmers use the browser for everything:

* checking problems
* viewing contests
* checking submissions

This tool aims to:

* reduce browser dependency
* make workflows faster
* provide a clean terminal experience

Also, this is a learning project to understand:

* HTTP requests in C++
* working with APIs
* building CLI tools
* structuring real-world C++ projects

---

## Features (current)

* Get user information

```bash
cf user <handle>
```

* List contests

```bash
cf contest list
```

---

## Project Structure

```
cf-cli/
├── include/
│   ├── api/
│   │   └── codeforces.h
│   └── commands/
│       ├── user.h
│       └── contest.h
├── src/
│   ├── main.cpp
│   ├── api/
│   │   └── codeforces.cpp
│   └── commands/
│       ├── user.cpp
│       └── contest.cpp
├── build/
└── README.md
```

---

## How It Works

### 1. CLI Entry

The program starts from `main.cpp`.

It reads command line arguments:

```
cf <command> <subcommand> [args]
```

Example:

```
cf user tourist
cf contest list
```

---

### 2. Command Layer

Each command is separated into its own module:

* `user.cpp` → handles user-related operations
* `contest.cpp` → handles contest-related operations

This keeps the code clean and scalable.

---

### 3. API Layer

Located in:

```
src/api/codeforces.cpp
```

This layer:

* makes HTTP requests using libcurl
* returns raw response data

Function used:

```
http_get(url)
```

---

### 4. JSON Parsing

Uses `nlohmann/json` library.

Example:

```
auto j = json::parse(data);
```

This converts API response into usable data.

---

## Dependencies

* libcurl (for HTTP requests)
* nlohmann/json (for JSON parsing)

---

## Installation

### Install libcurl

```bash
sudo apt update
sudo apt install libcurl4-openssl-dev
```

### Add JSON library

```bash
mkdir -p include/nlohmann
wget https://raw.githubusercontent.com/nlohmann/json/develop/single_include/nlohmann/json.hpp -O include/nlohmann/json.hpp
```

---

## Build

From project root:

```bash
g++ src/main.cpp src/api/codeforces.cpp src/commands/user.cpp src/commands/contest.cpp -Iinclude -o build/cf -lcurl
```

---

## Run

```bash
./build/cf user tourist
./build/cf contest list
```

---

## Design Decisions

* No external CLI libraries (manual parsing for learning)
* Modular structure (API vs commands)
* Header/source separation
* Minimal dependencies

---

## Current Limitations

* No authentication
* No submission support
* Basic CLI parsing (not robust yet)
* No error handling for network failures

---

## Future Plans

* Better CLI parsing system
* Add submissions command
* Add problem fetching
* Implement login/session handling
* Submit solutions from terminal
* Improve output formatting

---

## Contributing

This is an open learning project.

You can contribute by:

* adding new commands
* improving structure
* fixing bugs
* improving documentation

Before contributing:

* keep code simple
* follow existing structure
* avoid unnecessary complexity

---

## Notes for Contributors

* Do not include `.cpp` files inside other `.cpp`
* Use headers properly
* Keep API logic separate from command logic


