
#ifndef REDIRECTIONS_H_
# define REDIRECTIONS_H_

# include "21sh.h"

# define TRUE 1
# define FALSE 0

# define NEW_FILE_MODE	S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH

# define SIMPLE_OUTPUT_REDIRECTION ">"
# define APPENDING_OUTPUT_REDIRECTION ">>"
# define INPUT_REDIRECTION "<"
# define CLOSE_DIRECTION '-'

# define STDOUT 1
# define STDERR 2
# define STDIN 0
# define STDOUT_AND_STDERR -1
# define CLOSE_FD -1
# define AMBIGUOUS -2
# define NO_RIGHT_FD 0

typedef                 void(*t_setup_ptr)(t_bash *, t_vect *, t_arg *);

typedef struct			s_redirection_set_up
{
	t_setup_ptr		f;
	char			*operator;
}						t_redirection_set_up;

typedef struct			s_redirection
{
	int						left_fd;
	int						right_fd;
	int						backup_fd;
	char					*operator;
	char					*file_word;
	struct s_redirection	*next;
}						t_redirection;


/*
**	STRUCT
*/

t_redirection   *new_redirection(t_vect *cmd, int default_in, int default_out);
void            free_redirection(t_redirection *redirection);

/*
** SET UP
*/

void            initialize_redirection_set_up_functions(t_bash *data);
void            search_redirections_in_cmd(t_vect *cmd, t_bash *data);


/*
**  TOOLS
*/

int             search_left_fd(t_bash *data, t_arg *arg, int operator_index, int default);
int             search_right_fd(t_bash *data, char *substring);
char            *search_file_word(t_bash *data, t_arg *arg, int substring_index);
int     		is_stdout_and_stderr_redirection(left_fd, right_fd)
void		    set_up_stdout_and_stderr_redirection(t_bash *data, t_vect *cmd, t_arg *arg, int substring_index)

/*
** EXECUTION
*/

bool            handle_redirections(t_redirection *redirection, int position);
void            restore_directions(t_redirection *redirection);

#endif