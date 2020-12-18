#include <stdio.h>
#include <unistd.h>

int main(void){
	char buff[8];
	while (42)
	{
		read(0, buff, 8);
		printf("%s\n", buff);
	}
	return (0);
}