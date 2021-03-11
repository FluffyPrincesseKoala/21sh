
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
* function typed "int" to return true/false -> tinier int

## Not forget to
* fix heredoc_format before using set_heredoc
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
* test 'cat << lol << lol'
* not expand when " ' "

* put one non-static function in each file, organise files in folders


# Pour le 42SH
- Les inhibiteurs ``”`` (double quote), ``’`` (simple quote) et ``\`` (backslash)
- La substitution de commande ``$()``
- La gestion complète de l’historique 
```
!!
!word
!number
!
number
◦La sauvegarde dans un fichier pour être utilisé sur plusieurs sessions
◦Le built-in fc (toutes les options POSIX)
◦Recherche incrémentale dans l’historique avecCTRL-R
```
- Auto Complétion dynamique contextuelle des commandes
- La gestion des alias via les built-ins ``alias`` et ``unalias``

# Error
bad output
**Input**
```
cat << lol ; cat << p
a
lol
1'b'c
p
```
**Output**
```
a
'b'c
```

# Correction
fork
```
srcs/execution/handle_commands.c
```
execve
```
srcs/execution/execute_command/execute_command.c
```