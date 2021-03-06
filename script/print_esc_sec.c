#include <stdio.h>
#include <unistd.h>
#include "../includes/vingt_et_un_sh.h"

/*
* SIGINT signal interrupts process 
*/
static void sigint_handler(int sig)
{
    signal(sig, sigint_handler);
}

/*
* SIGSTP signal suspends process
*/
static void sigtstp_handler(int sig)
{
    signal(sig, sigtstp_handler);
}

/*
* SIGCHLD signal is sent to parent process when child process dies
*/
static void sigchld_handler(int sig)
{
    // ft_putendl(RED);
    // ft_putendl("It's over now");
    // ft_putendl(RESET);
    signal(sig, sigchld_handler);
}

void        setup_signals()
{
    signal(SIGINT, sigint_handler);
    signal(SIGTSTP, sigtstp_handler);
    signal(SIGCHLD, sigchld_handler);
}

int main(void){
	char buff[8];
	setup_signals();
	while (42)
	{
		read(0, buff, 8);
		printf("%s\n", buff);
	}
	return (0);
}