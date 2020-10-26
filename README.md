# add_signals_handling commit

## Makefile
* add signals.c
* add unit test rules with their own main

## 21sh.h
* add
> void set_up_signals();

## Main
* call set_up_signals() in main function or during setup process
* build sub main for unit test :
	- use double quotes to exec cmd
	````./21sh "ls -lra" "echo $PATH"````
	- cmd are executed argv by argv using same env
* add file compatibility to sub-main
* add posibility to save or not the env like
`` ./21sh --save-env "setenv PATH=$PATH:foo/bar"	``


## Ideas
* add a libft function that takes two string as arguments : string to write and macro-string for color