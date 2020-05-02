# add_signals_handling commit

## 21sh.h
* add 
> void set_up_signals();

## main
* call set_up_signals() in main function or during setup process

## Makefile
* add signals.c

## Ideas
* add a libft function that takes two string as arguments : string to write and macro-string for color

# handle_execution_redirections commit

## 21sh.h
> #include "redirections.h"
* in s_vect, add
> t_redirection		*redirections;
* in s_bash, add
> t_redirection_set_up *redirections_set_up;
* in s_bash change char *error; to char error[256] ans readapt your use of error in the rest of the code
* rename
> exec_cmd -> handle_fork
* declare
> int fork_failed(pid_t pid);
> int is_child(pid_t pid);

## Other Updates
* add free_redirections to free_vect

## Makefile
* add redirections_execution.c
* add redirections_setup.c
* add redirections_struct.c
* add redirections_tools.c
* add functions_not_macros.c

## Not forget to
* Set all concerned functions as static
* change error formating
* change return values for explicit MACROs
* handle execve errors
* handle dup2 errors
* properly wrap open used in exec.c/is_out_fd_authorized
* handle close errors
* learn more about usable fd to make our backups
* handle wait status
* handle malloc failures
* check files header!