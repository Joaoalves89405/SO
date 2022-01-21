#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <signal.h>
int pid;

main(){
        char pidline[1024];
        char *pid;
        int i =0;
        int pidno[64];
        FILE *fp = popen("pidof prog4s","r");
    
        fgets(pidline,1024,fp);
        
        pid = strtok (pidline," ");

        pidno[i] = atoi(pid);
        printf("%d\n",pidno[i]);
        pid = strtok (NULL , " ");
                        
        if (kill(pidno[i],SIGKILL)!=0){
            printf("%d\n",kill);
            printf("Nao consegui matar o processo %d\n", pidno[i]);
        }
        pclose(fp);
}


