# Minishell
* Minishell with Dimitris
---
### Bash Reference Manual
[Bash Manual - GNU](https://www.gnu.org/software/bash/manual/bash.html)
---
### Limitations

While `minishell` aims to replicate essential features of `bash`, its behavior is intentionally restricted to meet the scope of the subject.
Only specific functionalities are required and implemented, such as basic quoting, redirections, pipes, environment variable expansion, and a minimal set of built-in commands.
Advanced features like job control, command substitution, process groups, or extended globbing are out of scope. Additionally, only one global variable (for signal handling) is allowed, limiting inter-process state tracking. Our implementation also uses `/proc/self/stat` to introspect process-related metrics and `/dev/urandom` to generate randomness where needed; however, portability is constrained to Unix-like systems with a working `/proc` and `/dev` filesystem.
These limitations reflect both project constraints and OS-specific dependencies, and are not intended to fully emulate a production-ready shell like `bash`.

### How to install and use

#### 🔧 Installation

1. **Clone the repository:**
   ```bash
   git clone git@github.com:ThiwankaS/Minishell.git && cd Minishell
   ```
   
2. **Build the project:**
   ```bash
   make
   ```
   This will compile the `minishell` executable using the provided `Makefile`. Make sure your system has a C compiler (`cc`) and `readline` development libraries installed.

#### ▶️ Running Minishell

To start the shell, simply run:
```bash
./minishell
```
You will see a custom prompt indicating that the shell is waiting for input. You can now execute built-in commands (`cd`, `echo`, `pwd`, etc.) and external programs (like `/bin/ls`, `cat`, etc.).

#### ⌨️ Keyboard Shortcuts

- `Ctrl-C`: Interrupts the current command and shows a new prompt.
- `Ctrl-D`: Exits the shell.
- `Ctrl-\`: Does nothing (ignored, like in `bash`).

#### 💡 Notes

- The shell supports basic features such as pipelines (`|`), redirections (`>`, `<`, `>>`, `<<`), and environment variable expansion (`$VAR`, `$?`).
- Only the features specified in the subject are implemented; anything beyond that may not work or is deliberately excluded.

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

#### 02). `add_history`
```c
void add_history(const char *line);
```
The `add_history` function is also part of the GNU Readline library and is used to add a line of input to the history list.

#### 03). `rl_clear_history`
```c
void rl_clear_history(void);
```
The `rl_clear_history` function in C is part of the GNU Readline library. It's used to clear the entire input history that Readline maintains — for example, the lines you've entered during an interactive session

#### 04). `rl_on_new_line`
```c
int rl_on_new_line(void);
```
Tells Readline that the cursor is on a new line, so it's ready to redraw the prompt and the current input line correctly. Returns `0` on success, `-1` if the internal line state is invalid (e.g. `rl_line_buffer` is `NULL`).

#### 05). `rl_replace_line`
```c
void rl_replace_line(const char *text, int clear_undo);
```
The `rl_replace_line` function from the GNU Readline library is used to replace the current input line with a new string — without affecting the command history.
* `text`: The new string to use as the input line
* `clear_undo`: If non-zero, clears the undo list

It changes what the user sees as the current line in the terminal.
#### 06). `rl_redisplay`
```c
void rl_redisplay(void);
```
The `rl_redisplay` function is part of the GNU Readline library, and it’s used to redraw the prompt and current input line on the screen. Forces Readline to refresh the current input line and prompt display.
After making changes to the input buffer (e.g. with `rl_replace_line`), or when terminal output messes up the current input display.

#### 07). `getcwd`
```c
char *getcwd(char *buf, size_t size);
```
The `getcwd` function in C is used to get the current working directory of the calling process.
* buf: A pointer to a buffer where the path will be stored.
* size: The size (in bytes) of that buffer.
Returns: A pointer to `buf` on success, or `NULL` on failure (e.g. if the buffer is too small). If you want `getcwd` to allocate memory for you (POSIX extension), pass `NULL` for `buf` and `0` for `size`.

#### 08). `chdir`
```c
int chdir(const char *path);
```
The chdir() function in C is used to change the current working directory of the running process.
* `path`: A string representing the new directory path.
Returns `0` on success `-1` on failure (and sets errno).

#### 09). `stat`
```c
int stat(const char *pathname, struct stat *statbuf);
```
The stat() function in C is used to get information about a file or directory — like its size, permissions, timestamps, and more.
* `pathname`: Path to the file or directory.
* `statbuf`: Pointer to a struct stat where the info will be stored.
Returns, `0` on success, `-1` on failure, and sets errno.

```c
struct stat
```
– Key Fields

* `st_mode`	File type and permissions
* `st_size`	File size in bytes
* `st_uid`	User ID of owner
* `st_gid`	Group ID of owner
* `st_mtime`	Time of last modification
* `st_ctime`	Time of last status change
* `st_atime`	Time of last access

#### 10). `lstat`
```c
int lstat(const char *pathname, struct stat *statbuf);
```
The `lstat` function in C is very similar to stat(), but with one key difference: `lstat` does not follow symbolic links, while `stat` does. In writing a tool like `ls -l` or `find`, and want to list symlinks without resolving them, use `lstat`.

#### 11). `fstat`
```c
int fstat(int fd, struct stat *statbuf);
```
The `fstat` function in C is used to get file information from an open file descriptor, instead of a file path.
* `fd`: A file descriptor (from open(), fileno(), pipe(), etc.).
* `statbuf`: A pointer to a struct stat that will be filled with file info.
Returns `0` on success. `-1` on failure (check errno).

#### 12). `unlink`
```c
int unlink(const char *pathname);
```
The `unlink` function in C is used to delete (remove) a file from the filesystem.`unlink` only removes the name from the directory. The file's contents are deleted only when no process has it open and there are no other links to it. Works like `rm` command in the shell.

#### 13). `execve`
```c
int execve(const char *pathname, char *const argv[], char *const envp[]);
```
The `execve` function in C is a low-level system call that replaces the current process image with a new program — meaning it starts another program and never returns (unless there’s an error).
* `pathname`	Full path to the executable file (e.g., /bin/ls)
* `argv[]`	Null-terminated array of argument strings. argv[0] should be the program name.
* `envp[]`	Null-terminated array of environment variables (like PATH, HOME, etc.)

#### 14). `dup`
```c
int dup(int oldfd);
```
The dup() function in C is used to duplicate a file descriptor. It creates a copy of an existing file descriptor that refers to the same open file or resource.
* `oldfd` : An existing (open) file descriptor (e.g., for a file, pipe, or socket).
Returns, A new file descriptor with the lowest unused number on success or `-1` on failure (and sets errno).

#### 15). `dup2`
```c
int dup2(int oldfd, int newfd);
```
The dup2() function in C is used to duplicate a file descriptor into a specific file descriptor number, often for I/O redirection (like redirecting stdout to a file).
* `oldfd`	The original file descriptor you want to duplicate
* `newfd`	The desired file descriptor number to copy into (e.g., STDOUT_FILENO)
If newfd is already open, it is closed automatically before being reused. `dup2()` is perfect for redirecting standard input/output/error (STDIN_FILENO, STDOUT_FILENO, STDERR_FILENO).
If `oldfd == newfd`, `dup2()` does nothing and returns newfd. If newfd was already open, it will be safely closed first (to avoid leaks).
Returns the new file descriptor (newfd) on success, or `-1` on error.

#### 16). `pipe`
```c
int pipe(int pipefd[2]);
```
The pipe() function in C is used to create a unidirectional communication channel between processes — usually between a parent and child process.
It provides inter-process communication (IPC) via file descriptors: one for reading, one for writing.
pipefd: An array of two integers:
* `pipefd[0]`: Read end
* `pipefd[1]`: Write end
Returns: `0` on success `-1` on failure (and sets errno).

#### 17). `opendir`
```c
DIR *opendir(const char *name);
```
* `name` : Path to the directory (e.g., "." for the current directory).
Returns, A pointer to a `DIR structure` (directory stream) on success.`NULL` on failure (check errno for details).

```c
struct dirent
```
- Key Fields
* `d_name`	Name of the file (string)
* `d_type`	Type of file (if available, e.g. regular file, dir)

#### 18). `readdir`
```c
struct dirent *readdir(DIR *dirp);
```
The `readdir` function in C is used to read entries from an open directory stream, one at a time. It's commonly used after `opendir` to list files and subdirectories.
* `dirp` : A pointer to a DIR object returned by `opendir`.
Returns, A pointer to a `struct dirent` representing the next directory entry. `NULL` when there are no more entries (or on error).

#### 19). `closedir`
```c
int closedir(DIR *dirp);
```
The `closedir` function in C is used to close a directory stream that was opened with `opendir`.
* `dirp` : A pointer to a DIR object (returned by `opendir`).
Returns `0` on success `-1` on failure (and sets errno).

#### 20). `strerror`
```c
char *strerror(int errnum);
```
The `strerror` function in C is used to convert an error number (errno) into a human-readable error message — like "Permission denied" or "No such file or directory".
errnum: An error number, usually obtained from the global variable errno (set by functions like open(), read(), execve(), etc.).
`strerror` returns a pointer to a static string, so don’t modify or free it.

#### 21). `perror`
```c
void perror(const char *s);
```
The `perror` function in C is used to print a descriptive error message to stderr, based on the current value of the global variable errno.
* `s`: A custom message you want to prefix the error with (like the function name or context).

#### 22). `isatty`
```c
int isatty(int fd);
```
The `isatty` function in C is used to check if a file descriptor refers to a terminal (TTY).
* `fd`: A file descriptor (e.g. STDIN_FILENO, STDOUT_FILENO, or any open file descriptor).
Returns, `1` (true) if the file descriptor is connected to a terminal device. `0` (false) if not (and sets errno).

#### 23). `ttyname`
```c
char *ttyname(int fd);
```
The `ttyname` function in C is used to get the name of the terminal (TTY) device associated with a given file descriptor.
* `fd` : A file descriptor (e.g., `STDIN_FILENO`, `STDOUT_FILENO`, etc.).
Returns, A pointer to a string containing the terminal device name (like /dev/tty1 or /dev/pts/0) on success.`NULL` on
failure (e.g. if fd is not a terminal), and sets errno.

#### 24). `ttyslot`
```c
int ttyslot(void);
```
The `ttyslot` function in C is used to get the slot number of the terminal in the system's terminal database (usually /etc/ttys or /etc/utmp).
It helps identify which terminal device a user is connected to.

#### 25). `ioctl`
```c
int ioctl(int fd, unsigned long request, ...);
```
The ioctl() function in C is a powerful, low-level system call used to perform device-specific input/output operations on file descriptors — often terminals,
sockets, or special devices.
* `fd`	File descriptor (e.g., terminal, socket, file)
* `request`	Device-specific control code (macro like TIOCGWINSZ, FIONREAD, etc.)
* `...`	Optional third argument — a pointer to data to send/receive. Returns `0` on success, `-1` on failure (sets errno).

#### 26). `getenv`
```c
char *getenv(const char *name);
```
The `getenv()` function in C retrieves the value of an environment variable specified by name. It returns a pointer to the value string if the variable exists, or `NULL` if it is not found. The returned string must not be modified. This function is commonly used to access variables like `PATH`, `HOME`, or `USER` from the environment.

#### 27). `tcsetattr`
```c
int tcsetattr(int fd, int optional_actions, const struct termios *termios_p);
```
The `tcsetattr` function sets terminal attributes for the terminal referred to by the file descriptor fd. The optional_actions argument determines when the changes take effect (`TCSANOW`, `TCSADRAIN`, or `TCSAFLUSH`), and termios_p is a pointer to a termios structure containing the new terminal settings. It returns `0` on success and `-1` on failure, setting errno accordingly.

#### 28). `tcgetattr`
```c
int tcgetattr(int fd, struct termios *termios_p);
```
The `tcgetattr` function retrieves the current terminal attributes for the terminal referred to by the file descriptor `fd` and stores them in the structure pointed to by `termios_p`. It is commonly used before modifying terminal settings with `tcsetattr`. Returns `0` on success and `-1` on failure, setting `errno` accordingly.

#### 29). `tgetent`
```c
int tgetent(char *bp, const char *name);
```
The `tgetent` function loads the terminal entry for the terminal type specified by `name` from the termcap database and stores it in the buffer `bp`. If `bp` is `NULL`, a default internal buffer is used. Returns `1` if the terminal type was found, `0` if it was not found, and `-1` if the database could not be accessed.

#### 30). `tgetflag`
```c
int tgetflag(const char *id);
```
The `tgetflag` function retrieves the boolean value of a terminal capability specified by the two-character identifier `id` from the termcap database. It returns `1` if the capability is present, `0` if not, and `-1` if an error occurs or the capability is unknown.

#### 31). `tgetnum`
```c
int tgetnum(const char *id);
```
The `tgetnum` function retrieves the numeric value of a terminal capability specified by the two-character identifier `id` from the termcap database. It returns the value as an `int` if the capability exists, `-1` if the capability is not available or an error occurs.

#### 32). `tgetstr`
```c
char *tgetstr(const char *id, char **area);
```
The `tgetstr()` function retrieves the string value of a terminal capability specified by the two-character identifier `id` from the termcap database. The resulting string is stored in the buffer pointed to by `*area`, which is updated to point past the end of the stored string. Returns a pointer to the string if found, or `NULL` if the capability does not exist or an error occurs.

#### 33). `tgoto`
```c
char *tgoto(const char *cap, int col, int row);
```
The `tgoto()` function generates a cursor movement string based on the capability string `cap`, typically obtained from `tgetstr()`, and the target column `col` and row `row`. It returns a pointer to the resulting string that can be output to move the cursor accordingly. If an error occurs, it returns a string that may not be meaningful.

#### 34). `tputs`
```c
int tputs(const char *str, int affcnt, int (*putc)(int));
```
The `tputs()` function outputs a string containing terminal control codes, typically obtained via `tgetstr()` or `tgoto()`. The `str` argument is the control string, `affcnt` is the number of affected lines (used for padding), and `putc` is a function to output each character (usually `putchar`). Returns `0` on success or a non-zero value if an error occurs during output.

#### 35). `access`
```c
int access(const char *pathname, int mode);
```
The `access()` function checks a file's accessibility based on the calling process's real user and group IDs. The `pathname` is the file to check, and `mode` is a bitmask of permissions to test (`R_OK`, `W_OK`, `X_OK`, or `F_OK` to check existence). Returns `0` if the requested access is permitted, or `-1` if it is not, setting `errno` accordingly.

#### 36). `open`
```c
int open(const char *pathname, int flags, mode_t mode);
```
Parameters:
  * pathname: The path to the file you want to open.
  * flags: These are options that define the behavior of the open operation (e.g., ```O_RDONLY```, ```O_WRONLY```, ```O_RDWR```, ```O_CREAT```).
  * mode: The file permission settings, required when creating a new file (typically used with ```O_CREAT```). It's given in octal format (e.g., 0644).
Return value:
  On success, it returns a file descriptor (a non-negative integer).
  On failure, it returns -1, and errno is set to indicate the error.

#### 37). `read`
```c
ssize_t read(int fd, void *buf, size_t count);
```
The `read()` function attempts to read up to `count` bytes of data from the file descriptor `fd` into the buffer `buf`. It returns the number of bytes actually read (`0` indicates end-of-file), or `-1` on error, setting `errno` accordingly.

#### 38). `close`
```c
int close(int fd);
```
The `close()` function closes the file descriptor `fd`, releasing any system resources associated with it. Once closed, the file descriptor can no longer be used. Returns `0` on success, or `-1` on failure, setting `errno` accordingly.

#### 39). `fork`
```c
pid_t fork(void);
```
The `fork()` function creates a new process by duplicating the calling process. The new process (child) is an exact copy of the calling process (parent), except for the returned value. Returns `0` in the child process, the child's PID in the parent process, or `-1` on failure, setting `errno` accordingly.

#### 40). `wait`
```c
pid_t wait(int *wstatus);
```
The `wait()` function suspends execution of the calling process until one of its child processes terminates. If `wstatus` is not `NULL`, it stores the exit status of the terminated child. Returns the PID of the terminated child on success, or `-1` on failure (e.g., no child processes), setting `errno` accordingly.

#### 41). `waitpid`
```c
pid_t waitpid(pid_t pid, int *wstatus, int options);
```
The `waitpid()` function suspends execution of the calling process until the specified child process (`pid`) changes state. The `pid` can be a specific process ID, `-1` to wait for any child, or other special values. The `wstatus` stores the exit status if not `NULL`, and `options` can modify behavior (e.g., `WNOHANG`, `WUNTRACED`). Returns the PID of the child that changed state, `0` if `WNOHANG` is set and no child has exited, or `-1` on failure, setting `errno`.

#### 42). `wait3`
```c
pid_t wait3(int *wstatus, int options, struct rusage *rusage);
```
The `wait3()` function suspends execution of the calling process until one of its child processes exits or a signal is received. It behaves like `waitpid(-1, wstatus, options)` but also provides resource usage information in the `rusage` structure if it is not `NULL`. Returns the PID of the terminated child, `0` if `WNOHANG` is specified and no child has exited, or `-1` on failure, setting `errno`.

#### 43). `wait4`
```c
pid_t wait4(pid_t pid, int *wstatus, int options, struct rusage *rusage);
```
The `wait4()` function is similar to `waitpid()` but additionally provides resource usage information for the terminated child process in the `rusage` structure. The `pid` specifies which child to wait for, `wstatus` stores the exit status, and `options` can modify behavior (e.g., `WNOHANG`, `WUNTRACED`). Returns the PID of the child that changed state, `0` if `WNOHANG` is set and no child has exited, or `-1` on failure, setting `errno`.

#### 44). `signal`
```c
__sighandler_t signal(int signum, __sighandler_t handler);
```
The `signal()` function sets a handler function for a specific signal `signum` (e.g., `SIGINT`, `SIGTERM`). The `handler` can be a function pointer to a custom handler, or the constants `SIG_IGN` (ignore) or `SIG_DFL` (default action). Returns the previous signal handler on success, or `SIG_ERR` on failure, setting `errno` accordingly.

#### 45). `sigaction`
```c
int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
```
The `sigaction()` function allows precise control over the handling of signals. It sets a new action for the signal `signum` using the `act` structure, and optionally stores the previous action in `oldact` if it is not `NULL`. This function is preferred over `signal()` for reliable and portable signal handling. Returns `0` on success, or `-1` on failure, setting `errno` accordingly.

#### 46). `sigemptyset`
```c
int sigemptyset(sigset_t *set);
```
The `sigemptyset()` function initializes the signal set pointed to by `set`, clearing all signals from it. This means the set will contain no signals after the call. It is typically used before adding specific signals to the set. Returns `0` on success, or `-1` on failure, setting `errno` accordingly.

#### 47). `sigaddset`
```c
int sigaddset(sigset_t *set, int signum);
```
The `sigaddset()` function adds the signal `signum` to the signal set pointed to by `set`. This is used to build a set of signals for blocking or handling operations. Returns `0` on success, or `-1` on failure, setting `errno` accordingly.

#### 48). `kill`
```c
int kill(pid_t pid, int sig);
```
The `kill()` function sends the signal `sig` to the process specified by `pid`. If `pid` is greater than `0`, the signal is sent to that specific process. Special values like `0`, `-1`, or negative group IDs can target process groups or all processes the caller has permission to signal. Returns `0` on success, or `-1` on failure, setting `errno` accordingly.

#### 49). `exit`
```c
void exit(int status);
```
The `exit()` function terminates the calling process immediately, returning the exit `status` to the parent process. It performs cleanup operations such as flushing standard I/O buffers and calling functions registered with `atexit()`. The `status` code is typically used to indicate success (`0`) or failure (non-zero).

#### 50). `printf`
```c
int printf(const char *format, ...);
```
`printf` prints formatted output to the standard output (usually the terminal).

#### 51). `malloc`
```c
void *malloc(size_t size);
```
`malloc` in C is used to dynamically allocate memory at runtime from the heap.

#### 52). `free`
```c
void free(void *ptr);
```
The `free` function in C is used to deallocate memory that was previously allocated with `malloc`, `calloc`, or `realloc`. It's essential for preventing memory leaks.

#### 53). `write`
```c
ssize_t write(int fd, const void *buf, size_t count);
```
The `write()` function writes up to `count` bytes from the buffer `buf` to the file descriptor `fd`. It returns the number of bytes actually written, which may be less than `count`, or `-1` on failure, setting `errno` accordingly.
