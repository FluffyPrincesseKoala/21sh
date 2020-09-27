# add_signals_handling commit

## Makefile
* add signals.c
* add unit test rules with their own main

## 21sh.h
* add 
> void set_up_signals();

## Main
* call set_up_signals() in main function or during setup process
* build sub main for unit test

## Ideas
* add a libft function that takes two string as arguments : string to write and macro-string for color