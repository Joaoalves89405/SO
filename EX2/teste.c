#define _GNU_SOURCE
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#define MAX 100000

char buffer[1000];
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





int main2(int linhas, char *ficheiro){
    char line[256];
     
    printf("%s \n",ficheiro);
    printf("%d \n",linhas);

    int fd = open(ficheiro, O_RDONLY); 
    FILE *file=fopen(ficheiro,"r");
    if(fd==NULL){
        printf("Nao abriu \n");

    }
    
    while(readln(fd, line, 200) > 0){
        
       nln1++;
        if(linhas>=nln1){
            printf("%s\n",line);
        }   
    

    }
    printf("-------------------1\n");
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
    printf("-------------------2\n");
    int i=0;
    while(fgets(line, sizeof line,file)!=NULL){
            i++;
           
    }
    
    int aux=i-linhas;
   
     lseek(fd,0,SEEK_SET);
    while(readln(fd, line, 200) > 0){
         nln++;
        if(nln>aux){
            printf("%s\n",line);
        }
          
            
    
    }
       
   
    return 0;
}
int main(int argc, char* argv[]){
printf("%d\n",argc);
//nº de ciclos= argc-2, corresponde ao numero de ficheiros a ler
//fork() e negativo caso de asneira
int nlinhas=atoi(argv[argc-1]);
printf("numero de linhas %d\n ", nlinhas);

for(int l=0;l<(argc-2);l++){
    if(fork()==0){

        printf("Sou o filho %d\n", l);
        printf("Nome do ficheiro %s\n", argv[l+1]);
        main2(nlinhas,argv[l+1]);

        printf("Terminei tarefa %d\n",l);
        _exit(0);
        
    }
}
for(int l = 0; l < 10; l++){
        wait(NULL);
    }

    return 0;
}
