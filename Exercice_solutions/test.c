#include<stdio.h>
#include<stdlib.h>

#define SIZE 10

void printVector(double* a);
void exo1();


int main(){

double tab[SIZE] = {1,2,35,4,66,4,1,23,5,4};

exo1();
//printVector(tab);

return 0;
}

void exo1(){

double v[SIZE] = {1,2,3,4,5,6,7,8,9,100};
printVector(v);

}


void printVector(double* a){

for ( int i = 0;i<SIZE;i++)

	printf("%f \n",*(a + i));
}

double dot(double v1[],double v2[])
{

double resultat = 0;

for(int i = 0;i < SIZE;i++)
	resultat += v1[i]*v2[i];// equiv : resultat = resultat + v1[i]*v2[i];

return resultat;
}

void copyVector(double dest[], double src[]){

for(int i = 0; i < SIZE;i++)
	dest[i] = src[i];

}


double max(double v[]){

double m = v[0];

for(int i = 1;i<SIZE;i++){

	if(v[i] > m) 
		m = v[i];
		
}

return m;

}


double min(double v[]){

double m = v[0];

for(int i = 1;i<SIZE;i++){

	if(v[i] < m) 
		m = v[i];
		
}

return m;

}

double valMoy(double v[]){

double vm = 0;

for(int i = 0;i<SIZE;i++){
	vm += v[i];}
	
vm /= SIZE;
	
return vm;
}




































