#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int NBETUDIANT=2;
int NBMODULE=2;


//Définition structures
typedef struct Module{
	int num;
	char *intitule;
	float coef;
}Module;

typedef struct Resultat_Module{
	int num_module;
	float *moyenne;
	char *valide;
}Resultat_Module;

//liste de resultat module
typedef struct resultatElement{
    Resultat_Module result;
    struct resultatElement *suivant;
    }resultatElement;
typedef struct listeResultats{
    resultatElement *debut;
    int taille;
}listeResultats;

typedef struct Etudiant{
	char *nom;
	char *prenom;
	float resultat_semestre;
	listeResultats *lr;
}Etudiant;
//liste d'etudiants
typedef struct etudiantElement{
    Etudiant etudiant;
    struct etudiantElement *suivant;
    }etudiantElement;
typedef struct listeEtudiants{
    etudiantElement *debut;
    int taille;
}listeEtudiants;

// liste de modules
typedef struct moduleElement{
    Module module;
    struct moduleElement *suivant;
    }moduleElement;
typedef struct listeModules{
    moduleElement *debut;
    int taille;
}listeModules;



//prototypes fonctions gestion etudiants
void initialiser_etudiants(listeEtudiants*);
void initialiser_modules(listeModules*);
void saisir_notes(listeEtudiants*,listeModules*);
void afficher_resultat(listeEtudiants*);//afficher resultats de tous les etudiants
int calcul_resultat_semestre(listeEtudiants*,listeModules*);
void afficher_resultat_semestre(listeEtudiants*);
int verifier_note(listeEtudiants*);//verifier si toutes les notes sont introduites
void afficheResultatEtudiant(Etudiant); //afficher resultat d'un etudiant
int rechercher_etudiant(listeEtudiants*,char*);
void supprimerEtudiant(listeEtudiants*,int);
void exporter(listeEtudiants*,listeModules*);
etudiantElement *findElementEtudiantByInd(listeEtudiants*,int); //recuperer etudiant avec indice
int isNote(char*);//verifier si la note est sous la forme(correcte) xx.xx



//definition des fonctions
void initialiser_etudiants(listeEtudiants *le){
	fflush(stdin);
	int i,j;
	char nom[32];
	char prenom[32];
	etudiantElement *env;
	le->debut=NULL;
    le->taille=0;
	for(i=0;i<NBETUDIANT;i++){
		printf("Nom (32 char max):");
		gets(nom);
		printf("Prenom (32 char max):");
		gets(prenom);
		env=(etudiantElement*)malloc(sizeof(etudiantElement));
		env->etudiant.nom=(char*)malloc(sizeof(nom));
		env->etudiant.prenom=(char*)malloc(sizeof(prenom));
		env->etudiant.lr=(listeResultats*)malloc(sizeof(listeResultats));
         env->etudiant.lr->debut=NULL;
         env->etudiant.lr->taille=0;
                      for(j=0;j<NBMODULE;j++){
                    resultatElement *rel=(resultatElement*)malloc(sizeof(resultatElement));
             rel->result.moyenne=(float*)malloc(sizeof(float));
             *(rel->result.moyenne)=-1;
             rel->suivant=env->etudiant.lr->debut;
             env->etudiant.lr->debut=rel;
             env->etudiant.lr->taille++;
             //env->etudiant.result[j].moyenne=(float*)malloc(sizeof(float));
				//*(env->etudiant.result[j].moyenne)=-1;
            }
		strcpy(env->etudiant.nom,nom);
		strcpy(env->etudiant.prenom,prenom);
		env->suivant=le->debut;
		le->debut=env;
		le->taille++;
	}
}

