/*!
* \file main.c
* \brief Fichier source contenant
* \version 1.0
* \date 25/12/2020
* \author Maxime SZYMANSKI Jules PETRY
* -# Ligne principale du jeu :
* Differentes fonctions des differents fichiers sources sont appelees afin de faire fonctionner le programme.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "craft.h"
#include "all.h"
#define MAX_SIZE 1000


int main()
{   system("title TextCraft");

	etiq1:
	system("cls");
	srand(time(NULL));
    bool repetition = false;
    liste_fait deduction;
    deduction = creer_liste_fait();

	BTree t = creer_arbre(2);
	BTree l = creer_arbre(1);
	BTree r = creer_arbre(3);
	t = enraciner(l,r,t);

	Joueur j;
    j = creer_joueur();
    int choice;

    choice = 0;

    do{
    	system("cls");

		choice = menu_accueil();

	    int est_quitte = 0;
	    char chaine[MAX_SIZE] = "";
	    FILE* file = NULL;

		switch(choice){
			case 1:

				/*MISE EN ROUTE DU JEU*/
				system("cls");
				commande_regarder(j);
				while(est_quitte != 1){

					if(j->vie <= 0){

						j->score += nombre_noeuds(t);
						menu_perdu(j, t);
						system("pause");
						detruire_inv(j->inv);
						detruire_arbre(t);
						detruire_joueur(j);
						goto etiq1;
					}
			        j->liste_craft = Remise_a_zero_base_connaissance(j->liste_craft);

					j->craft_faisable = moteur_inference(j->liste_craft,j->craft_faisable,&deduction,&repetition);

					est_quitte = saisie_joueur();
					j = gestion_commande_arg1(j, t,deduction);
					j = attaquer_joueur(j, t);
					t = extansion(j, t);

					deduction = creer_liste_fait();
					}
				j->score += nombre_noeuds(t);
				menu_perdu(j, t);
				system("pause");
				detruire_inv(j->inv);
				detruire_arbre(t);
				detruire_joueur(j);
				goto etiq1;

				break;

				/*---------------------*/

			case 2:

				system("cls");

				file = fopen("regle_du_jeu.txt", "r");

		        if (file != NULL)
		        {
		            //Read
		            while(fgets(chaine, MAX_SIZE, file) != NULL)
		            {
		                printf("%s", chaine); //print
		            }
		            //End of reading and writing
		            fclose(file);
		        }
		        else
		        {
		            printf("Failed while opening the file foret.txt\n");
		            fclose(file);
		        }
		        printf("\n");
		        system("pause");

				break;

			case 0:
				return EXIT_SUCCESS;
		}
	}while(choice != 1);

	detruire_inv(j->inv);
	detruire_arbre(t);
	detruire_joueur(j);

	return 0;
}
