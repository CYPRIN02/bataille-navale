#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <fcntl.h>
#define PORT 32000
void tcp_connection_client(int * client_fd)
{
    struct sockaddr_in serv_addr;
    int port_no=PORT;
    char *ip = malloc(200);

    printf("\nEntrez l'@IP du serveur : ");
	scanf("%s", ip);




    *client_fd = socket(AF_INET, SOCK_STREAM, 0);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(ip);
    serv_addr.sin_port = htons(port_no);


    if( connect(*client_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
    {
        perror("Connexion impossible, verifiez que le serveur est démarré ! \n");
        exit(0);
    }
    printf(" -- CONNECTE -- \n");
}

int main() {
	system("clear");
	printf("\n -- BATAILLE NAVALE EN RESEAU - CLIENT --\n");

    int reponse=0;		
    int question;
    int server_fd, client_fd;
    int nb_cli;
    int nb_joueur;
    	int nb_joueur_atk;
    	int j_atk;
    
    tcp_connection_client(&client_fd);
    recv(client_fd, &nb_joueur, sizeof(nb_joueur), 0);	
    recv(client_fd, &nb_cli, sizeof(nb_cli), 0);


    printf("\n La partie est constituée de %i joueurs \n", nb_cli+1);
    printf("\n Tu es le joueur %i \n", nb_joueur+2);

    while (1==1){
    	recv(client_fd, &nb_joueur_atk, sizeof(nb_joueur_atk), 0);
		recv(client_fd, &j_atk, sizeof(j_atk), 0);
    	recv(client_fd, &reponse, sizeof(reponse), 0);
		
		while (reponse!=0){
				printf("\n Le joueur %i attaque le joueur %i en case n° %i \n \n", nb_joueur_atk, j_atk, reponse);
				reponse=0;
				/** printf("A mon tour, quelle case voulez-vous attaquer ? ");
				scanf("%i", &question);
				send(client_fd, &question, sizeof(question), 0);
				printf("\n"); **/
		
		}
	}


}

/**
		recv(client_fd, &reponse, sizeof(reponse), 0);
		printf("A mon tour, quelle case voulez-vous attaquer ? ");
		scanf("%i", &question);
		send(client_fd, &question, sizeof(question), 0);
		while (1==1){
		
			recv(client_fd, &reponse, sizeof(reponse), 0);
		

			while (reponse!=0){

				printf(" AIE ! - j'ai mal à la case : \n %i \n \n", reponse);
				reponse=0;
				printf("A mon tour, quelle case voulez-vous attaquer ? ");
				scanf("%i", &question);
				send(client_fd, &question, sizeof(question), 0);
				printf("\n");

		
		}
	}
	**/
