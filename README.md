# Brainfuck Compiler

This is a set of tools about brainfuck language written in C programming language.

## What is Brainfuck?

Brainfuck is an esoteric programming language created in 1993 by Swiss student Urban Müller.Designed to be extremely minimalistic, the language consists of only eight simple commands, a data pointer, and an instruction pointer.

Brainfuck is an example of a so-called Turing tarpit: it can be used to write any program, but it is not practical to do so because it provides so little abstraction that the programs get very long or complicated. While Brainfuck is fully Turing-complete, it is not intended for practical use but to challenge and amuse programmers. Brainfuck requires one to break down commands into small and simple instructions.

The language takes its name from the slang term brainfuck, which refers to things so complicated or unusual that they exceed the limits of one's understanding, as it was not meant or made for designing actual software but to challenge the boundaries of computer programming.

Because the language's name contains profanity, many substitutes are used, such as brainfsck, branflakes, brainoof, brainfrick, BrainF, and BF.

*-- from wikipedia*

## Commands in Brainfuck

There's only 8 operations(commands) in Brainfuck.

| Character | Instruction Performed |
|------------|------------------------|
| `>` | Increment the data pointer by one (to point to the next cell to the right). |
| `<` | Decrement the data pointer by one (to point to the next cell to the left). |
| `+` | Increment the byte at the data pointer by one. |
| `-` | Decrement the byte at the data pointer by one. |
| `.` | Output the byte at the data pointer. |
| `,` | Accept one byte of input, storing its value in the byte at the data pointer. |
| `[` | If the byte at the data pointer is zero, then instead of moving the instruction pointer forward to the next command, jump it forward to the command after the matching `]` command. |
| `]` | If the byte at the data pointer is nonzero, then instead of moving the instruction pointer forward to the next command, jump it back to the command after the matching `[` command. |

## Build

This project uses CMake for building. Ensure you have CMake and a C++ compiler (GCC/Clang/MSVC) installed.

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

## Usage

### Interpreter (bfi)

Run a Brainfuck program directly:

```bash
# Syntax: ./bfi <filename.bf> [options]
./bfi helloworld.bf
```

### Debugger (bfdbg)

Start the interactive debugger to analyze your code:

```bash
./bfdbg helloworld.bf
```

**Debugger Commands:**

| Command | Alias | Description |
|---------|-------|-------------|
| `step` | `s` | Run single step (execute one command) |
| `next` | `n` | Run next step |
| `continue`| `c`, `x`| Continue execution until breakpoint or end |
| `bp <addr>`| `b` | Set breakpoint at hex address (e.g., `b 1A`) |
| `debp <id>` | `db` | Delete breakpoint by ID |
| `watch <addr>` | `w` | Watch memory at hex address |
| `dewatch <addr>` | `dw` | Stop watching memory at hex address |
| `stat` | `a` | Show current status (pointers, memory value) |
| `setinput` | `si` | Set input stream |
| `watchoutput`| `wo` | View current output buffer |
| `help` | | Show help message |
| `quit` | `exit` | Exit the debugger |

## Project Structure

* `src/core`: Core logic for the Brainfuck virtual machine (Runner, State).
* `src/Interpreter`: Entry point for the command-line interpreter (`bfi`).
* `src/Debugger`: Entry point for the interactive debugger (`bfdbg`).
* `include`: Header files defining interfaces and configuration.
* `test`: Test cases and example Brainfuck scripts.

## About the project

This project implements a modular Brainfuck toolset in C++, featuring a highly configurable interpreter and a powerful interactive debugger.

**Key Features:**
* **Modular Architecture:** Core execution logic is separated from the interface, allowing easy extension.
* **Configurable VM:** Supports custom memory tape size and stack depth limits.
* **Interactive Debugging:** Full control over execution flow with breakpoints and state inspection.

**Development Status:**

:white_check_mark: Brainfuck Interpreter
:white_check_mark: Brainfuck Debugger
:no_entry_sign: Brainfuck Compiler (Planned)
:no_entry_sign: Brainfuck Demos (Planned)
:no_entry_sign: Brainfuck Puzzles (Planned)

Welcome to commit and pull request!