#ifndef ALL_H_INCLUDED
#define ALL_H_INCLUDED
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "craft.h"

/*!
* \file all.h
* \brief Contient les en-têtes des fonctions relatives a la gestion de l'inventaire, des interfaces, de l'arbre et du joueur.
* \version 1.0
* \date 25/12/2020
* \author Maxime SZYMANSKI Jules PETRY
*/

/**
 * \struct monstre
 * \brief Contient les informations d'un monstre
 * Cette structure contient les informations d'un monstre (vie , type).
 *\n Cette structure nous facilite la gestion des monstres.
 */

typedef struct monstre{
    int vie;
    int type;
}monstre;

/**
 * \struct lieu
 * \brief Contient les informations d'un lieu
 * Cette structure contient les informations d'un lieu (nom , unique_id, est_monstre, monstre).
 *\n Cette structure nous facilite la gestion des lieux.
 */

typedef struct lieu{
	int nom;
	int unique_id;
    bool est_monstre;
    struct monstre* monstre;
}lieu;

/**
 * \struct tree_elem
 * \brief Contient les informations d'un noeud de l'arbre.
 * Cette structure contient les informations d'un monstre (lieu, *right, *left, *parent).
 *\n Cette structure nous facilite la gestion de l'arbre.
 */

typedef struct tree_elem{
	lieu* lieu;
	struct tree_elem *right;
	struct tree_elem *left;
	struct tree_elem *parent;
}tree_elem;

typedef tree_elem* BTree;

/**
 * \struct Liste_inv
 * \brief Contient les informations d'un element de l'inventaire.
 * Cette structure contient les informations d'un element de l'inventaire (quantite, nom, next).
 *\n Cette structure nous facilite la gestion de l'inventaire.
 */

typedef struct elem{
    int quantite;
    char* nom;
    struct elem* next;
}elem;
typedef elem* Liste_inv;

/**
 * \struct Joueur
 * \brief Contient les informations d'un Joueur
 * Cette structure contient les informations d'un Joueur (vie , pseudo, lieu, inventaire, score, craft_faisable, liste_craft).
 *\n Cette structure nous facilite la gestion des Joueurs.
 */

typedef struct desc{
    char* pseudo;
    lieu* lieu;
    Liste_inv inv;
    int vie;
    int score;
    liste_fait craft_faisable;
    liste_regle liste_craft;
}desc;
typedef desc* Joueur;


/*FONCTION DE L'EVOLUTION DU JOUEUR SUR LA MAP*/

/**
 * \fn Joueur creer_joueur(void);
 * \brief Fonction qui creer et initialise la structure Joueur (inventaire, position, bdc, vie etc).
 * \param void
 * \return j retourne les informations du joueur.
*/

Joueur creer_joueur(void);

/**
 * \fn Joueur gestion_commande_arg1(Joueur j, BTree t,liste_fait deduction);
 * \brief Fonction qui appelle la fonction correspondante a la commande execute.
 * \param j Structure du Joueur.
 * \param t Arbre qui correspond a la map.
 * \param deduction Craft possible a faire.
 * \return j retourne les informations du joueur mise a jour en fonction de la commande execute.
*/

Joueur gestion_commande_arg1(Joueur j, BTree t,liste_fait deduction);

/**
 * \fn int saisie_joueur(void);
 * \brief Fonction qui recupere la commande execute par le joueur.
 * \param void
 * \return est_quitte Donne l'information si le joueur a entrer la commande "quitter".
*/

int saisie_joueur(void);

/**
 * \fn void detruire_joueur(Joueur j);
 * \brief Fonction qui libere la memoire utilise pour la structure joueur.
 * \param j Structure du Joueur.
 * \return void
*/

void detruire_joueur(Joueur j);

/**
 * \fn Joueur commande_aller(char* arg2, Joueur j, BTree t);
 * \brief Fonction qui deplace le joueur vers le lieu voulu.
 * \param arg2 Deuxieme argument de la commande executer par le joueur.
 * \param j Structure du Joueur.
 * \param t Arbre qui correspond a la map
 * \return j Structure du Joueur avec le lieu du joueur mis a jour.
*/

Joueur commande_aller(char* arg2, Joueur j, BTree t);

/**
 * \fn void commande_regarder(Joueur j);
 * \brief Fonction qui lit le fichier correspondant au lieu ou le joueur se situe.
 * \param j Structure du Joueur.
 * \return void.
*/

void commande_regarder(Joueur j);

/**
 * \fn BTree parcourir_arbre(Joueur j, BTree t);
 * \brief Fonction qui permet de parcourir l'arbre (la map) jusqu'au lieu ou se situe le joueur.
 * \param j Structure du Joueur.
 * \param t Arbre qui correspond a la map.
 * \return t Element de l'arbre ou le joueur se situe
*/

BTree parcourir_arbre(Joueur j, BTree t);

