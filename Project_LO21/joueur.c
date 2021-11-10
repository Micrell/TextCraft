/*!
* \file joueur.c
* \brief Fichier source des fonctions relative au Joueur et son evolution dans le jeu
* \version 1.0
* \date 25/12/2020
* \author Maxime SZYMANSKI Jules PETRY
* -# Gestion de l'evolution du joueur:
* Les commandes sont prises en consideration et les fonctions correspondantes aux commandes sont appelees.
*/

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#define MAX_SIZE 1000
#include "all.h"
#include "craft.h"


static char saisie[50];


Joueur creer_joueur()
{

    Joueur j;
    j = malloc(sizeof(desc));

    char pseudo[21];

    printf("Quel pseudo voulez-vous prendre pour jouer ?\n");

    fflush(stdin);
    fgets(pseudo, 21, stdin);

    while(strlen(pseudo) > 20 || strlen(pseudo) < 2)
    {
        printf("Attention, votre pseudo est trop court ou trop long\n");
        fflush(stdin);
        fgets(pseudo, 21, stdin);
    }

    j->pseudo = malloc((strlen(pseudo)+1)*sizeof(char));
    strcpy(j->pseudo, pseudo);
    j->lieu = malloc(sizeof(lieu));
    j->lieu->monstre = malloc(sizeof(monstre));
    j->lieu->unique_id = 0;
    j->lieu->nom = 2;
    j->lieu->est_monstre = false;
    j->lieu->monstre->type = 0;
    j->lieu->monstre->vie = 0;
    j->inv = creer_inv();
    j->vie = 20;
    j->score = 0;
    j->craft_faisable = creer_liste_fait();
    j->liste_craft = creer_base_vide();
    j->liste_craft = lire_fichier_regle();

    return j;
}


Joueur gestion_commande_arg1(Joueur j, BTree t,liste_fait deduction)
{

    //liste_fait base_de_fait;
    //liste_regle BDC;
    //base_de_fait = creer_liste_fait();
    //BDC = lire_fichier_regle();

    char* arg1 = strtok(saisie, " \n");
    char* arg2 = strtok(NULL, " \n");

    if(strcmp(arg1, "aller") == 0)
    {
        j = commande_aller(arg2, j, t);

    }
    else if(strcmp(arg1, "regarder") == 0)
    {
        commande_regarder(j);

    }
    else if(strcmp(arg1, "quitter") == 0)
    {
        printf("Vous quittez le jeu\n");

    }
    else if(strcmp(arg1, "inventaire") == 0)
    {
        afficher_inv(j);

    }
    else if(strcmp(arg1, "couper") == 0)
    {
        j = couper_bois(j);

    }
    else if(strcmp(arg1, "miner") == 0)
    {
        j = miner_fer(j);

    }
    else if(strcmp(arg1, "craft") == 0)
    {
        j = craft(j,arg2,deduction);
    }
    else if(strcmp(arg1, "attaquer") == 0)
    {
        BTree temp1 = parcourir_arbre(j, t);
        bool monstre1 = temp1->lieu->est_monstre;

        t = attaquer_monstre(j, t);

        BTree temp2 = parcourir_arbre(j, t);
        bool monstre2 = temp2->lieu->est_monstre;

        if(monstre1 != monstre2){
            j->score++;
            printf("Vous score a augmenter de 1\n");
        }
    }
    else if(strcmp(arg1, "aide") == 0 || strcmp(arg1, "?") == 0)
    {
        printf("Liste des commandes : aller, regarder, inventaire, couper, miner, craft, attaquer, manger, quitter, aide\n");
    }
    else if(strcmp(arg1, "manger") == 0)
    {
        j = commande_manger(j);
    }
    else
    {
        printf("Commande inconnue\n");
    }
    return j;
}

