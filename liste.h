#ifndef __LISTE_H__
#define __LISTE_H__
#include "bateau.h"

typedef struct element{
	bateau_t bateau; 
	struct element * pred; 
	struct element * succ;
}t_element;

typedef struct {
	t_element * drapeau;
	t_element * ec;
}t_liste;






void init_liste(t_liste*);
int liste_vide(t_liste*);
int hors_liste(t_liste*);
void en_tete(t_liste*);
void en_queue(t_liste*);
void precedent(t_liste*);
void suivant(t_liste*);
void valeur_elt(t_liste*, bateau_t*);
void modif_elt(t_liste*, bateau_t*);
void oter_elt(t_liste*);
void ajout_droit(t_liste*, bateau_t);
void ajout_gauche(t_liste*, bateau_t);

#endif
