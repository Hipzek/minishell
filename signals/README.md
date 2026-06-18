*This project has been created as part of the 42 curriculum by hbekka and hbelleuv.*

# Minishell

## Description

Minishell is a simplified Unix shell written in C as part of the 42 curriculum. The goal of this project is to reproduce the core behavior of Bash while gaining a better understanding of process management, file descriptors, signals, environment variables, and command execution.

The shell provides an interactive prompt where users can execute commands, use pipes and redirections, expand environment variables, and run built-in commands.

### Features

- Interactive command prompt
- Built-in commands:
  - `echo`
  - `cd`
  - `pwd`
  - `export`
  - `unset`
  - `env`
  - `exit`
- Execution of external commands
- Environment variable expansion (`$VAR`)
- Exit status expansion (`$?`)
- Pipes (`|`)
- Input redirection (`<`)
- Output redirection (`>`)
- Append redirection (`>>`)
- Here-document (`<<`)
- Signal handling (`Ctrl-C`, `Ctrl-D`, `Ctrl-\`)
- Command history with Readline

## Instructions

### Requirements

- CC
- Readline library

### Compilation

```bash
make
make re
```

### Execution

```bash
./minishell
```

### Cleaning

```bash
make clean
make fclean
```

### Example Usage

```bash
minishell$ echo Hello World
Hello World

minishell$ ls -l | grep minishell

minishell$ export USER42=student
minishell$ echo $USER42
student

minishell$ cat < infile.txt > outfile.txt
```

### Memory Checking

To avoid false-positive memory leak reports caused by the Readline library, a suppression file can be used with Valgrind:

```bash
valgrind --leak-check=full \
         --show-leak-kinds=all \
         --track-fds=yes \
         --suppressions=readline.supp \
         ./minishell
```

## Resources

### Documentation

- GNU Bash Manual  
  https://www.gnu.org/software/bash/manual/bash.html

- Readline Documentation  
  https://tiswww.case.edu/php/chet/readline/rltop.html

- Linux Manual Pages  
  https://man7.org/linux/man-pages/

### Additional References

- Writing Your Own Shell  
  https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf

- Advanced Bash-Scripting Guide  
  https://tldp.org/LDP/abs/html/

### Usage of AI

Artificial Intelligence tools were used as supplementary learning resources during the development of this project.

AI assistance was mainly used for:

- Understanding shell concepts and architecture
- Clarifying documentation and system calls
- Exploring edge cases related to parsing and signal handling