Joueur commande_aller(char* arg2, Joueur j, BTree t)
{
    BTree temp = t;
    int int_arg2 = direction_en_nombre(arg2);
    temp = parcourir_arbre(j, temp);

    if(temp->lieu->est_monstre == true)
    {
        printf("\nVous ne pouvez pas avance car un monstre bloque le chemin. Tuez le pour pouvoir continuer.\n");
        printf("Vie du boss: %d\n", temp->lieu->monstre->vie);
    }else{

        if(int_arg2 == 0)
        {
            if(temp->parent != NULL)
            {
                printf("\nVous pouvez aller au NORD (nord) dans : %s", nombre_en_lieu(temp->parent->lieu->nom));
            }
            if(temp->left != NULL)
            {
                printf("\nVous pouvez aller au SUD-OUEST (s-o) dans : %s", nombre_en_lieu(t->left->lieu->nom));
            }
            if(temp->right != NULL)
            {
                printf("\nVous pouvez aller au SUD-EST (s-e) dans : %s", nombre_en_lieu(temp->right->lieu->nom));
            }

        }
        else if(int_arg2 == 4)
        {
            printf("\nVous etes dans : %s\n", nombre_en_lieu(temp->lieu->nom));

        }
        else if(int_arg2 == 2 && temp->parent != NULL)
        {
            j->lieu->unique_id = temp->parent->lieu->unique_id;
            j->lieu->nom = temp->parent->lieu->nom;
            j->lieu->est_monstre = temp->parent->lieu->est_monstre;
            j->lieu->monstre->type = temp->parent->lieu->monstre->type;
            j->lieu->monstre->vie = temp->parent->lieu->monstre->vie;
            commande_regarder(j);

            printf("\nVous allez dans : %s\n", nombre_en_lieu(temp->parent->lieu->nom));


        }
        else if(int_arg2 == 1 && temp->left != NULL)
        {
            j->lieu->unique_id = temp->left->lieu->unique_id;
            j->lieu->nom = temp->left->lieu->nom;
            j->lieu->est_monstre = temp->left->lieu->est_monstre;
            j->lieu->monstre->type = temp->left->lieu->monstre->type;
            j->lieu->monstre->vie = temp->left->lieu->monstre->vie;
            commande_regarder(j);

            printf("\nVous allez dans : %s\n", nombre_en_lieu(temp->left->lieu->nom));

        }
        else if(int_arg2 == 3 && temp->right != NULL)
        {
            j->lieu->unique_id = temp->right->lieu->unique_id;
            j->lieu->nom = temp->right->lieu->nom;
            j->lieu->est_monstre = temp->right->lieu->est_monstre;
            j->lieu->monstre->type = temp->right->lieu->monstre->type;
            j->lieu->monstre->vie = temp->right->lieu->monstre->vie;

            commande_regarder(j);

            printf("\nVous allez dans : %s\n", nombre_en_lieu(temp->right->lieu->nom));


        }
        else
        {
            printf("Vous ne pouvez pas aller la-bas\n");
        }
    }

    return j;
}

void commande_regarder(Joueur j)
{

    char chaine[MAX_SIZE] = "";
    FILE* file = NULL;

    switch(j->lieu->nom)
    {
    case 2:

        file = fopen("foret.txt", "r");

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
        break;

    case 1:

        file = fopen("grotte.txt", "r");

        if (file != NULL)
        {
            //Read
            while(fgets(chaine, MAX_SIZE, file) != NULL)
            {
                printf("%s", chaine); //print
            }
            //End
            fclose(file);
        }
        else
        {
            printf("Failed while opening the file grotte.txt\n");
            fclose(file);
        }
        break;
    case 3:

        file = fopen("donjon.txt", "r");

        if (file != NULL)
        {
            //Read the 1.txt
            while(fgets(chaine, MAX_SIZE, file) != NULL)
            {
                printf("%s", chaine); //print the scoreboard register in the .txt
            }
            //End of reading and writing
            fclose(file);
        }
        else
        {
            printf("Failed while opening the file donjon.txt\n");
            fclose(file);
        }
        break;

    case 4:

        file = fopen("desert.txt", "r");

        if (file != NULL)
        {
            //Read the 1.txt
            while(fgets(chaine, MAX_SIZE, file) != NULL)
            {
                printf("%s", chaine); //print the scoreboard register in the .txt
            }
            //End of reading and writing
            fclose(file);
        }
        else
        {
            printf("Failed while opening the file donjon.txt\n");
            fclose(file);
        }

        break;
    }
}


