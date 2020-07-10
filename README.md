# add_signals_handling commit

## Main
* call set_up_signals() in main function or during setup process
* build sub main for unit test

## Ideas
* add a libft function that takes two string as arguments : string to write and macro-string for color

# handle_execution_redirections commit


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
* handle malloc failures
* check files header!