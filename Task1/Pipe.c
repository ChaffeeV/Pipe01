#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(){
	pid_t pid;
	int fd[2];
	size_t size;
	char string[14];
	if (pipe(fd) < 0){
		printf ("Can't create pipe\n");
		exit(-1);
	}
	pid = fork();
	if (pid == -1){
		printf ("some error happened\n");
		exit(-1);
	}
	else if (pid == 0){
		printf("Дочерний процесс. Введите строку:");
		close(fd[0]);
		gets(string);
		size = write (fd[1], string, 14);
		if (size != 14){
			printf("Маленькая строка");
		}
		close(fd[1]);
		exit(-1);
	}
	else{
		int stat;
		wait(&stat);
		close(fd[1]);
		size = read(fd[0], string, 14);
		if (size<0){
			printf(" Не могу прочитать\n");
		}
		printf("Родительский процесс. Введенная строка: %s\n", string);
		close(fd[0]);
	}
	return 0;
}

		

	
