#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include<wait.h>
#define MSGSIZE 30
char msg1[30] = "hello, world from child!!";
char msg2[30] = "hello, world from parent!";

int main()
{
    char inbuf_ch[MSGSIZE];
		char inbuf_pr[MSGSIZE];
    int p1[2], p2[2], pid, nbytes;

    if (pipe(p1) < 0 || pipe(p2) < 0)// on success return 0 else -1
        exit(1);

    if ((pid = fork()) == 0) {
			close(p1[0]);// close read side of p2 pipe
			close(p2[1]);// close write side of p1 pipe
        write(p1[1], msg1, sizeof(msg1));
				read(p2[0],inbuf_ch,100);
				fflush(stdout);
			 close(p1[1]);// close write of p1
			 close(p2[0]);// close read op p2 not need any more
			 printf("I am child and comming message is '%s'\n",inbuf_ch );
			sleep(3);
			exit(0);
    }

    else {
        			close(p1[1]);//close write of p1
				close(p2[0]);// close read of p2
				 write(p2[1], msg2, sizeof(msg2));
				 read(p1[0],inbuf_pr,1000);
	    			 fflush(stdout);
				close(p2[1]);
				close(p1[0]);
				printf("I am parent and child send me a message like '%s'\n",inbuf_pr );
        printf("Parent is waiting for child to exit \n");
				wait(NULL);
		}
		printf("Bay Bay..\n" );
    return 0;
}
