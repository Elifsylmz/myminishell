*This project has been created as part of the 42 curriculum by eyilmaz, facelik.*

# Minishell

## Description

Minishell is a simple Unix shell implementation written in C.

The goal of this project is to recreate the basic behavior of a shell, similar to Bash, within the scope required by the 42 curriculum. The program reads user input, parses commands, handles redirections and pipes, expands environment variables, executes external commands, and implements several built-in commands.

This project helped us understand important system programming concepts such as process creation, file descriptor management, environment handling, signal behavior, and command execution.

The shell supports:

- Command execution using `PATH`
- Built-in commands: `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`
- Pipes with `|`
- Input, output and append redirections with `<`, `>` and `>>`
- Heredoc with `<<`
- Environment variable expansion with `$VAR`
- Last exit status expansion with `$?`
- Single and double quote handling
- Basic signal handling

This project does not aim to be a complete Bash replacement. It focuses on the required features of the Minishell subject.

## Instructions

### Compilation

To compile the project, run:

```bash
make
```

This will create the executable:

```bash
./minishell
```

To remove object files:

```bash
make clean
```

To remove object files and the executable:

```bash
make fclean
```

To rebuild the project:

```bash
make re
```

### Execution

After compilation, run:

```bash
./minishell
```

Example usage:

```bash
minishell$ echo hello world
hello world
```

Example with redirection:

```bash
minishell$ echo hello > file.txt
minishell$ cat < file.txt
hello
```

Example with a pipe:

```bash
minishell$ ls | wc -l
```

Example with environment variable expansion:

```bash
minishell$ echo $HOME
/home/user
```

To exit the shell:

```bash
minishell$ exit
```

You can also exit with `Ctrl-D`.

## Resources

The following resources were used to understand shell behavior and system programming concepts:

- Bash manual  
  https://www.gnu.org/software/bash/manual/bash.html

- POSIX Shell Command Language  
  https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html

- GNU Readline documentation  
  https://tiswww.case.edu/php/chet/readline/readline.html

- Linux manual pages for system calls such as `fork`, `execve`, `pipe`, `dup2`, `waitpid`, and `signal`

- 42 Minishell subject

AI was used as a support tool during the project, mainly for understanding shell concepts, reviewing edge cases, and organizing documentation.

AI was also used to better understand and review topics such as parsing, execution, built-ins, redirections, heredocs, signals, and environment expansion. The final implementation, debugging, testing, and project decisions were made by the project authors.
