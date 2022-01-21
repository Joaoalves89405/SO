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
char *result;
char *toRead;
int nlinhas;
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
       
   
    line[i] = '\n';
    line[i+1] = 0;

    return i;
}

void output (){
    char line[1024];
    //int x = atoi(argv[1]);
    char enter='\n';

    int fd = open(toRead, O_RDONLY); 
    int fd2= open(result, O_WRONLY|O_CREAT|O_APPEND, 0600);
    FILE *file=fopen(toRead,"r");
    while(readln(fd, line, 200) > 0){
       nln1++;
        if(nlinhas>=nln1){
             printf("%s\n",line);
            write(fd2, &line, strlen(line));
           // write(fd2, &enter, sizeof(enter));

        }   
    

    }
    
    char temp[512];
    char *str="sistemas operativos";
     lseek(fd,0,SEEK_SET);
     int ret;
      
     while(fgets(temp,512,file)!=NULL){
       if((strcasestr(temp,str))!=NULL){
           write(fd2, &temp, strlen(temp));
         //write(fd2, &enter, sizeof(enter));
       }
     }
  
    fseek(file,0,SEEK_SET);
   
    int i=0;
    while(fgets(line, sizeof line,file)!=NULL){
            i++;
           
           
    }
     printf("Linhas totais  %d\n",i);
     printf("Numero de linhas a ler  %d\n",nlinhas);
    int aux=i-nlinhas;
    printf("Ler a partir da linha %d (para as ultimas n)\n",aux);
   
     lseek(fd,0,SEEK_SET);
    while(readln(fd, line, 200) > 0){
         nln++;
        if(nln>aux){
            write(fd2, &line, strlen(line));
            //write(fd2, &enter, sizeof(enter));
        }
    }
    nln=0;
    nln1=0;
}





int main(int argc, char* argv[]){
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
        //numero de linha a ler
        nlinhas=atoi(arg[0]);

        //ficheiro a guardar
        result=arg[2];

        //ficheiro a ler
        toRead=arg[1];
        if(nlinhas!=0 && result!=NULL && toRead!=NULL)
        output();
        to_end = strcmp(readbuf, end);
      if (to_end == 0) {
            close(fd);
         break;
      }

   }

    
    
    
       
   
    return 0;
}


