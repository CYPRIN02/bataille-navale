#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <fcntl.h>
#define PORT 32000
#define ip "127.0.0.1"
#include "bateau.h"
#include "matricepion.h"
#include "liste.h"
#include "listebateau.h"
#include "IA_bateaux.h"
#include "IA_pions.h"
#include "matrice.h"



void tcp_connection_client(int * client_fd)
{
    struct sockaddr_in serv_addr;
    int port_no=PORT;
    //char *ip = malloc(200);

    printf("\n Entrez l'@IP du serveur : DEJA FAIT ");
	//scanf("%s", ip);




    *client_fd = socket(AF_INET, SOCK_STREAM, 0);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(ip);
    serv_addr.sin_port = htons(port_no);


    if( connect(*client_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
    {
        perror("Connexion impossible, verifiez que le serveur est démarré ! \n");
        exit(0);
    }
    printf("\n -- CONNECTE -- \n");
}

int main() {
	system("clear");
	printf("\n -- BATAILLE NAVALE EN RESEAU - CLIENT --\n");

    int choix_c_atk = -1;
    int choix_c_atk2 = -1;
    int question;
    int server_fd, client_fd;
    int nb_cli;
    int nb_joueur;
  	int tour_atk;
  	int choix_j_atk;
  	int i;
  	int nb_joueur_atk;
  	int info_j_atk;
  	int info_c_atk;
  	int info_c_atk2;
    matrice_pion_t mat;
    matrice_pion_t mat2;
    matrice_pion_t mat3;
    matrice_pion_t mat4;
    matrice_pion_t mat5;




    tcp_connection_client(&client_fd);
    recv(client_fd, &nb_joueur, sizeof(nb_joueur), 0);
    recv(client_fd, &nb_cli, sizeof(nb_cli), 0);




    printf("\n La partie est constituée de %i joueurs \n", nb_cli);
    printf("\n Tu es le joueur %i \n", nb_joueur+1);

     //Choix de la grille
    if(nb_joueur+1==1){
      mat=choixgrille(mat);
      init_matrice_adv(mat);
      send(client_fd, &mat.nbc, sizeof(mat.nbc), 0);
      send(client_fd, &mat.nbl, sizeof(mat.nbl), 0);
      send(client_fd, mat.grille[0], sizeof(case_t)*mat.nbl*mat.nbc, 0);
    }
    printf(" \n ----------------------------------------------------------------------------- \n");

    switch(nb_cli){
		case 5 :recv(client_fd, &mat5.nbc, sizeof(mat5.nbc), 0);
				recv(client_fd, &mat5.nbl, sizeof(mat5.nbl), 0);
        mat5=creer_matrice_adv(mat5.nbl, mat5.nbc);
				recv(client_fd, mat5.grille[0], sizeof(case_t)*mat5.nbl*mat5.nbc, 0);

		case 4 :recv(client_fd, &mat4.nbc, sizeof(mat4.nbc), 0);
				recv(client_fd, &mat4.nbl, sizeof(mat4.nbl), 0);
        mat4=creer_matrice_adv(mat4.nbl, mat4.nbc);
				recv(client_fd, mat4.grille[0], sizeof(case_t)*mat4.nbl*mat4.nbc, 0);

		case 3 :recv(client_fd, &mat3.nbc, sizeof(mat3.nbc), 0);
				recv(client_fd, &mat3.nbl, sizeof(mat3.nbl), 0);
        mat3=creer_matrice_adv(mat3.nbl, mat3.nbc);
				recv(client_fd, mat3.grille[0], sizeof(case_t)*mat3.nbl*mat3.nbc, 0);

		case 2 :recv(client_fd, &mat2.nbc, sizeof(mat2.nbc), 0);
				recv(client_fd, &mat2.nbl, sizeof(mat2.nbl), 0);
        mat2=creer_matrice_adv(mat2.nbl, mat2.nbc);
				recv(client_fd, mat2.grille[0], sizeof(case_t)*mat2.nbl*mat2.nbc, 0);

				recv(client_fd, &mat.nbc, sizeof(mat.nbc), 0);
				recv(client_fd, &mat.nbl, sizeof(mat.nbl), 0);
        mat=creer_matrice_adv(mat.nbl, mat.nbc);
				recv(client_fd, mat.grille[0], sizeof(case_t)*mat.nbl*mat.nbc, 0);

		default : break;
	}
	switch(nb_cli){
		case 5 : if(nb_joueur+1!=5){
					printf(" Affichage de la grille de l'adversaire 5 \n\n");
					afficher_matrice_pion(mat5);
				}

		case 4 :if(nb_joueur+1!=4){
					printf(" Affichage de la grille de l'adversaire 4 \n\n");
					afficher_matrice_pion(mat4);
				}

		case 3 :if(nb_joueur+1!=3){
					printf(" Affichage de la grille de l'adversaire 3 \n\n");
					afficher_matrice_pion(mat3);
				}

		case 2 :if(nb_joueur+1!=2){
					printf(" Affichage de la grille de l'adversaire 2 \n\n");
					afficher_matrice_pion(mat2);
				}
				if(nb_joueur+1!=1){
					printf(" Affichage de la grille de l'adversaire 1 \n\n");
					afficher_matrice_pion(mat);
				}
		default : break;
	}

  	while (1){
		recv(client_fd, &tour_atk, sizeof(tour_atk), 0);
		printf("\n \n ----------------------------------------------------------------------------- \n");
		printf(" Tour de  %i \n", tour_atk);
		if(tour_atk==nb_joueur+1){
      printf("Le nombre de joueurs est de %i",nb_cli);
      if(nb_cli!=2){
        do{
        	printf("\n Qui voulez-vous attaquer ? ");
  			scanf("%i", &choix_j_atk);
  			if(choix_j_atk<1 || choix_j_atk>nb_cli){
  				printf("Le numéro du joueur est inexistant. Veuillez entrer un numéro de joueur compris entre 1 et %d \n", nb_cli );
  			}
        if(choix_j_atk== nb_joueur+1){
          printf("Vous ne pouvez vous attaquer vous-même !\n");
        }
  		}while(choix_j_atk<1 || choix_j_atk>nb_cli || choix_j_atk==nb_joueur+1);
        send(client_fd, &choix_j_atk, sizeof(choix_j_atk), 0);
      }
			do{
				printf("\n Quelle case voulez-vous attaquer ( de la forme \"x y\")? ");
				scanf("%i %i", &choix_c_atk, &choix_c_atk2);
				if(choix_c_atk==-1 || choix_c_atk2==-1){
					printf("Une case contient une abcisse et une ordonnée. Veuillez rentrer les deux champs. Ex de case valide : 2 5\n");
				}
			}while( choix_c_atk==-1 || choix_c_atk2==-1);
			send(client_fd, &choix_c_atk, sizeof(choix_c_atk), 0);
			send(client_fd, &choix_c_atk2, sizeof(choix_c_atk2), 0);
			printf("\n Envoyé \n");
			recv(client_fd, &info_j_atk, sizeof(info_j_atk), 0);
			recv(client_fd, &info_c_atk, sizeof(info_c_atk), 0);
			recv(client_fd, &info_c_atk2, sizeof(info_c_atk2), 0);
			printf(" ----------------------------------------------------------------------------- \n \n");
		}
		else{
			recv(client_fd, &info_j_atk, sizeof(info_j_atk), 0);
			recv(client_fd, &info_c_atk, sizeof(info_c_atk), 0);
			recv(client_fd, &info_c_atk2, sizeof(info_c_atk2), 0);

			if( info_j_atk == nb_joueur+1){
				printf("\n Le joueur %i vous attaque en case n° %i %i\n", tour_atk, info_c_atk, info_c_atk2);

			}else{
				printf("\n Le joueur %i attaque le joueur %i en case n° %i %i\n", tour_atk, info_j_atk, info_c_atk, info_c_atk2);
			}
			printf(" ----------------------------------------------------------------------------- \n \n");
		}

	}
}
