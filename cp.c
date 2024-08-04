#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
int main(int argc,char *argv[])
{
   int fd,flags=O_CREAT |O_RDWR,fd1;
   mode_t mode;
   mode= S_IRUSR| S_IWUSR| S_IRGRP| S_IROTH;  //rw-r--r--

   //int open(const char *pathname, int flags);
   fd=open(argv[1],flags,mode);
   ssize_t count;
   char buf[2048];

   //ssize_t read(int fd, void *buf, size_t count);
   count=read(fd,buf,2048);
   if(count==-1)
   {
      perror("read()");
      printf("ERROR\n");
   }
   
   close(fd);
   //int open(const char *pathname, int flags, mode_t mode);

   fd1=open(argv[2],flags,mode);

   //ssize_t write(int fd, const void *buf, size_t count);
   write(fd1,buf,count);
   if(fd==-1)
   {
      printf("Error in coping\n");
   }
   else
   {
      printf("copied successfully!\n");
   }
   close(fd1);
}
