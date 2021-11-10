/*!
* \file inventaire.c
* \brief Fichier source des fonctions relative a l'inventaire du joueur
* \version 1.0
* \date 25/12/2020
* \author Maxime SZYMANSKI Jules PETRY
* -# Gestion de l'inventaire du joueur :
* L'inventaire est creer puis les elements sont ajoutes ou supprimes en fonction des actions du joueur dans le jeu.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "all.h"



Liste_inv ajout_inv(Liste_inv inv, int quantite, char* nom)
{
	if(est_inv(inv, nom) == true){
		Liste_inv temp = inv;

		while(strcmp(temp->nom, nom) != 0){
			temp = temp->next;
		}
		temp->quantite += quantite;
		return inv;

	}else{

		Liste_inv newel;
		newel = malloc(sizeof(elem));
		newel->nom = malloc((strlen(nom)+1)*sizeof(char));

		newel->quantite = quantite;
		strcpy(newel->nom, nom);
		newel->next = inv;

		return newel;
	}
}

Liste_inv supp_item_inv(Liste_inv inv, char* nom, int quantite)
{

	Liste_inv temp;

    //CAS OU LE MOT A SUPPRIMER EST LE PREMIER DE LA LISTE
    if(strcmp(inv->nom , nom) == 0){
        if(inv == NULL){
            inv = NULL;
        }else{

        	if(inv->quantite == quantite){
        		printf("debug\n");
        		printf("Element supprime : %d de %s\n", quantite, inv->nom);
            	temp = inv->next;
            	free(inv);
            	return temp;
        	}else{

        		inv->quantite -= quantite;
        		printf("Element supprime : %d de %s\n", quantite, inv->nom);
        	}
        }

    }else{

    /*CAS OU LE MOT A SUPPRIMER N'EST PAS LE PREMIER*/

    	temp = inv;

        while(strcmp(temp->next->nom , nom) != 0)  /*On parcourt la liste jusqu'a ce que la prochaine proposition soit celle qui faut supp*/
        {
            temp = temp->next;
        }

        if(temp->next->quantite == quantite){
        	Liste_inv temp2;
        	temp2 = temp->next->next;
        	printf("Element supprime : %d de %s\n", quantite, temp->next->nom);
        	free(temp->next);
        	temp->next = temp2;
        }else{
        	temp->next->quantite -= quantite;
        	printf("Element supprime : %d de %s\n", quantite, temp->next->nom);
        }
    }
    return inv;
}


void afficher_inv(Joueur j)
{
	Liste_inv inv = j->inv;

	if(inv == NULL){
		printf("Vie : %d\n\n", j->vie);
		printf("Votre inventaire est vide\n");
	}else{
		Liste_inv temp = inv;
		printf("\n");
		printf("|----------INVENTAIRE----------|\n\n");
		printf("Vie : %d\n\n", j->vie);
		while(temp->next != NULL){
			printf("%s : %d\n",temp->nom, temp->quantite);
			temp = temp->next;
		}
		printf("%s : %d\n\n",temp->nom, temp->quantite);
		printf("|------------------------------|\n");
	}
}

Liste_inv creer_inv(void)
{
	Liste_inv inv;
	inv = malloc(sizeof(elem));
	inv = NULL;
	return inv;
}

bool est_inv(Liste_inv inv, char* nom)
{
	if(inv == NULL){
		return false;
	}else if(strcmp(inv->nom, nom) == 0){
		return true;
		}else{
			est_inv(inv->next, nom);
		}
}

int quantite_item(Liste_inv inv, char* nom)
{
	Liste_inv temp = inv;

	if(est_inv(inv, nom) == true){				/*VERIFICATION QUE LE JOUEUR POSSEDE BIEN CET ITEM DANS SON INV*/
		while(strcmp(temp->nom, nom) != 0){
			temp = temp->next;
		}
		return temp->quantite;
	}else{
		return 0;
	}
}

void detruire_inv(Liste_inv inv)
{
	if(inv == NULL){
		return;
	}else{
		detruire_inv(inv->next);
		free(inv);
	}
}





