# add_signals_handling commit

## 21sh.h
* add 
> void set_up_signals();

## main
* call set_up_signals() in main function or during setup process

## Ideas
* add a libft function that takes two string as arguments : string to write and macro-string for color

# handle_execution_redirections commit

## 21sh.h
* in s_vect, add
> 	int				*redirections[2];
* in function declarations
> bool fork_failed(pid_t pid);
> bool is_child(pid_t pid);
* rename
> exec_cmd
* into
> handle_fork

## Makefile
* add signals.c
* add functions_not_macros.c

## Not forget
* to handle execve errors
* to handle dupe errors
