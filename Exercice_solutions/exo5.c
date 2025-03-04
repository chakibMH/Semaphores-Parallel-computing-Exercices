#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>


sem_t file,piste,nouv_piste,s;
int occup ;


void deco_ou_atter(long id,long action,int piste){

if(action == 1){

	printf("***** %ld : decollage en cours....piste %d occupee\n",id,piste);
	
	sleep(5);
	
	printf("***** %ld : decollage termine:piste %d est libre\n",id,piste);

}else{

	printf("***** %ld : atterissage en cours....piste %d occupee\n",id,piste);
	
	sleep(3);
	
	printf("***** %ld : atterissage termine:piste %d est libre\n",id,piste);
}

}

void* proc_avion(void *t){

long action = (long) t;

//attendre pour chaque avion

int duree = rand()%10;

if(action == 1)
	printf("%ld : demmande de decollage....\n",pthread_self());
else
	printf("%ld : demmande d atterissage....\n",pthread_self());

sleep(duree);



sem_wait(&piste);

deco_ou_atter(pthread_self(),action,1);

sem_post(&piste);


return NULL;
}





/* avec 2 piste : on rajoute a proc_avion un smapore piste2 et on utilise
sem_getvalue pour avoir la valeur de la 1ere piste*/

void* proc_avion_2_pistes(void *t){

long action = (long) t;

//attendre pour chaque avion

int duree = rand()%10;

int valeur;


sleep(duree);


sem_wait(&file);


//on test avant si la 1ere piste est dispo 



//sem_getvalue(&piste,&valeur);

sem_wait(&s);
int inter = occup;
sem_post(&s);
if(!inter){
//if(valeur == 1){
	sem_wait(&s);
	occup = 1;
	sem_post(&s);
	
	sem_wait(&piste);
	
	deco_ou_atter(pthread_self(),action,1);
	
	sem_wait(&s);
	occup = 0;
	sem_post(&s);
	sem_post(&piste);
}else{

	sem_wait(&nouv_piste);

	deco_ou_atter(pthread_self(),action,2);

	sem_post(&nouv_piste);
}

sem_post(&file);

return NULL;
}






int main(int argc,char* argv[]){


//d pour decollage
int d = atoi(argv[1]);
//a pour atterissage
int a = atoi(argv[2]);

//tableaux des avions
pthread_t avions[a+d];



//initialiser piste: semphore binaire
sem_init(&piste,0,1);
sem_init(&nouv_piste,0,1);
sem_init(&file,0,2);
sem_init(&s,0,1);


occup = 0;
//creer les avions:

//ceux qui veulent decoller;

long x = 1;
for(int i= 0 ;i < d;i++)
	//si on veut avec une seule piste:
	pthread_create(&avions[i],0,proc_avion,(void*) x);
	
	///*si on veut 2 pistes:
	//pthread_create(&avions[i],0,proc_avion_2_pistes,(void*) x);
	
	
	
//ceux qui veulent atterir

x = 2;
for(int i= 0 ;i < a;i++)
	//si on veut avec une seule piste:
	pthread_create(&avions[d+i],0,proc_avion,(void*) x);
	
	///*si on veut 2 pistes:
	//pthread_create(&avions[i],0,proc_avion_2_pistes,(void*) x);
	



for (int i = 0;i<a+d;i++){

	if(pthread_join(avions[i],NULL))
		perror("pthread join");
		
}

return 0;
}

