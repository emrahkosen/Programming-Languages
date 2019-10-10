#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main( int argc, char *argv[] )
{
	int N = atoi(argv[1]);
	int PipeNumber = 3*N-1;
	int mypipe[PipeNumber][2],pid[2*N];
	int i,j,boyut = 5000;
	char  *gl = (char *) malloc(boyut*sizeof(char));



	if(argv[3] == NULL) //doğru olmayabilir
	{
		for(i = 0; i < N ;i++)
				pipe(mypipe[i]);

		for(i = 0; i < N ; i++ )
		{
			pid[i] = fork();
			if(pid[i] == 0)
			{
			for (j = 0; j < N; j++)
				{
					close(mypipe[j][1]);
					if(j != i)
							close(mypipe[j][0]);
				}
				dup2(mypipe[i][0],0);
				close(mypipe[i][0]);
				execv(argv[2],argv);
				perror("exec error");
				exit(1);
			}
		}
		for (i = 0; i < N; i++)
			close(mypipe[i][0]);
		i = 0;
		while(fgets(gl,boyut,stdin) )
		{
			i++;
			j = ((i-1)%N);
			write(mypipe[j][1],gl,strlen(gl));
		}
		for (i = 0; i < N; i++)
			{close(mypipe[i][1]);}
			wait(NULL);
			free(gl);
		}





		else
		{
			for ( i = 0; i < PipeNumber; i++)
				pipe(mypipe[i]);

			for (i = 0; i < N; i++)  //map process
			{
				pid[i] = fork();
				if(pid[i] == 0) //mapper childs
				{
					for (j = 0; j < PipeNumber; j++)
					{
						if(j != N + i )
							close(mypipe[j][1]); //map dan reducer e giden
						if(j != i)
								close(mypipe[j][0]); // parent den map a giden
					}
					dup2(mypipe[i][0],0);
					close(mypipe[i][0]);
					dup2(mypipe[N+i][1],1);
					close(mypipe[i+N][1]);
					execv(argv[2],argv);
					perror("exec error");
					exit(1);
				}
			}


			for (i = N; i < 2*N; i++)  //reduce process
			{
				pid[i] = fork(); //reducer childs
				if(pid[i] == 0)
				{
					for (j = 0 ; j < PipeNumber; j++)
					{
						if(j != N + i   )
							close(mypipe[j][1]); //reducer1 dan reducer2 e giden
						if(j != i+N-1  && j != i) // map -> r2 a giden ve r1 den r2 ye giden
								close(mypipe[j][0]);
						if(i == N && j == 2*N-1 )
								close(mypipe[j][0]); //ilk reducer in bası kapattım
					}

					dup2(mypipe[i][0],0); //mapdan gelen
					close(mypipe[i][0]);
					if(i != 2*N-1)
							{
								dup2(mypipe[i+N][1],1);
								close(mypipe[i+N][1]);
							}
					if(i != N )
						{
							dup2(mypipe[i+N-1][0],2);
							close(mypipe[i+N-1][0]);
						}
					execv(argv[3],argv);
					perror("exec error");
					exit(1);
				}
			}
			for (i = 0; i < PipeNumber; i++)
				{
					close(mypipe[i][0]);
					if(i >= N)
						close(mypipe[i][1]);
				}

			i = 0;
			while(fgets(gl,boyut,stdin) )
			{
				i++;
				j = ((i-1)%N);
				write(mypipe[j][1],gl,strlen(gl));
			}
			for (i = 0; i < N; i++)
				{close(mypipe[i][1]);}
				wait(NULL);
				free(gl);
		}
	return 0;
}
