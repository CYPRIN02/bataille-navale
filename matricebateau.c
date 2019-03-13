#include <stdio.h>
#include <stdlib.h>
#include "liste.h"

int danslagrille(int taille, case_t cell ){
	if( cell.x >= taille || cell.y >= taille || cell.x < 1 || cell.y < 1 )
		return 0;
	return 1;
}

int type_bateau(t_liste joueur){
	en_tete(&joueur);
	bateau_t *actuel;	
	if(liste_vide(&joueur)){
			return 0;
	}
	while(!hors_liste(&joueur)){
		valeur_elt(&joueur, actuel);
		if(actuel->taille == 1){
			actuel->type = mine;
		}
		if(actuel->taille == 2){
			actuel->type = torpilleur;
		}
		if(actuel->taille == 3){
			actuel->type = sousmarin;
		}
		if(actuel->taille == 4){
			actuel->type = croiseur;
		}
		if(actuel->taille == 5){
			actuel->type = porteavion;
		}
		suivant(&joueur);
	}
	return 1;
}


int appliquer_bateau(t_liste joueur1, t_liste joueur2){
		en_tete(&joueur1);
		en_tete(&joueur2);
		bateau_t nouveau;
		if(liste_vide(&joueur1)){
			return 0;
		}
		while(!hors_liste(&joueur1)){
			valeur_elt(&joueur1, &nouveau);
			ajout_droit(&joueur2, nouveau);
			suivant(&joueur1);
			suivant(&joueur2);
		}
		return 1;
}

int fin_bateau_vertical(bateau_t *bateau){ 
	return (bateau->coord.y + bateau->taille);
}
       
int fin_bateau_horizontal(bateau_t *bateau){
	return (bateau->coord.x + bateau->taille); 
}

// Voir avec la SDL. Ici version terminal
void afficher_matrice_bateau(t_liste joueur, int taille){
	bateau_t * actuel;
	for(int i=0; i<taille ; i++){
       		for(int j=0; j<taille ; j++){
       			en_tete(&joueur);
       			while(!hors_liste(&joueur)){
       				valeur_elt(&joueur, actuel);
       				if(i==actuel->coord.x && j==actuel->coord.y){
	       				if(actuel->dir == vertical){
	       					for(int k=j; k< (fin_bateau_vertical(actuel)); k++){
	       						printf("[.]");
	       					}
	       				}
	       				if(actuel->dir == horizontal){
	       					for(int k=j; k< (fin_bateau_horizontal(actuel)); k++){
	       						printf("[.]");
	       					}
	       				}
	       			}
	       			else{
	       				printf("[ ]");
	       			}
	       			suivant(&joueur);
	       		}
       		}
		printf("\n");
	}
}

