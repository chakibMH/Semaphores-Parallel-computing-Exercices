#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>

int nb_sur_barque;
int classement;

sem_t rev_naut, sbarque, s_nb_barque,att_arriv;
sem_t j2bloq[4];
sem_t buzz;

void* joueur1(void* v){




long num_eq = (long) v;

printf("joueur 1 de l equipe %ld : commencer\n",num_eq);


//parcourir 1000m

int tps = 5;

tps += rand() %6;

printf("joueur 1 de l\'equipe : %ld va finir dans %d\n",num_eq,tps);
sleep(tps);

//arrive de joueur 1

sem_wait(&sbarque);

sem_wait(&s_nb_barque);
nb_sur_barque ++;


if(nb_sur_barque == 2){
		printf("joueur 1 de l\'equipe %ld sur barque, on traversse !\n",num_eq);
		//on libere nb_sur_barque
		sem_post(&s_nb_barque);
		//c le 2eme donc on reveille le nautonier
		sem_post(&rev_naut);
		//on attend d'etre arrive
		sem_wait(&att_arriv);

}else{
printf("joueur 1 de l\'equipe %ld sur barque : en attente d un autre joueur\n",num_eq);
//on libere nb_sur_barque
sem_post(&s_nb_barque);
//on attend d'etre arrive
sem_wait(&att_arriv);
}

printf("joueur 1 de l equipe %ld : fini !\nje libere joueur 2 : bon courage !\n",num_eq);

sem_post(&j2bloq[num_eq-1]);

}



void* joueur2(void* v){

long num_eq = (long) v;

printf("joueur 2 de l equipe %ld pret !\n",num_eq);


sem_wait(&j2bloq[num_eq-1]);

printf("joueur 2 de l equipe %ld je prend le relai !\n",num_eq);

int es =4;
es += rand() %3;

printf("joueur 2 de l equipe %ld je commence l esscalade...\n",num_eq);

sleep(es);

//appuyer sur le buzzer

sem_wait(&buzz);

printf("joueur 2 de l equipe %ld : l\'equipe %ld est arrive a la %d  place\n",num_eq,num_eq,classement);

classement++;

sem_post(&buzz);




}

void* nautonier(void* v){

for(int i = 0; i <=1;i++){
printf("nautonier : j attend!\n");
//il se bloque en attente de 2 joueurs
sem_wait(&rev_naut);

//traversser
sleep(3);

//reveiller les  2 joueurs dans la barque
sem_post(&att_arriv);
sem_post(&att_arriv);


//revenir
sleep(2);

//signaler que la barque est vide
nb_sur_barque = 0;
//et reveiller les joueurs en attente sur l'autre rive
sem_post(&sbarque);
sem_post(&sbarque);
}


}

int main(){

pthread_t eq1[2];
pthread_t eq2[2];
pthread_t eq3[2];
pthread_t eq4[2];

pthread_t naut_barque;

long num_eq;



//initialiser les semaphores
//pour le nautonier
sem_init(&rev_naut,0,0);
//pour verifier si barque pleine
sem_init(&sbarque,0,2);
//pour modifier le nb de joueur sur barque
sem_init(&s_nb_barque,0,1);
//attendre l'arrive
sem_init(&att_arriv,0,0);


//initialiser le tableau des emaphores des joueurs2
for(int i = 0;i < 4; i++)
	sem_init(&j2bloq[i],0,0);


//semaphire pour le buzzer
sem_init(&buzz,0,1);

//initialiser le nb de joueurs dans la arque
nb_sur_barque = 0;

//inialiser classement
classement = 1;


//on cree le 2eme joueur de chaque equipe
num_eq = 1;
pthread_create(&eq1[1],0,joueur2,(void*) num_eq);

num_eq = 2;
pthread_create(&eq2[1],0,joueur2,(void*) num_eq);

num_eq = 3;
pthread_create(&eq3[1],0,joueur2,(void*) num_eq);

num_eq = 4;
pthread_create(&eq4[1],0,joueur2,(void*) num_eq);

sleep(4);


//on cree le 1er joueur de chaque equipe
num_eq = 1;
pthread_create(&eq1[0],0,joueur1,(void*) num_eq);

num_eq = 2;
pthread_create(&eq2[0],0,joueur1,(void*) num_eq);

num_eq = 3;
pthread_create(&eq3[0],0,joueur1,(void*) num_eq);

num_eq = 4;
pthread_create(&eq4[0],0,joueur1,(void*) num_eq);

pthread_create(&naut_barque,0,nautonier,NULL);





	if(pthread_join(eq1[0],NULL))
		perror("pthread join");

	if(pthread_join(eq2[0],NULL))
		perror("pthread join");

	if(pthread_join(eq3[0],NULL))
		perror("pthread join");

	if(pthread_join(eq4[0],NULL))
		perror("pthread join");

	if(pthread_join(naut_barque,NULL))
		perror("pthread join");

	if(pthread_join(eq1[1],NULL))
		perror("pthread join");

	if(pthread_join(eq2[1],NULL))
		perror("pthread join");

	if(pthread_join(eq3[1],NULL))
		perror("pthread join");

	if(pthread_join(eq4[1],NULL))
		perror("pthread join");

return 0;
}
