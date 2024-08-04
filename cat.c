#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
int main(int argc,char *argv[])
{
   int fd,flags=O_CREAT;
   //int open(const char *pathname, int flags);
   fd=open(argv[1],flags);
   ssize_t count;
   char buf[2048];
   //ssize_t read(int fd, void *buf, size_t count);
   count=read(fd,buf,2048);
   if(count==-1)
     printf("ERROR\n");
   //ssize_t write(int fd, const void *buf, size_t count);
   write(STDOUT_FILENO,buf,count);
   close(fd);
}

