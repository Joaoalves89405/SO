/* Filename: fifoclient_twoway.c */
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#define FIFO_FILE "MYFIFO"

int main(int argc, char* argv[]) {
   int fd;
   char buffer[50]={" "};
   fd = open(FIFO_FILE, O_CREAT|O_WRONLY|O_TRUNC);
      for(int v=1;v<argc;v++){
         strcat(buffer,argv[v]);
         strcat(buffer," ");
      }
         write(fd, buffer, strlen(buffer));
         //printf("%s",buffer);
   return 0;
}