/**
 * \fn char* nombre_en_lieu(int nombre);
 * \brief Fonction qui retourne le lieu en char* a partir de son integer correspondant.
 * \param nombre Integer correspondant a un lieu.
 * \return char* Nom du lieu pris en parametre en toute lettre.
*/

char* nombre_en_lieu(int nombre);

/**
 * \fn int lieu_en_nombre(char* lieu);
 * \brief Fonction qui retourne le lieu en integer a partir de son char* correspondant.
 * \param lieu Nom d'un lieu en toute lettre.
 * \return int Nom du lieu pris en parametre en integer.
*/

int lieu_en_nombre(char* lieu);

/**
 * \fn char* nombre_en_direction(int nombre);
 * \brief Fonction qui retourne une direction en char* a partir de son integer correspondant.
 * \param nombre Integer correspondant a une direction.
 * \return char* Nom de la direction prise en parametre en toute lettre.
*/

char* nombre_en_direction(int nombre);

/**
 * \fn int direction_en_nombre(char* lieu);
 * \brief Fonction qui retourne une direction en integer a partir de son char* correspondant.
 * \param lieu nom d'une direction en toute lettre.
 * \return int Nom de la direction prise en parametre en integer.
*/

int direction_en_nombre(char* lieu);

/**
 * \fn Joueur couper_bois(Joueur j);
 * \brief Fonction qui ajoute des buches dans l'inventaire du joueur quand il fait la commande "couper".
 * \param j Structure du Joueur.
 * \return j Structure du Joueur mise a jour avec potentiellement du bois et une pomme.
*/

Joueur couper_bois(Joueur j);

/**
 * \fn Joueur miner_fer(Joueur j);
 * \brief Fonction qui ajoute du fer dans l'inventaire du joueur quand il fait la commande "miner".
 * \param j Structure du Joueur.
 * \return j Structure du Joueur mise a jour avec potentiellement du fer.
*/

Joueur miner_fer(Joueur j);

/**
 * \fn Joueur attaquer_joueur(Joueur j, BTree t);
 * \brief Fonction qui enleve des points de vie au joueur.
 * \param j Structure du Joueur.
 * \return j Structure du Joueur mise a jour avec des pts de vie en moins.
*/

Joueur attaquer_joueur(Joueur j, BTree t);

/**
 * \fn Joueur commande_manger(Joueur j);
 * \brief Fonction qui ajoute des points de vie au joueur quand il mange une pomme.
 * \param j Structure du Joueur.
 * \return j Structure du Joueur mise a jour avec potentiellement des pts de vie en plus.
*/

Joueur commande_manger(Joueur j);

/*-------------------------------------*/


/*FONCTION QUI AGISSENT SUR L'INVENTAIRE*/

/**
 * \fn Liste_inv creer_inv(void);
 * \brief Creer un inventaire vide.
 * \param void.
 * \return inv Inventaire du joueur vide.
*/

Liste_inv creer_inv(void);

/**
 * \fn Liste_inv ajout_inv(Liste_inv inv, int quantite, char*nom);
 * \brief Ajoute une quantite d'un item a l'inventaire du joueur.
 * \param inv Inventaire du Joueur.
 * \param quantite Quantite d'item a ajoute.
 * \param nom Nom de l'item a ajoute.
 * \return inv Inventaire du joueur mise a jour avec l'item ajoute.
*/

Liste_inv ajout_inv(Liste_inv inv, int quantite, char* nom);

/**
 * \fn Liste_inv supp_item_inv(Liste_inv inv, char* nom, int quantite);
 * \brief Supprime une quantite d'un item a l'inventaire du joueur.
 * \param inv Inventaire du Joueur.
 * \param nom Nom de l'item a ajoute.
 * \param quantite Quantite d'item a ajoute.
 * \return inv Inventaire du joueur mise a jour avec l'item ajoute.
*/

Liste_inv supp_item_inv(Liste_inv inv, char* nom, int quantite);

/**
 * \fn void afficher_inv(Joueur j);
 * \brief Affiche l'inventaire du joueur.
 * \param j Structure du Joueur.
 * \return void.
*/

void afficher_inv(Joueur j);

/**
 * \fn bool est_inv(Liste_inv inv, char* nom);
 * \brief Retourne "true" si le joueur possede l'item en parametre dans son inv, sinon "false".
 * \param inv Inventaire du Joueur.
 * \param nom Nom de l'item qu'on recherche dans l'inventaire.
 * \return bool True ou False selon les conditions.
*/

bool est_inv(Liste_inv inv, char* nom);

/**
 * \fn int quantite_item(Liste_inv, char* nom);
 * \brief Retourne la quantite d'un item pris en parametre que le joueur possede dans son inv.
 * \param inv Inventaire du Joueur.
 * \param nom Nom de l'item qu'on recherche dans l'inventaire.
 * \return temp->quantite Quantite de l'item recherche.
*/

int quantite_item(Liste_inv inv, char* nom);

