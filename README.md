# Simple C++ Shell Implementation

A minimal Unix-like shell written in C++ that handles basic commands, built-ins, and process management.

## Features

- **Command execution**: Runs external programs (e.g., `ls`, `echo`, `g++`)
- **Built-in commands**:
  - `cd`: Change directory
  - `exit`: Terminate the shell
- **Prompt display**: Shows current working directory
- **Process management**: Properly waits for child processes
- **Input handling**: Basic tokenization of commands and arguments
# Build Instructions
- Compile with any C++11 (or newer) compiler:
```bash
g++ -std=c++11 -o myshell myshell.cpp
```
# Usage
- Run the compiled binary:
```bash
./myshell
/home/user/projects > ls -l
/home/user/projects > cd src
/home/user/projects/src > exit
