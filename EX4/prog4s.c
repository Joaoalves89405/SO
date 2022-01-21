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

int nln =0;
int nln1 =0;
char *result;
char *toRead;
int nlinhas;
int nProc;

int readchar(int fd){
    char c[1];
    if(read(fd, c, 1) != 0){
        return c[0];
    } else { 
        return -1;
    }      
}

ssize_t readln(int fd, char *line, size_t size){
    int i = 0;
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
    int fd = open(toRead, O_RDONLY); 
    int fd2= open(result, O_WRONLY|O_CREAT|O_APPEND, 0600);
    FILE *file=fopen(toRead,"r");

    while(readln(fd, line, 200) > 0){
       nln1++;
        if(nlinhas>=nln1){
             printf("%s\n",line);
             write(fd2, &line, strlen(line));
        }   
    }
    
    char temp[512];
    char *str="sistemas operativos";
    lseek(fd,0,SEEK_SET);
      
    while(fgets(temp,512,file)!=NULL){
       if((strcasestr(temp,str))!=NULL){
           write(fd2, &temp, strlen(temp));
       }
    }
  
    fseek(file,0,SEEK_SET);
    int i=0;
    while(fgets(line, sizeof line,file)!=NULL){
        i++;      
    }
    int aux=i-nlinhas;
    lseek(fd,0,SEEK_SET);

    while(readln(fd, line, 200) > 0){
        nln++;
            if(nln>aux){
                write(fd2, &line, strlen(line));
            }
    }
    nln=0;
    nln1=0;
}





int main(int argc, char* argv[]){
    char *p;
    char *arg [80];
    int i =0;
    int fd;
    char readbuf[80];
    int clientes=0;
    int read_bytes;
    nProc=atoi(argv[1]);  
    mknod(FIFO_FILE, S_IFIFO|0640, 0);

    while(1) {
      
        fd = open(FIFO_FILE, O_RDONLY);
        while(read(fd, readbuf, sizeof(readbuf))>0){
            clientes++;
            if(clientes<=nProc){
                printf("Clientes %d \n",clientes);
                if(fork()==0){
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
                }
            }
            wait(NULL);
            clientes--;
            printf("Clientes %d \n",clientes);
        }     
   }

    close(fd);
    return 0;
}


