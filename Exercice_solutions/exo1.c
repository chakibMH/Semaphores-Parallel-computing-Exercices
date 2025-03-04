#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<sys/wait.h>

void main(){

int pid,pid1;

pid = fork();



if(pid == -1)
    //erreur
    printf("Erreur lors de l\'execution");
else {if(pid == 0) {
           //fils
           for(int i = 0;i <5; i++){
           sleep(2);

           printf("je suis le processus fils N %d, et mon pid est : %d, mon pere   est %d\n",i,getpid(),getppid());}

            }else{//pere

            /* printf("je suis le processus pere mon pid est : %d, mon fils                  est %d\n",getpid(),pid1);*/

             printf("je suis le processus pere mon pid est : %d, mon fils                  est %d\n",getpid(),pid);

             /*int val = wait(NULL);
             printf("val = %d",val);*/

             waitpid(pid);
             }
      }

}
