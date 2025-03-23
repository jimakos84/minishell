# minishell
Minishell with Thiwnaka

---

### Proper Implementation of a Shell
[Build Your Own Shell - Codecrafters](https://github.com/codecrafters-io/build-your-own-x?tab=readme-ov-file#build-your-own-shell)

---

### Minishell Example Projects
- [cclaude42/minishell](https://github.com/cclaude42/minishell)
- [mcombeau/minishell](https://github.com/mcombeau/minishell)

---

### Bash Reference Manual
[Bash Manual - GNU](https://www.gnu.org/software/bash/manual/bash.html)

---

### Allowed Functions

#### 01). `readline`
```c
char *readline (char *prompt);
```

So, exapmle of using the function
```c
char *line = readline("Enter a line: ");
```
`readline` returns the text of the line read.  A blank line returns the empty string.  If `EOF` is encountered while reading a line, and the line is empty, `NULL` is returned.  If an `EOF` is read with a non-empty line, it is treated as a newline.


#### rl_clear_history
#### rl_on_new_line
#### rl_replace_line
#### rl_redisplay
#### add_history
#### printf
#### malloc
#### free
#### write
#### access
#### open
#### read,
#### close
#### fork
#### wait
#### waitpid
#### wait3
#### wait4
#### signal
#### sigaction
#### sigemptyset
#### sigaddset
#### kill
#### exit,
#### getcwd
#### chdir
#### stat
#### lstat
#### fstat
#### unlink
#### execve
#### dup
#### dup2
#### pipe
#### opendir
#### readdir
#### closedir
#### strerror
#### perror
#### isatty
#### ttyname
#### ttyslot
#### ioctl
#### getenv
#### tcsetattr
#### tcgetattr
#### tgetent
#### tgetflag
#### tgetnum
#### tgetstr
#### tgoto
#### tputs
