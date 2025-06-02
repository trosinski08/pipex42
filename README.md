# Pipex (pipex42)

## Table of Contents
1.  [Project Description](#project-description)
2.  [Project Goal](#project-goal)
3.  [Functionalities](#functionalities)
4.  [How it Works?](#how-it-works)
5.  [Project Structure](#project-structure)
6.  [Building](#building)
7.  [Usage & Test Cases](#usage--test-cases)
8.  [Flow Diagram](#flow-diagram)
9.  [License](#license)

## Project Description
Pipex is a program that simulates the Unix pipe operator `|`, allowing the output of one command to be redirected as input to another command. The project is part of the 42 school curriculum and provides a deep understanding of inter-process communication (IPC) mechanisms and process management in Unix-like systems.

## Project Goal
*   Understand and implement the pipe mechanism (`pipe`)
*   Master process management with `fork`, `execve`, `wait`, `waitpid`
*   Handle file descriptors and I/O redirections
*   Parse and execute shell commands with arguments
*   Implement here-document functionality

## Functionalities
*   Basic pipe functionality: `./pipex infile "cmd1" "cmd2" outfile`
*   Here-document support: `./pipex here_doc LIMITER "cmd1" "cmd2" outfile`
*   Multiple commands (unlimited pipes): `./pipex infile "cmd1" "cmd2" "cmd3" ... "cmdN" outfile`
*   Handling of commands with single and double quotes
*   Proper error handling and memory management
*   Support for command paths in PATH environment variable

## How it Works?

### 1. Basic Pipe Operation
*   Creates a pipe between two processes
*   First process reads from infile, executes cmd1, writes to pipe
*   Second process reads from pipe, executes cmd2, writes to outfile
*   Equivalent to shell command: `< infile cmd1 | cmd2 > outfile`

### 2. Here-doc Operation
*   Creates temporary pipe for here-document input
*   Reads stdin until delimiter is encountered
*   Uses collected input as stdin for first command
*   Equivalent to: `<< LIMITER cmd1 | cmd2 >> outfile`

### 3. Multiple Commands
*   Creates a chain of pipes
*   Each command reads from previous pipe and writes to next pipe
*   Last command writes to outfile
*   Equivalent to: `< infile cmd1 | cmd2 | cmd3 | ... | cmdN > outfile`

## Project Structure
```
pipex42/
├── Makefile           # Build system
├── README.md          # Documentation
├── src/              # School project (mandatory part)
│   ├── pipex.c
│   ├── utils.c
│   ├── parsing_utils.c
│   └── pipex.h
├── src_bonus/        # Enhanced version (default build)
│   ├── pipex_bonus.c
│   ├── utils_bonus.c
│   ├── parsing_utils_bonus.c
│   ├── errors.c
│   └── pipex_bonus.h
└── libft/            # Library with utility functions
```

## Building

### Default Build (Enhanced Version)
```bash
make        # Builds pipex with here_doc and multiple pipes support
```

### School Project Build (Mandatory Part)
```bash
make mandatory  # Builds pipex_mandatory (basic functionality only)
```

### Other Make Targets
```bash
make clean     # Remove object files
make fclean    # Remove object files and executables
make re        # Full rebuild
```

## Usage & Test Cases

### Basic Usage (Both Versions)
```bash
# Create test files
echo "Hello World\nTest Line\nAnother Test" > infile.txt

# Basic usage (equivalent in both versions)
./pipex infile.txt "grep Test" "wc -l" outfile.txt
# Should output "2" to outfile.txt
```

### Here-doc Feature (Enhanced Version)
```bash
# Basic here-doc usage
./pipex here_doc EOF "cat" "grep test" outfile.txt
this is a test
another test line
final test
EOF
# outfile.txt should contain all lines with "test"

# Here-doc with command arguments
./pipex here_doc STOP "grep -i hello" "wc -l" outfile.txt
Hello World
hello test
HELLO FINAL
STOP
# outfile.txt should contain "3"
```

### Multiple Commands (Enhanced Version)
```bash
# Three commands
./pipex infile.txt "cat" "grep Test" "wc -l" outfile.txt

# Complex command chain
./pipex infile.txt "cat" "grep Test" "sed 's/Test/CHECK/g'" "wc -l" outfile.txt
```

### Error Handling Test Cases
```bash
# Non-existent input file
./pipex nonexistent.txt "cat" "wc -l" outfile.txt
# Should show appropriate error message

# Invalid command
./pipex infile.txt "invalidcmd" "wc -l" outfile.txt
# Should show "command not found" error

# Permission denied
./pipex infile.txt "cat" "wc -l" /root/forbidden.txt
# Should show permission denied error
```

### Advanced Test Cases

#### Multiple Commands Test
```bash
# Test with 6 commands (works correctly)
./pipex input.txt "cat" "sort" "uniq" "tr l L" "tr e E" "grep test" output.txt

# Test with 7 commands and newline handling (cat -e test)
./pipex input.txt "cat -e" "cat -e" "cat -e" "cat -e" "cat -e" "cat -e" "cat -e" output.txt
# Each line will show 7 $ signs, demonstrating correct newline handling through all pipes

# Test parallel execution with sleep
./pipex input.txt "sleep 10" "sleep 10" "sleep 10" "sleep 10" "sleep 10" "sleep 10" "sleep 10" output.txt
# All sleeps execute in parallel, total execution time ~10s, not 70s
```

#### Process Control Tests
```bash
# Test process handling with kill command
./pipex input.txt "sleep 10" "pkill sleep" "sleep 10" output.txt
# Demonstrates proper process management and signal handling
```

#### Here_doc Tests
```bash
# Test here_doc with multiple commands
./pipex here_doc END "tr [:lower:] [:upper:]" "sort -r" output.txt << EOF
test line 1
test line 2
another line
last line
END
EOF
```

### Key Findings from Testing
1. Command Chain Limits:
   - Reliable execution with up to 7 commands
   - Proper pipe management and data flow
   - Correct handling of standard input/output

2. Process Management:
   - Parallel execution of commands
   - Proper cleanup of child processes
   - Correct signal handling

3. Special Features:
   - Proper newline handling across multiple pipes
   - Here_doc functionality working as expected
   - Correct handling of various command types (text processing, system commands)
```

## Flow Diagram
[Previous diagram content remains unchanged]

## License
This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.