#ifndef __LISTEBATEAU_H__
#define __LISTEBATEAU_H__


#include "matricepion.h"
#include "liste.h"
#include "bateau.h"

int etat_tir( int taille, coord_t cell, t_liste joueur);
int veriftouche(coord_t cell, matrice_t matrice, t_liste joueur)
int bateaux_coules( t_liste joueur, int nb_bat);
void type_bateau(t_liste);
void appliquer_bateau(t_liste,t_liste);
void affichage_flotte(t_liste joueur, matrice_t)
void cases_prises(t_liste, coord_t *, int);
int placement_bateau(t_liste, bateau_t *, dir_t, coord_t, int);
void placer_bateau(t_liste, int);
void choixbateau(t_liste,int);
int bateau_plus_petit(t_liste);

#endif