int saisie_joueur()
{
    int est_quitte = 0;

    printf("\n->");
    fflush(stdin);
    fgets(saisie, sizeof(saisie), stdin);

    while(strcmp(saisie, "\n") == 0)
    {
        printf("Veuillez entrer au moins un argument (ex : aller, regarder...)");
        printf("\n\n->");
        fflush(stdin);
        fgets(saisie, sizeof(saisie), stdin);
    }

    if(strcmp(saisie, "quitter\n") == 0)
    {
        est_quitte++;
    }

    return est_quitte;
}


void detruire_joueur(Joueur j)
{
    printf("Suppression du pseudo: %s", j->pseudo);
    free(j->pseudo);
    printf("Suppression du joueur\n");
    free(j);
}


char* nombre_en_lieu(int nombre)
{
    switch(nombre)
    {
    case 2:
        return "foret";
        break;
    case 1:
        return "grotte";
        break;
    case 3:
        return "donjon";
        break;
    case 4:
        return "desert";
        break;
    default:
        return NULL;
    }
}


int lieu_en_nombre(char* lieu)
{
    if(lieu == NULL)
    {
        return 0;
    }

    if(strcmp(lieu, "foret") == 0)
    {
        return 2;
    }
    else if(strcmp(lieu, "grotte") == 0)
    {
        return 1;
    }
    else if(strcmp(lieu, "donjon") == 0)
    {
        return 3;
    }
    else if (strcmp(lieu, "desert")== 0)
    {
        return 4;
    }
    else
    {
        return 0;
    }
}

char* nombre_en_direction(int nombre)
{
    switch(nombre)
    {
    case 2:
        return "nord";
        break;
    case 1:
        return "s-o";
        break;
    case 3:
        return "s-e";
        break;
    default:
        return NULL;
    }
}


int direction_en_nombre(char* lieu)
{
    if(lieu == NULL)
    {
        return 0;
    }

    if(strcmp(lieu, "nord") == 0)
    {
        return 2;
    }
    else if(strcmp(lieu, "s-o") == 0)
    {
        return 1;
    }
    else if(strcmp(lieu, "s-e") == 0)
    {
        return 3;
    }
    else if(strcmp(lieu, "ici") == 0)
    {
        return 4;
    }
    else
    {
        return 0;
    }
}



Joueur couper_bois(Joueur j)
{
    if(est_inv(j->inv, "buche")){
        printf("Vous avez deja du bois\n");
        j->inv = ajout_inv(j->inv, 1, "pomme");
        printf("Tu viens de recuperer une pomme\n");
    }else{
        if(j->lieu->nom == 2)
        {
            j->inv = ajout_inv(j->inv, 1, "buche");
            j->inv = ajout_inv(j->inv, 1, "pomme");
            printf("SCHHARKK\n");
            printf("Tu viens de couper 4 buches\n");
            printf("Tu viens de recuperer une pomme\n");
            j->craft_faisable = ajouter_fait("buche",j->craft_faisable);
        }
        else
        {
            printf("Il n'y a pas d'arbre a couper ! Va dans une foret tu auras plus de chances d'en trouver :)\n");
        }
    }
    return j;
}



Joueur supprimer_craft( Joueur j ,char* nom_item){

    liste_regle temporaire;

    temporaire = j->liste_craft;

    while(strcmp(temporaire->regle->conclusion.nom,nom_item)!= 0){

        temporaire = temporaire->next;
    }

    Liste temporaire_bis;
    temporaire_bis = temporaire->regle->premisse;

    while(temporaire_bis != NULL){

        j = Suppression_item(j,temporaire_bis->valeur.nom);
        j->inv = supp_item_inv(j->inv,temporaire_bis->valeur.nom,1);
        temporaire_bis = temporaire_bis->next;

    }

    return j;

}

