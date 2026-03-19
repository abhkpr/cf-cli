# cf-cli

A minimal terminal client for Codeforces built in C++.

This project lets you interact with Codeforces directly from the terminal, similar to tools like GitHub CLI, but focused on competitive programming workflows.

## Motivation

Most competitive programmers use the browser for everything:

- Checking problems
- Viewing contests
- Checking submissions

This tool aims to:

- Reduce browser dependency
- Make workflows faster
- Provide a clean terminal experience
- Serve as a learning project for understanding APIs, HTTP requests, and CLI tool development in C++

## Features (current)

- Get user information
```

cf user <handle>

```

- List contests
```

cf contest list

```

- Fetch and view problems
```

cf problem <contestId><index> [--refresh]

```

- Automatic caching with refresh:
  - Problems, contests, and user info are cached in `~/.cf-cli`
  - Cache automatically refreshes if older than 12 hours
  - Manual refresh supported with `--refresh` flag

## Project Structure

```

cf-cli/
├── include/
│   ├── api/
│   │   └── codeforces.h
│   └── commands/
│       ├── user.h
│       ├── contest.h
│       └── problem.h
├── src/
│   ├── main.cpp
│   ├── api/
│   │   └── codeforces.cpp
│   └── commands/
│       ├── user.cpp
│       ├── contest.cpp
│       ├── problem.cpp
│       └── registry.cpp
├── src/utils/
│   └── cache.cpp
├── build/
└── README.md

```

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
cf problem 1700A

```

### 2. Command Layer

Each command is separated into its own module:

- `user.cpp` → handles user operations
- `contest.cpp` → handles contest operations
- `problem.cpp` → handles problem fetching

This modular design keeps the code clean and scalable.

### 3. API Layer

Located in `src/api/codeforces.cpp`, it:

- Makes HTTP requests using libcurl
- Returns raw response data
- Works with the JSON parsing layer

### 4. JSON Parsing

Uses `nlohmann/json` library.

Example:

```

auto j = json::parse(data);

```

This converts API response into usable JSON objects.

### 5. Caching System

- Stores cached data in `~/.cf-cli/`  
- Checks file modification time  
- Automatically refreshes cache if older than 12 hours  
- Manual refresh supported via `--refresh`  

## Dependencies

- libcurl (for HTTP requests)  
- nlohmann/json (for JSON parsing)  

## Installation

### Install libcurl

```

sudo apt update
sudo apt install libcurl4-openssl-dev

```

### Add JSON library

```

mkdir -p include/nlohmann
wget [https://raw.githubusercontent.com/nlohmann/json/develop/single_include/nlohmann/json.hpp](https://raw.githubusercontent.com/nlohmann/json/develop/single_include/nlohmann/json.hpp) -O include/nlohmann/json.hpp

```

## Build

From project root:

```

make

```

This will compile all files and produce the binary:

```

build/cf

```

## Run

```

./build/cf user tourist
./build/cf contest list
./build/cf problem 1700A

```

## Design Decisions

- No external CLI libraries (manual parsing for learning)  
- Modular structure (API vs commands)  
- Header/source separation  
- Minimal dependencies  
- Auto-refresh caching for offline-friendly performance

## Current Limitations

- No authentication  
- No submission support  
- Basic CLI parsing (not robust yet)  
- Limited error handling for network failures  

## Future Plans

- Better CLI parsing system  
- Add submissions command  
- Add problem fetching by tag  
- Implement login/session handling  
- Submit solutions from terminal  
- Improve output formatting and terminal UX  

## Contributing

This is an open learning project.

You can contribute by:

- Adding new commands  
- Improving structure  
- Fixing bugs  
- Improving documentation  

Before contributing:

- Keep code simple  
- Follow existing structure  
- Avoid unnecessary complexity  