/*  */
void cases_prises(t_liste joueur, case_t* case_nonlibres, int taille){
	bateau_t *bat;	
	int fin_bat;
	int i, compteur;
	case_t actuel;
	en_tete(&joueur);  
	while(!hors_liste(&joueur)){
		valeur_elt(&joueur, bat);
		if(bat->dir == vertical){
	       		fin_bat = fin_bateau_vertical(bat);
	       		for(i=bat->coord.y,compteur =0;i<=fin_bat; i++){
       				actuel.x=bat->coord.x;
       				actuel.y=bat->coord.y;
       				if(i==bat->coord.y){ 
					actuel.x--;
					if(danslagrille(taille, actuel)){
							case_nonlibres[compteur] = actuel;
							compteur++;
					}
					actuel.x++;		
					case_nonlibres[compteur] = actuel;
					compteur++;
					actuel.x++;
					if(danslagrille(taille, actuel)){
						case_nonlibres[compteur] = actuel;
						compteur++;
					}
					actuel.y--;
					if(danslagrille(taille, actuel)){
						case_nonlibres[compteur] = actuel;
						compteur++;
					}
       					actuel.x--;
					if(danslagrille(taille, actuel)){
						case_nonlibres[compteur] = actuel;
						compteur++;
					}
					actuel.x--;
					if(danslagrille(taille, actuel)){
						case_nonlibres[compteur] = actuel;
						compteur++;
					}
				}
				else if(i==fin_bat){
					actuel.x--;
					if(danslagrille(taille, actuel)){
						case_nonlibres[compteur] = actuel;
						compteur++;
					}
					actuel.x++;
					case_nonlibres[compteur] = actuel;
					compteur++;
					actuel.x++;
					if(danslagrille(taille, actuel)){
						case_nonlibres[compteur] = actuel;
						compteur++;
					}
					actuel.y++;
					if(danslagrille(taille, actuel)){
							case_nonlibres[compteur] = actuel;
							compteur++;
					}
       					actuel.x--;
					if(danslagrille(taille, actuel)){
							case_nonlibres[compteur] = actuel;
							compteur++;
					}
					actuel.x--;
					if(danslagrille(taille, actuel)){
						case_nonlibres[compteur] = actuel;
						compteur++;
					}
				}
				else{
					case_nonlibres[compteur].x =actuel.x ;
					case_nonlibres[compteur].y =actuel.y ; 
					actuel.x--;
					if(danslagrille(taille, actuel)){
						case_nonlibres[compteur] = actuel;
						compteur++;
					}
					actuel.x++;
					case_nonlibres[compteur] = actuel;
					compteur++;
					actuel.x++;
					if(danslagrille(taille, actuel)){
						case_nonlibres[compteur] = actuel;
						compteur++;
					}
				}
			}
		}
		if(bat->dir == horizontal){
			fin_bat = fin_bateau_horizontal(bat);
       			for(i=bat->coord.x,compteur =0;i<=fin_bat; i++){
       				actuel.x=bat->coord.x;
       				actuel.y=bat->coord.y;
       				if(i==bat->coord.x){ 
					actuel.y--;
					if(danslagrille(taille, actuel)){	
						case_nonlibres[compteur] = actuel;
						compteur++;
					}
					actuel.y++;
					case_nonlibres[compteur] = actuel;
					compteur++;
					actuel.y++;
					if(danslagrille(taille, actuel)){
						case_nonlibres[compteur] = actuel;
						compteur++;
					}
					actuel.x--;
					if(danslagrille(taille, actuel)){
						case_nonlibres[compteur] = actuel;
						compteur++;
					}
       					actuel.y--;
					if(danslagrille(taille, actuel)){
						case_nonlibres[compteur] = actuel;
						compteur++;
					}
					actuel.y--;
					if(danslagrille(taille, actuel)){
						case_nonlibres[compteur] = actuel;
						compteur++;
					}
				}
				else if(i==fin_bat){
					actuel.y--;
					if(danslagrille(taille, actuel)){
						case_nonlibres[compteur] = actuel;
						compteur++;
					}
					actuel.y++;
					case_nonlibres[compteur] = actuel;
					compteur++;
					actuel.y++;
					if(danslagrille(taille, actuel)){
						case_nonlibres[compteur] = actuel;
						compteur++;
					}
					actuel.x++;
					if(danslagrille(taille, actuel)){
						case_nonlibres[compteur] = actuel;
						compteur++;
					}
       					actuel.y--;
					if(danslagrille(taille, actuel)){
						case_nonlibres[compteur] = actuel;
						compteur++;
					}
					actuel.y--;
					if(danslagrille(taille, actuel)){
						case_nonlibres[compteur] = actuel;
						compteur++;
					}
				}
				else{
					case_nonlibres[compteur].x =actuel.x ;
					case_nonlibres[compteur].y =actuel.y ; 
					actuel.y--;
					if(danslagrille(taille, actuel)){
						case_nonlibres[compteur] = actuel;
						compteur++;
					}
					actuel.y++;
					case_nonlibres[compteur] = actuel;
					compteur++;
					actuel.y++;
					if(danslagrille(taille, actuel)){
						case_nonlibres[compteur] = actuel;
						compteur++;
					}
				}
			}			
		}
	}
	case_nonlibres[compteur].x = -1;
	case_nonlibres[compteur].y = -1;
}


