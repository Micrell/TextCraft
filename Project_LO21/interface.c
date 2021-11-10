/*!
* \file interface.c
* \brief Fichier source des fonctions relative aux interfaces
* \version 1.0
* \date 25/12/2020
* \author Maxime SZYMANSKI Jules PETRY
* -# Affichage des menus :
* Differents menus sont affiches en fonction des besoins du programme.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "craft.h"
#include "all.h"

int menu_accueil(void)
{
	printf("88888888888                888     .d8888b.                   .d888 888    \n");
    printf("    888                    888    d88P  Y88b                 d88P   888    \n");
	printf("    888                    888    888    888                 888    888    \n");
	printf("    888   .d88b.  888  888 888888 888        888d888 8888b.  888888 888888 \n");
	printf("    888  d8P  Y8b `Y8bd8P' 888    888        888P        88b 888    888    \n");
    printf("    888  88888888   X88K   888    888    888 888    .d888888 888    888    \n");
    printf("    888  Y8b.     .d8  8b. Y88b.  Y88b  d88P 888    888  888 888    Y88b.  \n");
    printf("    888    Y8888  888  888   Y888   Y8888P   888     Y888888 888      Y888 \n");
    printf("\n\n\n");
    printf("Bienvenue dans TextCraft. Plongez vous dans une petite aventure dans la vie sauvage ou vous allez devoir trouver des elements pour en creer d'autres et vaincre les monstres\n");

    printf("1: Commencer une partie\n");
    printf("2: Afficher les regles du jeu\n");
    printf("0: quitter\n");

    int choice;

    do{
        printf("\n->");
    	choice = getch();
    	choice =choice   - 48;

    }while(choice < 0 || choice > 3);

    return choice;
}

void menu_perdu(Joueur j, BTree t)
{
    system("cls");

    printf("8888888b.  8888888888 8888888b.  8888888b.  888     888\n");
    printf("888   Y88b 888        888   Y88b 888  'Y88b 888     888\n");
    printf("888    888 888        888    888 888    888 888     888\n");
    printf("888   d88P 8888888    888   d88P 888    888 888     888\n");
    printf("8888888P'  888        8888888P   888    888 888     888\n");
    printf("888        888        888 T88b   888    888 888     888\n");
    printf("888        888        888  T88b  888  .d88P Y88b. .d88P\n");
    printf("888        8888888888 888   T88b 8888888P'   'Y88888P' \n");
    printf("\n\n\n");
    printf("Vous etes mort\n\n");
    printf("Pseudo : %s\n", j->pseudo);
    printf("Votre score : %d\n", j->score);
    printf("Part du score Decouverte : %d\n", nombre_noeuds(t));
    printf("Part du score craft / kill : %d\n", ((j->score)-(nombre_noeuds(t))));
}
