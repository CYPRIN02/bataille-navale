#include <stdio.h>
#include <stdlib.h>
#include "liste.h"
#include "listebateau.h"
#include "matricepion.h"
#include "bateau.h"


// En fonction de la case choisis, renvoie une valeur suivant si le tir touche, coule ou rate
int etat_tir( matrice_t matrice , coord_t cell, t_liste joueur){
		return veriftouche(cell, matrice, joueur);
}


// pour chaque bateau, verifie son l'état du tir
int veriftouche(coord_t cell, matrice_t matrice, t_liste joueur){
	int touche;
	bateau_t * actueltemp;
	en_tete(&joueur);
	while(!hors_liste(&joueur)){
		valeur_elt(&joueur,actueltemp);
		touche=toucheunbateau( matrice, cell, actueltemp);
		if(touche!=0){
			return touche;
		}
		suivant(&joueur);
	}
	return touche;
}


// vérifie si toute la flotte est coulée
int bateaux_coules( t_liste joueur, int nb_bat){
	bateau_t * bateau;
	int c_bat_coul=0;
	while(!hors_liste(&joueur)){
		valeur_elt(&joueur,bateau);
		c_bat_coul+=bat_coul(bateau, nb_bat);
		suivant(&joueur);
	}
	if(c_bat_coul==nb_bat){
		return 1;
	}
	return 0;
}


