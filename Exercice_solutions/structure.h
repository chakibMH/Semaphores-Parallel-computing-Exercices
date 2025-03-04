#define tchaine 80
#define nbCourse 3

typedef struct _COURSE COURSE;
struct _COURSE{
	char title[tchaine];
	double score;
};

typedef struct _FICHE FICHE;
struct _FICHE{
	char nom[tchaine];
	char prenom[tchaine];
	int numero;
	COURSE myCourse[nbCourse];
	};