/**
 * \fn void detruire_inv(Liste_inv inv);
 * \brief Detruit et libere la memoire allouee pour l'inventaire.
 * \param inv Inventaire du Joueur.
 * \return void.
*/

void detruire_inv(Liste_inv inv);

/*-----------------------------------------*/

/*FONCTIONS ARBRE*/


/**
 * \fn BTree creer_arbre(int nom);
 * \brief Fonction qui creer et initialise un element d'arbre.
 * \param nom Nom du lieu que sera l'element de l'arbre.
 * \return t Element d'arbre qui vient d'etre creer.
*/

BTree creer_arbre(int nom);

/**
 * \fn void detruire_arbre(BTree t);
 * \brief Fonction qui libere la memoire allouer a la constitution d'un arbre.
 * \param t L'arbre a detruire.
 * \return void.
*/

void detruire_arbre(BTree t);

/**
 * \fn BTree enraciner(BTree l, BTree r, BTree t);
 * \brief Fonction qui enracine deux feuilles a un noeud.
 * \param l L'element d'arbre a enraciner en temps que fils gauche.
 * \param r L'element d'arbre a enraciner en temps que fils droit.
 * \param t L'element d'arbre sur lequel les feuilles vont s'enraciner.
 * \return t L'arbre avec la racine et les deux fils.
*/

BTree enraciner(BTree l, BTree r, BTree t);

/**
 * \fn void afficher_arbre_prefix(BTree t);
 * \brief Fonction qui affiche l'arbre de gauche a droite.
 * \param t L'arbre a afficher.
 * \return void.
*/

void afficher_arbre_prefix(BTree t);

/**
 * \fn int nombre_noeuds(BTree t);
 * \brief Fonction qui affiche le nombre de noeud de l'arbre (feuilles et racine comprises) (fonction recursive).
 * \param t L'arbre dont on veut compter le nombre de noeuds.
 * \return int Integer qui correspond a la somme des noeuds des fils gauche et des fils droits d'une racine.
*/

int nombre_noeuds(BTree t);

/**
 * \fn BTree extansion(Joueur j, BTree t);
 * \brief Fonction qui creer et ajoute une feuille droite et gauche a l'element ou le joueur est aller.
 * \param j Structure du Joueur.
 * \param t L'arbre qu'on veut etendre.
 * \return t L'arbre potentiellement etendu.
*/

BTree extansion(Joueur j, BTree t);

/**
 * \fn BTree attaquer_monstre(Joueur j, BTree t);
 * \brief Fonction qui enleve de la vie au monstre dans un donjon avec la commande "attaquer".
 * \param j Structure du Joueur.
 * \param t L'arbre correspondant a la map.
 * \return t L'arbre dont la structure du monstre du donjon ou le joueur se trouve, est actualisee.
*/

BTree attaquer_monstre(Joueur j, BTree t);


/*-------------------------------------------*/

/*FONCTIONS CRAFT*/

/**
 * \fn Joueur craft(Joueur j,char* nom_item, liste_fait deduction);
 * \brief Fonction qui craft l'objet entré en parametre et l'ajoute dans la base de fait et dans l'inventaire du joueur.
 * \param j Structure du joueur.
 * \param nom_item Nom de l'objet a crafter.
 * \param deduction Craft possible a faire.
 * \return Joueur  Retourne les informations du joueur apres le craft.
*/

Joueur craft(Joueur j,char* nom_item, liste_fait deduction);    /*FONCTION QUI CREER ET AJOUTE UN ITEM A L'INVENTAIRE SUITE A LA COMMANDE "CRAFT <objet>"*/

/**
 * \fn Joueur Suppression_item(Joueur j, char* nom_item);
 * \brief Fonction qui supprime un objet de la base de fait.
 * \param j Structure du joueur.
 * \param nom_item Nom de l'objet a supprimer.
 * \return Joueur  Retourne les informations du joueur apres la suppression .
 */

Joueur Suppression_item(Joueur j, char* nom_item);

/**
 * \fn Joueur supprimer_craft( Joueur j ,char* nom_item);
 * \brief Fonction qui supprime les objets utilisé pour le craft de l'objet en parametre.
 * \param j Structure du joueur.
 * \param nom_item Nom de l'objet dont on veut supprimer les ressources utilisé pour le créer.
 * \return Joueur  Retourne les informations du joueur apres la suppression .
 */

Joueur supprimer_craft( Joueur j ,char* nom_item);

/*-------------------------------------------*/

/*FONCTION DES MENUS*/

/**
 * \fn int menu_accueil(void);
 * \brief Fonction qui affiche le premier menu d'accueil.
 * \param void.
 * \return choice Retourne le choix du joueur.
 */

int menu_accueil(void);

/**
 * \fn void menu_perdu(Joueur j, BTree t);
 * \brief Fonction qui affiche le premier menu d'accueil.
 * \param j Structure du Joueur.
 * \param t Arbre correspondant a la map.
 * \return void.
 */

void menu_perdu(Joueur j, BTree t);


#endif // ALL_H_INCLUDED
