# Desciption
This is a mini linix shell in C, Ansi-style

# included files
- linux.c

# How to run the code?
1. Download the file or make a file and copy the code in that text file and save that file with ./ extension.

2. gcc filename.c -o filename

3. ./filename

# What this code does?

1. C code implementation of cd, ls, exit, pwd.
2. Rest all basic commands implementation similar to terminal.
3. Parse the commands
4. Execute Built in commands
5. cd, ls, pwd, exit, mkdir etc
6. ? Wild card expansion

# Part 1 - Parser
1. It takes in a line of code (READ)
2. Parses the command (EVALUATES)
3. Then executes the command and its arguments (PRINT output)
4. Loops and then prints out any output. (LOOP)

The first token will be the command
The second through N number of tokens will be any number of arguments.
(Optionally) The N+1 tokens through M tokens will be another command with arguments.

# Execute Built_in_Commands
1. After pasring it returns the first argument of input which is the command for linux.
2. We pass this command to Built_in_function to execute the commands if it is otherwise it executes all the system commands like mkdir, pwd, cd to root directory etc.

# Extra Commands
1. The use of "?" wildcard expansion
2. if you don't know thw exact name of file so, placing "?" i with ls instead of characters it will return you all the files matching with these wildcard.


