*This project has been created as part of the 42 curriculum by otlacerd.*

# get_next_line #

## Description
The **get_next_line** project consists of implementing a function in C that reads from a file descriptor and returns one line at a time at each function call. The goal of this project is to improve understanding of file descriptors, static variables, memory management, and buffered reading using the 'read()' system call.


## Instructions

### Compilation
#### Stardard:
```bash
cc -Wall -Wextra -Werror get_next_line.c get_next_line_utils.c
```
#### With a custom buffer size:
```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c
```
## Execution
The function is intended to be used inside a C program and called repeatedly to read lines from a file descriptor, until the EOF (End of File).


## Algorithm Explanation and Justification
This algorithm uses a single static buffer with two persistent indices to track which portions of the buffer have been consumed and which remain. On a loop, it scans for a newline or the end of the read data and progressively builds the current line by allocating a new buffer, big enough to copy the previous content plus the new segment, then freeing the old allocation. This repeats until a complete line or end-of-file is reached.

Leftover data is preserved implicitly by the indices, eliminating the need to move buffer contents between calls. This design allows the function to remain self-contained, efficient, and deterministic, demonstrating an alternative to the standard multi-function, buffer-shifting approach while fully complying with the project requirements.


## Resources
1. man read
2. man open
3. man close


## AI usage
During the development of this project, ChatGPT was used as a study and verification tool to explore critical aspects of the C language. It helped clarify how compound literals, initializers, and various syntax rules behave in different contexts, allowing for better understanding and safer implementation decisions. AI assistance was used solely for learning, conceptual understanding, and validation purposes.