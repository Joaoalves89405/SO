#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <signal.h>
int pid;

/*void handler(int signum){
    
    switch (signum){
        case SIGQUIT:{
             printf("Processo termindado\n");
             kill(SIGKILL,pid);
        }
    }
}*/


main(){
        char pidline[1024];
        char *pid;
        int i =0;
        int pidno[64];
        FILE *fp = popen("pidof prog3s","r");
    
        fgets(pidline,1024,fp);
        
        pid = strtok (pidline," ");

        pidno[i] = atoi(pid);
        printf("%d\n",pidno[i]);
        pid = strtok (NULL , " ");
                        
        if (kill(pidno[i],SIGKILL)!=0){
            printf("%d\n",kill);
            printf("Nao consegui matar esse\n");
        }
        pclose(fp);
}