void initialiser_modules(listeModules *lm){
	fflush(stdin);
	int i;
	char intitule[50],test;
	moduleElement *mnv;
	lm->debut=NULL;
    lm->taille=0;
	for(i=0;i<NBMODULE;i++){
            mnv=(moduleElement*)malloc(sizeof(moduleElement));
		do{
        fflush(stdin);
		printf("Le Numero de Module :");
		scanf("%c",&test);
		if(test-48<1 || test-48>9)printf("\n***c'est incorrecte svp resaisir***\n");
        //n=c-48;
		}while(test-48<1 || test-48>9);
		mnv->module.num=test-48;
		test=0;
		//scanf("%d",&(mnv->module.num));
		printf("l'intitule de Module' :");
		scanf("%s",intitule);
		do{
                        fflush(stdin);
		printf("le Coef de Module :");
        scanf("%c",&test);
		if(test-48<1 || test-48>9)printf("\n***c'est incorrecte svp resaisir***\n");
		//scanf("%f",&(mnv->module.coef));
		}while(test-48<1 || test-48>9);
		mnv->module.coef=test-48;
         test=0;

		mnv->module.intitule=(char*)malloc(sizeof(intitule));
		strcpy(mnv->module.intitule,intitule);
		mnv->suivant=lm->debut;
		lm->debut=mnv;
		lm->taille++;
	}
}
int isNote(char *n){
    int t[5],r;
        t[0]=n[0]-48;
        t[1]=n[1]-48;
        t[2]=n[2]-48;
        t[3]=n[3]-48;
        t[4]=n[4]-48;
r=((t[0]>=0 && t[0]<10) && (t[1]>=0 && t[1]<10) && (t[2]==-2) && (t[3]>=0 && t[3]<10) && (t[4]>=0 && t[4]<10))?1:0;
return r;


}
void saisir_notes(listeEtudiants *le,listeModules *lm){
	int i,j;
	float moyenne;
	char *buf=malloc(sizeof(float));
     etudiantElement *e=le->debut;
     moduleElement *m;
	for(j=0;j<NBETUDIANT;j++){

		printf("**********Etudiant :  %s **********\n",e->etudiant.nom);
		resultatElement *rel=e->etudiant.lr->debut;
		m=lm->debut;

		for(i=0;i<NBMODULE;i++){
			if(*(rel->result.moyenne)!=-1){
                afficheResultatEtudiant(e->etudiant);
			}
			else{
				fflush(stdin);
				afficheResultatEtudiant(e->etudiant);
				printf("Entrez note(Format xx.xx/tapez entree pour sauter) : ");
				fflush(stdin);gets(buf);
				//if(strlen(buf)!=0
        // int a=buf[0]-48;
         //int b=buf[1]-48;
        //printf("\n a:%d - b: %d\n ",a,b);
         if(isNote(buf)==1)
				{
					moyenne=atof(buf);
                    	rel->result.num_module=m->module.num;
			*(rel->result.moyenne)=moyenne;
			rel->result.valide=(char*)malloc(sizeof((moyenne>=12?"v":"nv")));
			strcpy(rel->result.valide,(moyenne>=12?"v":"nv"));
                    }
				else if(strlen(buf)==0)
					moyenne=-1;
					else{printf("\nFormat incorrecte\n");}

			}
         m=m->suivant;
         rel=rel->suivant;
		}
	e=e->suivant;

	}
}
void afficher_resultat(listeEtudiants *le){
	int j;
	etudiantElement *e=le->debut;
	for(j=0;j<NBETUDIANT;j++){
		afficheResultatEtudiant(e->etudiant);
		e=e->suivant;
	}
}

int calcul_resultat_semestre(listeEtudiants *le,listeModules *lm){
	if(verifier_note(le)==1){
		int i,j;
		float resultat_semestre=0;
		float somme_coef=0;
		etudiantElement *e=le->debut;
		moduleElement *m=lm->debut;
		for(i=0;i<NBMODULE;i++){
			somme_coef+=m->module.coef;
			m=m->suivant;
		}

		for(j=0;j<NBETUDIANT;j++){
                m=lm->debut;
                resultat_semestre=0;
                resultatElement *rel=e->etudiant.lr->debut;
			for(i=0;i<NBMODULE;i++){
				resultat_semestre+=*(rel->result.moyenne)*(m->module.coef);
        m=m->suivant;
        rel=rel->suivant;
			}
			resultat_semestre/=somme_coef;
			e->etudiant.resultat_semestre=resultat_semestre;
			e=e->suivant;
	}
	return 1;
	}
	else
			return -1;
}

