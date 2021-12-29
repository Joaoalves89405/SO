#define _GNU_SOURCE
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#define FIFO_FILE "MYFIFO"
#define MAX 100000

char buffer[1024];
int nln =0;
int nln1 =0;
int readchar(int fd){
    char c[1];
    if(read(fd, c, 1) != 0){
       
        
        return c[0];
    } else { 
      
        return -1;}   
       
}

ssize_t readln(int fd, char *line, size_t size){
    int i = 0;

    int ln=0;

    char c = readchar(fd);
    while(c > 0 && c != '\n' && i < size){
        line[i] = c; 

        i++;
        c = readchar(fd);
        
        }
       
   
    line[i] = 0;

    return i;
}

/*void output (){
    char line[1024];
    //int x = atoi(argv[1]);

    int fd = open(argv[2], O_RDONLY); 
    FILE *file=fopen(argv[2],"r");
    while(readln(fd, line, 200) > 0){
       nln1++;
        if(x>=nln1){
            printf("%s\n",line);
        }   
    

    }
    printf("-------------------\n");
    char temp[512];
    char *str="sistemas operativos";
     lseek(fd,0,SEEK_SET);
     int ret;
      
     while(fgets(temp,512,file)!=NULL){
       if((strcasestr(temp,str))!=NULL){
           printf("%s",temp);
       }
     }
  
    fseek(file,0,SEEK_SET);
    printf("-------------------\n");
    int i=0;
    while(fgets(line, sizeof line,file)!=NULL){
            i++;
           
    }
    
    int aux=i-x;
   
     lseek(fd,0,SEEK_SET);
    while(readln(fd, line, 200) > 0){
         nln++;
        if(nln>aux){
            printf("%s\n",line);
        }
    }
}*/





int main(int argc, char* argv[]){
    int fdo = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC,0640);
    char *p;
    char *arg [80];
    int n;
    int i =0;

    int fd;
    char readbuf[80];
    char end[10];
    int to_end;
    int read_bytes;
   
    
    mknod(FIFO_FILE, S_IFIFO|0640, 0);
    strcpy(end, "end");
    while(1) {
        fd = open(FIFO_FILE, O_RDONLY);
        read_bytes = read(fd, readbuf, sizeof(readbuf));
        readbuf[read_bytes] = '\0';
        p = strtok(readbuf," ");

        while(p != NULL){
            arg[i] =p;
            printf("%s\n",arg[i]);
            printf("%d\n",i);
            i++;
            p = strtok(NULL, " ");
        }
        i=0;
        to_end = strcmp(readbuf, end);
      if (to_end == 0) {
            close(fd);
         break;
      }
   }

    
    
    
       
   
    return 0;
}


