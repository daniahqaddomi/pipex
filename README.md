# Pipex

**Pipex** is a project written in C that simulates the behavior of a shell pipeline. It allows you to execute multiple commands with input/output redirection and piping between them.

## What I Did
- Used **fork()** to create child processes for executing commands.
- Implemented **inter-process communication** by passing data through pipes.
- Managed **file redirection** to read input from a file and write output to another.
- Handled various **edge cases**, such as invalid commands, permissions, and missing files.
  
## Example Usage
```sh
make        # To compile the project
./pipex file1 "command1" "command2" file2  # Execute a pipeline from file1 through two commands to file2
make clean  # To remove compiled files