void afficher_resultat_semestre(listeEtudiants *le){
	printf("\n\n****************** Resultat de Semestre ******************\n\n");
	int i;
	float moy_classe=0,note_max,note_min;
	int nb_v=0,nb_nv=0;
	etudiantElement *e=le->debut;
	note_max=e->etudiant.resultat_semestre;
	note_min=e->etudiant.resultat_semestre;
	for(i=0;i<NBETUDIANT;i++){
		printf("%s \t %s \t",e->etudiant.nom,e->etudiant.prenom);
		printf("%f\n",e->etudiant.resultat_semestre);
		moy_classe+=e->etudiant.resultat_semestre;
		(e->etudiant.resultat_semestre>=12)?nb_v++:nb_nv++;
		if(e->etudiant.resultat_semestre>note_max)
			note_max=e->etudiant.resultat_semestre;
		if(e->etudiant.resultat_semestre<note_min)
			note_min=e->etudiant.resultat_semestre;
			e=e->suivant;
		}
	moy_classe/=NBETUDIANT;
	printf("\n...\n\n");
	printf("Moyenne de Classe : %f\n",moy_classe);
	printf("Note Max : %f\n",note_max);
	printf("Note Min : %f\n",note_min);
	printf("Nombre d'etudiants ayant validé le Semestre : %d\n",nb_v);
	printf("Nombre d'etudiants n'ont pas validé le Semestre : %d\n",nb_nv);
}
int verifier_note(listeEtudiants *le){
	int i,j;
	etudiantElement *e=le->debut;
	for(i=0;i<NBETUDIANT;i++){
            resultatElement *rel=e->etudiant.lr->debut;
		for(j=0;j<NBMODULE;j++)
		{
			if(*(rel->result.moyenne)==-1)
				{return -1;}
    rel=rel->suivant;
            }
            e=e->suivant;
	}
	return 1;
}

void afficheResultatEtudiant(Etudiant etudiant){
	printf("%s \t %s \t",etudiant.nom,etudiant.prenom);
	int i;
	resultatElement *rel=etudiant.lr->debut;
		for(i=0;i<NBMODULE;i++){
			if(*(rel->result.moyenne)!=-1)
			printf("%f\t",*(rel->result.moyenne));
			else
			printf("\t");
			rel=rel->suivant;
		}
		printf("\n");
}

int rechercher_etudiant(listeEtudiants *le,char *nom){
	int i;
	etudiantElement *e=le->debut;

	for(i=0;i<NBETUDIANT;i++){
		if(strcmp(nom,e->etudiant.nom)==0)
			return i;
			e=e->suivant;
	}
	return -1;
}

etudiantElement *findElementEtudiantByInd(listeEtudiants *le,int ind)
{
etudiantElement *e=le->debut;
int i;
	for(i=0;i<ind;i++)
	{
	e=e->suivant;
	}
return e;
}


void supprimerEtudiant(listeEtudiants *le,int ind){
	int i,j;
		etudiantElement *e=le->debut;
	etudiantElement *e1=findElementEtudiantByInd(le,ind);
	//teste si l'element a supprimer est le premier de la liste

	if(strcmp(e->etudiant.nom,e1->etudiant.nom)==0)
    {
          int c;
                printf("\n confirmez suppression : tapez 1 pour confirmez ou 2 pour annuler ? \n");
                scanf("%d",&c);
                if(c==1){
                le->debut=e->suivant;
				free(e);
				le->taille--;
				NBETUDIANT--;
				puts("Suppression effectuee !");
    }
    }
    else{
	for(i=0;i<NBETUDIANT;i++)
	{
		if(strcmp(e->suivant->etudiant.nom,e1->etudiant.nom)==0)
			{
                                                  int c;
                printf("\n confirmez suppression : tapez 1 pour confirmez ou 2 pour annuler ? \n");
                scanf("%d",&c);
                if(c==1){
                        etudiantElement *aux;
                aux=e->suivant;
                        e->suivant=e1->suivant;
				free(aux);
				le->taille--;
								NBETUDIANT--;
				puts("Suppression effectuee !");
				break;
            }
            else
            break;
			}
			e=e->suivant;
	}
}
    }