Joueur Suppression_item(Joueur j, char* nom_item)
{


    //SI L'ELEMENT APPARTIENT A LA LISTE ALORS ON PEUT LE SUPPRIMER


    liste_fait temp;
    temp = j->craft_faisable;

    //CAS OU LE MOT A SUPPRIMER EST LE PREMIER DE LA LISTE
    if(strcmp(j->craft_faisable->fait.nom, nom_item) == 0)
    {

        temp = j->craft_faisable->next;
        free(j->craft_faisable);

        j->craft_faisable = temp;

    }
    else
    {
        //CAS OU LE MOT A SUPPRIMER N'EST PAS LE PREMIER

        while(temp->next != NULL && strcmp(temp->next->fait.nom, nom_item) != 0 )   /*On parcours la liste jusqu'a ce que la prochaine proposition soit celle qui faut supp*/
        {
            temp = temp->next;
        }

        liste_fait temp2;
        temp2 = temp->next->next;
        free(temp->next);
        temp->next = temp2;
    }

    //SI L'ELEMENT N'APPARTIENT PAS A LA LISTE


    return j;
}



Joueur craft(Joueur j,char* nom_item, liste_fait deduction)
{
    if(nom_item==NULL)
    {
        afficher_fait(deduction);
    }
    else
    {

        if(fait_deja_existant(nom_item,deduction)==true)
        {

            printf("Vous avez cree : %s \n",nom_item);
            j->craft_faisable = ajouter_fait(nom_item,j->craft_faisable);
            j->inv = ajout_inv(j->inv,1,nom_item);
            j->score += 1;
            printf("Votre score augmente de 1\n");

            j = supprimer_craft(j,nom_item);
        }

        else
        {
            printf(" Vous ne pouvez pas creer %s \n", nom_item);
        }
    }

    return j;
}

Joueur miner_fer(Joueur j)
{
    if(est_inv(j->inv, "fer")){
        printf("Vous avez deja du fer\n");
    }else{
        if(j->lieu->nom == 1)
        {
            j->inv = ajout_inv(j->inv, 1, "fer");
            printf("PUNSHKKK\n");
            printf("Tu viens de miner 1 fer\n");

            j->craft_faisable = ajouter_fait("fer",j->craft_faisable);
        }
        else
        {
            printf("Il n'y a pas de minerais a miner ! Va dans une grotte tu auras plus de chances d'en trouver :)\n");
        }
    }
    return j;
}

BTree attaquer_monstre(Joueur j, BTree t)
{
    BTree temp = t;
    temp = parcourir_arbre(j, temp);

    if(temp->lieu->est_monstre == false){
        printf("Il n'y a pas de monstre a attaquer\n");
    }else{
        if(est_inv(j->inv, "epee") == true)
        {
            temp->lieu->monstre->vie -= 5;

            if(temp->lieu->monstre->vie > 0)
            {
                printf("Vous venez d'infliger 5 de degats au monstre\n");
                printf("Vie du boss : %d\n", temp->lieu->monstre->vie);

            }else{
                temp->lieu->est_monstre = false;

                printf("Felicitation vous avez tue le monstre !\n");
            }

        }else{
            temp->lieu->monstre->vie -= 1;

            if(temp->lieu->monstre->vie > 0)
            {
                printf("Vous venez d'infliger 1 de degats au monstre\n");
                printf("Vie du boss : %d\n", temp->lieu->monstre->vie);
            }else{
                temp->lieu->est_monstre = false;
                printf("Felicitation vous avez tue le monstre !\n");
            }
        }
    }

    return t;
}


Joueur attaquer_joueur(Joueur j, BTree t)
{
    BTree temp = parcourir_arbre(j, t);
    if(j->vie > 0 && temp->lieu->monstre->vie != 0){
        j->vie -= 4;
        printf("Attention le monstre vous attaque, vous avez perdu 4 points de vie\n");
    }

    return j;
}

Joueur commande_manger(Joueur j)
{
    if(est_inv(j->inv, "pomme"))
    {
        if(j->vie < 18){
            j->inv = supp_item_inv(j->inv, "pomme", 1);
            j->vie += 3;
            printf("Vous avez gagne 3 points de vie\n");
        }else{
            j->inv = supp_item_inv(j->inv, "pomme", 1);
            j->vie += (20-(j->vie));
            printf("Votre sante est maximale\n");
        }
    }
    else
    {
        printf("Vous n'avez pas de pomme a manger\n");
    }
    return j;
}
