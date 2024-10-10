#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>

#define SBUF 512

int main(int argc,char **argv)
{
    int pipefd,fd1,fd2;
    char buf[SBUF];
    char str[SBUF];
    if(mkfifo(argv[1],0664)==-1)
    {   
        perror("mkfifo()");
        exit(EXIT_FAILURE);
    }   

    pipefd=open(argv[1],O_RDWR);
    if(pipefd==-1)
    {   
        perror("open()");
        exit(EXIT_FAILURE);
    }   

    pid_t pid=fork();
    if(pid<0)
    {   
	    perror("fork()");
	    exit(EXIT_FAILURE);
    }   

    if(pid==0)
    {   
	    fd1=open(argv[2],O_RDONLY);
	    if(fd1==-1)
	    {
		    perror("open()");
		    exit(EXIT_FAILURE);
	    }
	    int x=1;
	    ssize_t rd,wr;
	    while(rd=read(fd1,buf,1)>0)
	    {
		    if(write(pipefd,buf,1)==-1)
		    {
			    perror("write()");
			    exit(EXIT_FAILURE);
		    }
	    }
	    if(rd==-1)
	    {
		    perror("read()");
		    exit(EXIT_FAILURE);
	    }
	    exit(EXIT_SUCCESS);
    }
    close(fd1);
    wait(NULL);
    printf("file transfered\n");
    pid_t pid1=fork();
    if(pid1 < 0)
    {
	    perror("fork()");
	    exit(EXIT_FAILURE);
    }

    if(pid1==0)
    {
	    int upipe[2];
	    if(pipe(upipe)==-1)
	    {
		    perror("pipe()");
		    exit(EXIT_FAILURE);
	    }
	    int x=0,pfd;
	    ssize_t wr1,rd1,rd2;
	    fd2=open(argv[3],O_RDWR|O_CREAT,0644);
	    if(fd2==-1)
	    {
		    perror("open()");
		    exit(EXIT_FAILURE);
	    }
	    while((rd1=read(pipefd,str,1))>0)
	    {
		    x++;
		    if(x==257)
		    {
			    perror("shared file is not in limited size (limited size is 256 bytes\n)");
			    exit(EXIT_FAILURE);
		    }
		    if(write(fd2,str,rd1)==-1)
		    {
			    perror("write()");
			    exit(EXIT_FAILURE);
		    }
	    }
	    if(rd1==-1)
	    {
		    perror("read()");
		    exit(EXIT_FAILURE);
	    }
	    close(fd2);
	    exit(EXIT_SUCCESS);
    }
    exit(EXIT_SUCCESS);
}