void exporter(listeEtudiants *le,listeModules *lm){

	FILE* fichier = NULL;
    int i,j;
    etudiantElement *e=le->debut;
	moduleElement *m=lm->debut;
    fichier = fopen("fichier.txt", "w");

    if (fichier != NULL)
    {
    	fprintf(fichier,"Nom \t Prenom \t");


 		for(i=0;i<NBMODULE;i++){
 		fprintf(fichier,"%s\t",m->module.intitule);

 		m=m->suivant;
 		}
 		fprintf(fichier,"\n");

        for(i=0;i<NBETUDIANT;i++){
                resultatElement *rel=e->etudiant.lr->debut;
        	fprintf(fichier, "%s\t%s\t", e->etudiant.nom,e->etudiant.prenom);
        	for(j=0;j<NBMODULE;j++){
        		if(*(rel->result.moyenne)!=-1)
        		fprintf(fichier, "%f\t", *(rel->result.moyenne));
        		else
        		fprintf(fichier,"Vide \t");
        		rel=rel->suivant;
        	}
        	fprintf(fichier,"\n");
        	e=e->suivant;
		}

        fclose(fichier);
        system("fichier.txt");
    }
}





int main(int argc, char *argv[]) {
	int et=0,mod=0,note=0;
	listeEtudiants *le=(listeEtudiants*)malloc(sizeof(listeEtudiants));
	listeModules *lm=(listeModules*)malloc(sizeof(listeModules));
	char nom[32];
	int numero;
	char s;
	int choix;
	do{
	printf("\n\n------------------------------  Menu  ------------------------------\n\n");
	puts("1. Saisie des Etudiants");
	puts("2. Saisie des Modules");
	puts("3. Saisie des Notes Module'");
	puts("4. Details d'un Etudiant");
	puts("5. Afficher Les resultats de tous les Etudiants");
	puts("6. Afficher Les resultats d'un Semestre");
	puts("7. Supprimer un Etudiant");
	puts("8. Exporter vers Fichier");
	puts("0. Quitter");
	printf("\n------------------------------  Menu  ------------------------------\n");
	printf("\n Votre choix : ");
	//scanf("%d",&choix);
	fflush(stdin);
	//scanf("%c",&s);
	s=getch();
	//printf("%c %d ! ",s,s);
	choix=(int)s-48;
	printf("\n ");
	switch(choix){
		case 1  : if(et==0){et=1;initialiser_etudiants(le);} else printf("Etudiants deja saisis"); break;
             //et=1; initialiser_etudiants(tabEt); break;
		case 2  : if(mod==0){mod=1;initialiser_modules(lm);} else printf("Modules deja saisis"); break;
             //mod=1; initialiser_modules(tabMod);
		case 3  : if(et==1&&mod==1)
					{ note=1; saisir_notes(le,lm);}
				  else
					puts("Tableau Etudiants/Modules vide !! ");
		break;
		case 4  :
					if(et==1)
					{
					printf("Nom etudiant (32 char max): ");
					scanf("%s",nom);
					int ind = rechercher_etudiant(le,nom);
					if(ind!=-1)
                    {etudiantElement *e=findElementEtudiantByInd(le,ind);
							afficheResultatEtudiant(e->etudiant);}
					else
						puts("Etudiant Innexistant !!");
					}
					else
						puts("Tableau des Etudiant Vide");
					break;

		case 5  : if(et==1&&mod==1)
					afficher_resultat(le);
					else
					puts("Tableau Etudiants/Modules Vide !!");
		 break;
		case 6  : if(et==1&&mod==1&&note==1){
					if(calcul_resultat_semestre(le,lm)==1)
				  		afficher_resultat_semestre(le);
				  	else
				  		puts("Des notes introuvables !! ");
				  }
				  else
				  	puts("Tableau d'Etudiants/Modules/Notes Vide");
				break;
		case 7  : if(et==1){
					printf("Nom etudiant (32 char max): ");
					scanf("%s",nom);
					int ind = rechercher_etudiant(le,nom);
					if(ind!=-1)
						supprimerEtudiant(le,ind);
					else
						puts("Etudiant Innexistant !! ");
					}
					else
						puts("Tableau d'etudiants vide !!");
		 break;
		case 8  : if(et==1&&mod==1)
					exporter(le,lm);
					else
					puts("Tableau Etudiants/Modules Vide");
					 break;
		case 0  : exit(-1); break;
		default : puts("Erreur choix !");
	}
	}while(choix=!0);

	return 0;
}
