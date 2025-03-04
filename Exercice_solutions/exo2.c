#include<stdlib.h>
#include<stdio.h>
#include<sys/wait.h>
#include<unistd.h>

int main(){



for(int i = 0;i < 2 ;i++){
int p = fork();

if(p == -1){printf("erreur avec fork\n");}
if(p == 0){//fils
int nb = rand();
// 0 < nb < 1500
nb = nb + getpid();
nb = nb % 100;

printf("fils de pid %d: valeur aleatoire est %d\n",getpid(),nb);
exit(nb);
}
}


//afficher le max
int stat,val,val2;
int a = wait(&stat);
if(WIFEXITED(stat)){
val = WEXITSTATUS(stat);

}

int b = wait(&stat);
if(WIFEXITED(stat)){
val2 = WEXITSTATUS(stat);

}

if(val > val2) printf("le fils %d a la valeur la ++ elevee : %d\n",a,val);
else printf("le fils %d a la valeur la ++ elevee : %d\n",b,val2);



return 0;
}
