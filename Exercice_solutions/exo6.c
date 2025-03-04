#include<stdlib.h>
#include<stdio.h>
#include<sys/wait.h>
#include<unistd.h>
#include<math.h>

int main(int argc, char* argv[]){

int N;

if(argc != 2) printf("veuillez entrer une seule valeur entiere");

else{

N = atoi(argv[1]);


for(int i = 0;i < N ;i++){
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

// int pids[N];
// int val[N];

int max_pid, max_val;
int stat,a,val;

for(int i = 0;i < N ;i++){
a = wait(&stat);
if(WIFEXITED(stat))
  val = WEXITSTATUS(stat);

if((i == 0) | (val > max_val))
{
  max_pid = a;
  max_val = val;
}
}


printf("le fils %d a la valeur la plus elevee = %d\n",max_pid,max_val);

}

return 0;
}