int placement_bateau(t_liste joueur, bateau_t * bat, dir_t dir, case_t emp, int taille_mat){
	int i, j;
	int result= 1;
	case_t *casesprises = malloc(sizeof(case_t)*taille_mat*taille_mat);
	cases_prises(joueur, casesprises,taille_mat);
	if(dir == vertical){
		for(i=emp.y; i<(bat->taille+emp.y) && result; i++){
			for(j=0; casesprises[j].y != -1 && result; j++){
				if(casesprises[j].y == i && casesprises[j].x == emp.x){
					printf("Erreur : le bateau ne peut pas �tre plac� ici");
					result = 0;
				}
			}
		}
    }
    else {//if(dir == horizontal){
		for(i=emp.x; i<(bat->taille+emp.x) && result; i++){
			for(j=0; casesprises[j].x != -1 && result; j++){
				if(casesprises[j].x == i && casesprises[j].y == emp.y){
					printf("Erreur : le bateau ne peut pas �tre plac� ici");
					result = 0;
				}
			}
		}
    }
    if(result){
	    bat->coord.x = emp.x;
	    bat->coord.y = emp.y;
	    bat->dir = dir;
	    bat->etat = flotte;
	    bat->nb_touche = 0;
	    en_queue(&joueur);
	    ajout_droit(&joueur, *bat);
	}
	free(casesprises);    
    return result;
}

	
int placer_bateau(t_liste joueur, int taille_mat){
	type_t nom_bat;
	int dir_donne;
	int type_donne;
	dir_t direction;
	case_t emp;
	bateau_t * nouv;
	printf("Quel est le nom du bateau que vous voulez placer ?(donner un entier selon : mine=1 ,torpilleur=2, sousmarin=3,  croiseur=4 ou porteavion=5)");
	scanf("%i", &type_donne);
	if(type_donne <= 5 && type_donne >= 1){
		nouv->type = type_donne;
	}
	en_tete(&joueur);
	valeur_elt(&joueur, nouv);
	while(!hors_liste(&joueur) || nouv->type == nom_bat){
		valeur_elt(&joueur, nouv);
		suivant(&joueur);
	}
	if(!hors_liste(&joueur)){
		printf("Dans quelle direction voulez-vous placer le bateau ?(donner un entier selon : vertical = 1, horizontal = 2)");
		scanf("%i", &dir_donne);
		if(dir_donne <= 2 && dir_donne >= 1){
			direction = dir_donne;
		}
		do{
			printf("Quelles sont les coordonn�es a laquelle vous voulez placer le bateau ?(entre 1 et %i) \n x = ", taille_mat);
			scanf("%i", &emp.x);
		}while(emp.x <1 || emp.x > taille_mat);
		
		do{
			printf("\n y = ");
			scanf("%i", &emp.y);
		}while(emp.y < 1 || emp.y > taille_mat);
		if(placement_bateau(joueur, nouv, direction, emp, taille_mat)){
			printf("Le bateau a �t� plac�");
			free(nouv);
			return 1;
		}
		else{
			printf("Le bateau n'a pas pu �tre plac�");
			return 0;
		}
	}
}


int choixbateau(t_liste joueur, int taille){
       init_liste(&joueur);
       int nbbat=0;
       int t;
       int res=0;
       bateau_t nouveau;
       int nbmaxbat = (0,06 * (taille*taille)) - (0,3 * taille) +2;
       while(nbbat<= 0 || nbbat > nbmaxbat){
              printf("Combien de b�teau voulez-vous avoir ?(diff�rent de 0 et inf�rieur � : %i) : ", nbmaxbat);
              scanf("%i", &nbbat);
       }
       
       for(int i=0; i<nbbat;i++){
              printf("Ecrire la taille du %i bateau(entre 1 et 5) : ",i);
              if(i<=5 && i>=1){
                     scanf("%i", &t);
                     en_tete(&joueur);
                     nouveau.taille = t;
                     nouveau.coord.x = -1;
                     nouveau.coord.y = -1;
                     nouveau.dir = aucun;
                     nouveau.type = aucun;
                     nouveau.etat = flotte;
                     nouveau.nb_touche = 0;
                     ajout_droit(&joueur, nouveau);
              }
       }
       type_bateau(joueur);
       placer_bateau(joueur, taille);
}




int bateau_plus_petit(t_liste joueur){
	int min = 5;
	bateau_t * actuel;
	en_tete(&joueur);
	while(!hors_liste(&joueur)){
		valeur_elt(&joueur, actuel);
		if(actuel->taille < min){
			min = actuel->taille;
		}
		suivant(&joueur);
	}
	return min;
}