int type_bateau(t_liste joueur){
	en_tete(&joueur);
	bateau_t *actuel;
	if(liste_vide(&joueur)){
			return 0;
	}
	while(!hors_liste(&joueur)){
		valeur_elt(&joueur, actuel);
		modif_type_bat(actuel);
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


// Voir avec la SDL. Ici version terminal
void affichage_flotte(t_liste joueur, matrice_t matrice){
	bateau_t * actuel;
	for(int i=0; i<matrice.nbl ; i++){
       		for(int j=0; j<matrice.nbc ; j++){
       			en_tete(&joueur);
       			while(!hors_liste(&joueur)){
       				valeur_elt(&joueur, actuel);
       				afficher_bateau(actuel, i, j);
	       			suivant(&joueur);
	       		}
       		}
		printf("\n");
	}
}

/* remplit case_non,libres avec les cases occupées*/
void cases_prises(t_liste joueur, coord_t* case_nonlibres, matrice_t matrice ){
	bateau_t *bat;
	int fin_bat;
	int i, compteur;
	coord_t actuel;
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
					if(danslagrille(matrice, actuel)){
							case_nonlibres[compteur] = actuel;
							compteur++;
					}
					actuel.x++;
					case_nonlibres[compteur] = actuel;
					compteur++;
					actuel.x++;
					if(danslagrille(matrice, actuel)){
						case_nonlibres[compteur] = actuel;
						compteur++;
					}
					actuel.y--;
					if(danslagrille(matrice, actuel)){
						case_nonlibres[compteur] = actuel;
						compteur++;
					}
       					actuel.x--;
					if(danslagrille(matrice, actuel)){
						case_nonlibres[compteur] = actuel;
						compteur++;
					}
					actuel.x--;
					if(danslagrille(matrice, actuel)){
						case_nonlibres[compteur] = actuel;
						compteur++;
					}
				}
				else if(i==fin_bat){
					actuel.x--;
					if(danslagrille(matrice, actuel)){
						case_nonlibres[compteur] = actuel;
						compteur++;
					}
					actuel.x++;
					case_nonlibres[compteur] = actuel;
					compteur++;
					actuel.x++;
					if(danslagrille(matrice, actuel)){
						case_nonlibres[compteur] = actuel;
						compteur++;
					}
					actuel.y++;
					if(danslagrille(matrice, actuel)){
							case_nonlibres[compteur] = actuel;
							compteur++;
					}
       					actuel.x--;
					if(danslagrille(matrice, actuel)){
							case_nonlibres[compteur] = actuel;
							compteur++;
					}
					actuel.x--;
					if(danslagrille(matrice, actuel)){
						case_nonlibres[compteur] = actuel;
						compteur++;
					}
				}
				else{
					case_nonlibres[compteur].x =actuel.x ;
					case_nonlibres[compteur].y =actuel.y ;
					actuel.x--;
					if(danslagrille(matrice, actuel)){
						case_nonlibres[compteur] = actuel;
						compteur++;
					}
					actuel.x++;
					case_nonlibres[compteur] = actuel;
					compteur++;
					actuel.x++;
					if(danslagrille(matrice, actuel)){
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
					if(danslagrille(matrice, actuel)){
						case_nonlibres[compteur] = actuel;
						compteur++;
					}
					actuel.y++;
					case_nonlibres[compteur] = actuel;
					compteur++;
					actuel.y++;
					if(danslagrille(matrice, actuel)){
						case_nonlibres[compteur] = actuel;
						compteur++;
					}
					actuel.x--;
					if(danslagrille(matrice, actuel)){
						case_nonlibres[compteur] = actuel;
						compteur++;
					}
       					actuel.y--;
					if(danslagrille(matrice, actuel)){
						case_nonlibres[compteur] = actuel;
						compteur++;
					}
					actuel.y--;
					if(danslagrille(matrice, actuel)){
						case_nonlibres[compteur] = actuel;
						compteur++;
					}
				}
				else if(i==fin_bat){
					actuel.y--;
					if(danslagrille(matrice, actuel)){
						case_nonlibres[compteur] = actuel;
						compteur++;
					}
					actuel.y++;
					case_nonlibres[compteur] = actuel;
					compteur++;
					actuel.y++;
					if(danslagrille(matrice, actuel)){
						case_nonlibres[compteur] = actuel;
						compteur++;
					}
					actuel.x++;
					if(danslagrille(matrice, actuel)){
						case_nonlibres[compteur] = actuel;
						compteur++;
					}
       					actuel.y--;
					if(danslagrille(matrice, actuel)){
						case_nonlibres[compteur] = actuel;
						compteur++;
					}
					actuel.y--;
					if(danslagrille(matrice, actuel)){
						case_nonlibres[compteur] = actuel;
						compteur++;
					}
				}
				else{
					case_nonlibres[compteur].x =actuel.x ;
					case_nonlibres[compteur].y =actuel.y ;
					actuel.y--;
					if(danslagrille(matrice, actuel)){
						case_nonlibres[compteur] = actuel;
						compteur++;
					}
					actuel.y++;
					case_nonlibres[compteur] = actuel;
					compteur++;
					actuel.y++;
					if(danslagrille(matrice, actuel)){
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


int placement_bateau(t_liste joueur, bateau_t * bat, dir_t dir, coord_t emp, matrice_t matrice){
	int * result= 1;
	coord_t *casesprises = malloc(sizeof(coord_t)*matrice.nbl*matrice.nbc);
	cases_prises(joueur, casesprises,matrice);
	verif_placement_bateau(bat, emp, casesprises, result);
    if(result){
    	modif_coord(bat, emp);
    	modif_direction(bat, dir);
	    en_queue(&joueur);
	    ajout_droit(&joueur, *bat);
	}
	free(casesprises);
    return result;
}


int placer_bateau(t_liste joueur, matrice_t matrice){
	type_t nom_bat;
	int dir_donne, type_donne;
	dir_t direction;
	coord_t emp;
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
		
		do{
			printf("Dans quelle direction voulez-vous placer le bateau ?(donner un entier selon : vertical = 1, horizontal = 2)");
			scanf("%i", &dir_donne);
			if(dir_donne ==1){
				direction = VERTICAL;
			}
			else if(dir_donne == 2){
				direction = HORIZONTAL;
			}
			else{
				printf("mauvaise direction");
			}
		}while(dir_donne >2 || dir_donne <1);
		
		if(direction == VERTICAL){
			do{
				printf("Quelles sont les coordonnées a laquelle vous voulez placer le bateau ?(entre 1 et %i) \n x = ", matrice.nbl);
				scanf("%i", &emp.x);
			}while(emp.x <1 || emp.x > matrice.nbc);
	
			do{
				printf("\n y = ");
				scanf("%i", &emp.y);
			}while(emp.y < 1 || emp.y > matrice.nbl);
		}
		
		else{
			do{
				printf("Quelles sont les coordonnées a laquelle vous voulez placer le bateau ?(entre 1 et %i) \n x = ", matrice.nbl);
				scanf("%i", &emp.x);
			}while(emp.x <1 || emp.x > matrice.nbl);
	
			do{
				printf("\n y = ");
				scanf("%i", &emp.y);
			}while(emp.y < 1 || emp.y > matrice.nbc);
		}
		
		if(placement_bateau(joueur, nouv, direction, emp, matrice)){
			printf("Le bateau a été placé");
			free(nouv);
			return 1;
		}
		free(nouv);
		printf("Le bateau n'a pas pu être placé");
		return 0;
	}
}


int choixbateau(t_liste joueur, matrice_t matrice){
       init_liste(&joueur);
       int nbbat=0;
       int t;
       int res=0;
       bateau_t nouveau;
       int nbmaxbat = (0,06 * (matrice.nbc*matrice.nbl)) - (0,3 * matrice.nbl) +2;
       while(nbbat<= 0 || nbbat > nbmaxbat){
              printf("Combien de bâteau voulez-vous avoir ?(différent de 0 et inférieur à : %i) : ", nbmaxbat);
              scanf("%i", &nbbat);
       }

       for(int i=0; i<nbbat;i++){
              printf("Ecrire la taille du %i bateau(entre 1 et 5) : ",i);
              if(i<=5 && i>=1){
                     scanf("%i", &t);
                     en_tete(&joueur);
                     nouveau_bateau(t, *nouveau)
                     ajout_droit(&joueur, nouveau);
              }
       }
       type_bateau(joueur);
       placer_bateau(joueur, matrice);
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




