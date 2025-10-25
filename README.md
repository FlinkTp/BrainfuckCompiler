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

## About the project

This project is developing... Welcome to commit and pull request!

Todo list:

:warning: Brainfuck Interpreter

:no_entry_sign: Brainfuck Debugger

:no_entry_sign: Brainfuck Compiler

:no_entry_sign: Brainfuck Judge System

:no_entry_sign: Brainfuck Puzzles