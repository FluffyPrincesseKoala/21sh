
## Main
* build sub main for unit test :
	- use double quotes to exec cmd
	````./21sh "ls -lra" "echo $PATH"````
	- cmd are executed argv by argv using same env
* add file compatibility to sub-main
* add posibility to save or not the env like
`` ./21sh --save-env "setenv PATH=$PATH:foo/bar"	``


## Ideas
* add a libft function that takes two string as arguments : string to write and macro-string for color
* add scrolling
* function typed "in" to return true/false -> tinier int

## Cleaning
* rename findenv -> get_var_from_env

## Not forget to
* readapt the use of data->error
* Set all concerned functions as static
* change error formating
* change return values for explicit MACROs
* handle execve errors
* handle dup2 errors
* properly wrap open used in exec.c/is_file_word_authorized
* handle close errors
* learn more about usable fd to make our backups
* handle wait status
* handle malloc failures -> think about libft calls !
* check files header!
