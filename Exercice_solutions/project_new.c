#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include "structure.h"

#define nbCOURSE 3

void printFiche(FICHE fiche);
void exo1();

void saveFiche(FILE *file,FICHE f);
void exo2();

void exo3();

void loadFiche(FICHE *fiche, char *str);

void exo4();

void exo5();

int main(){

exo5();

return 0;
}

void exo1(){
FICHE f;
strcpy(f.nom,"DOE");

strcpy(f.prenom ,"John");
f.numero = 12345689;
for(int i = 0;i<nbCOURSE;i++){

	strcpy(f.myCourse[i].title ,"cours");

	f.myCourse[i].score = 18;

}
printFiche(f);
}

void printFiche(FICHE fiche){
	printf("Affichage de la fiche de l\'etidiant:\n");
	printf("nom : %s\n",fiche.nom);
	printf("prenom : %s\n",fiche.prenom);
	printf("numero : %d\n",fiche.numero);
	printf("Affichage des cours l\'etidiant:\n");
	
	for(int i=0; i < nbCOURSE; i ++)
	{
		printf("\n-----------------------------------\n");
		printf("nom cours:%s note : 		 %f\n",fiche.myCourse[i].title,fiche.myCourse[i].score);
	}
	
}


void exo2()
{
FICHE f;
strcpy(f.nom,"DOE");

strcpy(f.prenom ,"John");
f.numero = 12345689;
for(int i = 0;i<nbCOURSE;i++){

	strcpy(f.myCourse[i].title ,"cours");

	f.myCourse[i].score = 18;

}


saveFiche(stdout,f);


}

void saveFiche(FILE *file,FICHE f)
{
fprintf(file,"%s;%s;%d",f.nom,f.prenom,f.numero);
for(int i =0; i < nbCOURSE;i++)
	fprintf(file,";%s;%f",f.myCourse[i].title,f.myCourse[i].score);

fprintf(file,"\n");

}

void exo3()
{
FILE *fPtr;

fPtr = fopen("database.csv","w");
if(fPtr == NULL)
    {
        //erreur
        printf("erreur lors de la manipulation du fichier.\n");
        exit(EXIT_FAILURE);
    }
 
//creer une fiche
FICHE f;
strcpy(f.nom,"DOE");

strcpy(f.prenom ,"John");
f.numero = 12345689;
for(int i = 0;i<nbCOURSE;i++){

	strcpy(f.myCourse[i].title ,"cours");

	f.myCourse[i].score = 18;

}

saveFiche(fPtr,f);

fclose(fPtr);


}

void loadFiche(FICHE *f, char *str)
{
char *pv = ";";
char *tok = strtok(str,pv);

	//1ere val est celle du nom
		strcpy(f->nom , tok);
		
		//prenom
		tok = strtok(NULL,pv);
		strcpy(f->prenom ,tok);

		//numero ( int )
		tok = strtok(NULL,pv);
		f->numero = atoi(tok);
		
		//les cours
		for(int i = 0;i<nbCOURSE;i++){
			//title
			tok = strtok(NULL,pv);
			strcpy(f->myCourse[i].title,tok);
		
			//score
			tok = strtok(NULL,pv);
			f->myCourse[i].score = atof(tok);
	
		}
		
		
	
	

}

void exo5(){
//ouvrir le ficher database.csv

FILE *fPtr;

fPtr = fopen("database.csv","r");
if(fPtr == NULL)
    {
        //erreur
        printf("erreur lors de la manipulation du fichier.\n");
        exit(EXIT_FAILURE);
    }
    
    
//lire la 1ere ligne 
char line[150];
fgets(line,150,fPtr);

printf("\nline : %s\n",line);

FICHE f;

loadFiche(&f,line);

printf("affichage depuis la structure:\n");
printf("nom depuis fichier : %s\n",f.nom);
printf("prenom depuis fichier : %s\n",f.prenom);
printf("numero depuis fichier : %d\n",f.numero);
for(int i = 0;i<nbCOURSE;i++){
printf("nom cours num %d depuis fichier : %s\n",i,f.myCourse[i].title);
printf("note cours num %d depuis fichier : %f\n",i,f.myCourse[i].score);
}
}



