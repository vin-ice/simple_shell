# SIMPLE SHELL
A simple UNIX command interpreter
## Requirements
- Allowed editors: vi, vim, emacs
- All files will be compiled on Ubuntu 20.04 LTS using gcc, using the options -Wall -Werror -Wextra -pedantic -std=gnu89
- All files should end with a new line
- A README.md file, at the root of the folder of the project is mandatory
- Code should use the Betty style. It will be checked using [betty-style.pl](https://github.com/holbertonschool/Betty/blob/master/betty-style.pl) and [betty-doc.pl](https://github.com/holbertonschool/Betty/blob/master/betty-doc.pl).
- Your shell should not have any memory leaks
- No more than 5 functions per file
- All header files should be include guarded
- Use system calls only when you need to ([why?](https://alx-intranet.hbtn.io/rltoken/EU7B1PTSy14INnZEShpobQ)).
- Write a README with the description of your project
- You should have an AUTHORS file at the root of your repository, listing all individuals having contributed content to the repository. Format, see Docker

## Compilation
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
 
 ## Output
 - Unless specified otherwise, your program must have the exact same output as `sh` (`/bin/sh`) as well as the exact same error output.
 - The only difference is when you print an error, the name of the program must be equivalent to your `argv[0]` (See below)
Example of error with `sh`:

```bash
$ echo "qwerty" | /bin/sh
/bin/sh: 1: qwerty: not found
$ echo "qwerty" | /bin/../bin/sh
/bin/../bin/sh: 1: qwerty: not found
$
```

Same error with your program hsh:

```bash
$ echo "qwerty" | ./hsh
./hsh: 1: qwerty: not found
$ echo "qwerty" | ./././hsh
./././hsh: 1: qwerty: not found
$
```

## Files
File | Content
---- | -----------
[main](./shell-main.c) | entry point, executing function
[core](./shell-core.c) | Executes commands passed in by user
[shell.h](./shell.h) | function prototypes, standard libraries, structs
[errors](./errors.c) | error printing functions
[helper_functions](./helper_functions.c) | Utilities for common chores
[strings.c](./strings.c) | Basic string manipulation functions
[env.c](./_env.c) | Handles operations to environement variables