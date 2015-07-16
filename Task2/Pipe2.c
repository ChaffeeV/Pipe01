#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>



int main()
{
	int 	stat;
	int 	fd[2];
	int		i = 0;
	int		j = 0;

	FILE 	*fp;

	char 	*mas;
	char	c;
	size_t	size;
	pid_t 	pid;

	if (pipe(fd) < 0)
	{
		printf ("Can't create pipe\n");
		exit(-1);
	}

	pid = fork();
	if (pid == -1)
	{
		printf ("some error happened\n");
		exit(1);
	}

	else if (pid == 0)
	{
		close(fd[0]);

		freopen ("OUTPUT", "w", stdout);
		system ("ls -l");

		fp = fopen("OUTPUT", "r");

		while((c = getc(fp)) != EOF)
			i++;

		mas = malloc(i);
		i = 0;

		fseek (fp, 0, SEEK_SET);

		while ((c = getc(fp)) != EOF)
		{
			mas[i] = c;
			i++;
		}

		fclose(fp);
		size = write (fd[1], mas, 2000);

		system("rm -v OUTPUT");
		fclose (stdout);
		close(fd[1]);
		exit(1);
	}
	else
	{
		close(fd[1]);
		size = read(fd[0], mas, 2000);
		if (size < 0)
		{
			printf(" Не могу прочитать\n");
		}
		printf("Родительский процесс. Прочитано байт: %d\n", size);
		printf("%s", mas);
		close(fd[0]);
		exit(1);
	}
	return 0;
}