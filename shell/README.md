# Theory of OS Shell

## Building

To build, run make in your shell.

```shell
make
```

There is no separate debug and release versions in this shell

## Usage

To run the shell

```
sh$ ./sesh
$ 
```

To run commands, it also searches the PATH

```
$ /bin/ls
hello
$ ls
hello
$ ./hello
Hello, world!
```

When programs returns a non-zero exit code, it prints it out

```
$ false
program terminated with exit code: 1
```

To exit, run the built-in command exit, EOF also works

```
$ exit
sh$
```

## Progress

### Part 1

- [x] prints a command prompt which is `"$ "` and waits for the user to enter a command

- [x] parse the command using your tokenizer

- [x] create a child process that uses `execve(2)` to run the command with its arguments

- [x] if an absolute path is not specified, your shell should instead find it using the $PATH environment variable

- [x] the parent process should wait for the child to terminate before printing another command prompt.

- [x] print "command not found" if the command is not found

- [x] if the command fails (with a non-zero exit value N), your shell should print "program terminated with exit code: N"

- [x] empty commands should do nothing

- [x] the `exit` command should cause your shell to terminate

### Part 2

- [x] simple commands (e.g. `$ /bin/ls` or `$ ls` )

- [ ] simple pipes (e.g. `$ /bin/ls | /bin/sort -r`)

- [ ] background tasks (e.g. `$ find /etc -print &`)

- [ ] `cd [dir]` for `cd` you will need to lookup the library routine `chdir(2)`

- [ ] redirecting input and output (e.g. `$ ls > /tmp/files.txt`)

- [ ] setting environment variables: `var=value`

- [ ] expanding `~` at the beginning of a parameter

- [ ] expanding non-embedded environment variables (e.g. `echo $PATH`)

- [x] command line editing using ` readline(3)`

- [ ] expanding embedded environment variables (e.g. `echo ${HOME}/bin`)

- [ ] expanding `~` within a parameter (e.g. `ls | dd of=~/files.txt`)

- [ ] programs that cannot be exec'd or terminate with errors (non-zero exit codes) should be reported

