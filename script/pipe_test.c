# include <stdlib.h>
# include <unistd.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/time.h>
# include <sys/resource.h>

# include <signal.h>
# include <sys/ioctl.h>
# include <stdio.h>
#include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
#define MSGSIZE 16 
char* msg1 = "hello, world #1"; 
char* msg2 = "hello, world #2"; 
char* msg3 = "hello, world #3"; 
  
int main() 
{ 
	char **cat;
	char **wc;
	pid_t	cpid;
	int		pipefd[2];

	cat = malloc(sizeof(char*) * 3);
	cat[0] = strdup("cat");
	cat[1] = strdup("update_changed.sh");
	cat[2] = NULL;

	wc = malloc(sizeof(char*) * 2);
	wc[0] = strdup("wc");
	wc[1] = NULL;

	if (pipe(pipefd) == -1)
		return (-1);
	if ((cpid = fork()) == 0)
	{
		//child
		close(pipefd[0]);
		dup2(pipefd[1], 1);
	//	close(pipefd[1]);
		execve("/bin/cat", cat, NULL);
		exit(1);
	}
	else
	{
		close(pipefd[1]);
		dup2(pipefd[0], 0);
	//	close(pipefd[0]);
		execve("/usr/bin/wc", wc, NULL);
		wait(NULL);
	}

	return (0);
} 