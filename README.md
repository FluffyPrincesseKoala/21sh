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
> #define   NEW_FILE_MODE   S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH
* add structure
> typedef struct			s_redirection \
> { \
> 	int					    in_fd; \
> 	int					    out_fd; \
> 	int					    backup_fd; \
> 	char				    *opened_file;\
>   struct s_redirection	*next;\
> }						t_redirection
* in s_vect, add
> t_redirection		*redirections;
* in function declarations
> bool fork_failed(pid_t pid); \
> bool is_child(pid_t pid); \
> bool handle_redirections(t_redirection *redirection, int position); \
> void restore_directions(t_redirection *redirection);
* rename
> exec_cmd -> handle_fork

## Makefile
* add signals.c
* add functions_not_macros.c

## Not forget to
* add free_redirections to free_vect
* handle execve errors
* handle dup2 errors
* properly wrap open used in exec.c/is_out_fd_authorized
* handle close errors
* learn more about usable fd to make our backups
* handle wait status
* handle mallocs failure