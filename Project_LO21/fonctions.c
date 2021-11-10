/*!
* \file fonctions.c
* \brief Fichier source des fonctions relative a l'arbre et donc la map du jeu
* \version 1.0
* \date 25/12/2020
* \author Maxime SZYMANSKI Jules PETRY
* -# Creation de l'arbre :
* En premier lieu, un arbre est cree avec une racine et deux feuilles au tout debut du jeu.
* -# Gestion de l'arbre :
* \nDes feuilles peuvent etre ajoute en fonction de l'evolution du joueur // l'arbre est detruit a la fin du jeu.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "all.h"

BTree creer_arbre(int nom)
{

	BTree newel;
	lieu* newlieu;
	monstre* newmonstre;

	newel = malloc(sizeof(tree_elem));
	newlieu = malloc(sizeof(lieu));
	newmonstre = malloc(sizeof(monstre));

	newlieu->nom = nom;
	newlieu->unique_id = 0;

	if(nom == 3){
		newlieu->est_monstre = true;
		newmonstre->type = 1;
		newmonstre->vie = 10;
		newlieu->monstre = newmonstre;

	}else{
		newlieu->est_monstre = false;
		newmonstre->type = 0;
		newmonstre->vie = 0;
		newlieu->monstre = newmonstre;
	}

	newel->lieu = newlieu;

	newel->left = NULL;
	newel->right = NULL;
	newel->parent = NULL;

	return newel;
}



void detruire_arbre(BTree t)
{

	if(t == NULL){
		return;
	}

	detruire_arbre(t->left);
	detruire_arbre(t->right);

	free(t);
}


BTree enraciner(BTree l, BTree r, BTree t)
{
	t->left = l;
	t->right = r;

	if(l != NULL){
		l->parent = t;
		l->lieu->unique_id = t->lieu->unique_id - 128;
	}

	if(r != NULL){
		r->parent = t;
		r->lieu->unique_id = t->lieu->unique_id + 128;
	}

	return t;
}


void afficher_arbre_prefix(BTree t)
{
	if(t == NULL){
		return;
	}

	if(t->parent != NULL){
		printf("(%d) -> %d\n", t->parent->lieu->unique_id, t->lieu->unique_id);
	}else{
		printf("(%d)\n", t->lieu->unique_id);
	}

	if(t->left != NULL){
		afficher_arbre_prefix(t->left);
	}

	if(t->right != NULL){
		afficher_arbre_prefix(t->right);
	}
}

int nombre_noeuds(BTree t)
{
	if (t == NULL){
		return 0;
	}

	return (nombre_noeuds(t->left) + nombre_noeuds(t->right) + 1);
}


BTree extansion(Joueur j, BTree t)
{
	BTree temp = t;
	temp = parcourir_arbre(j, temp);

	if((j->lieu->unique_id)%128 == -1){
		printf("Vous ne pouvez pas aller plus loin, la limite de map est atteinte\n");
		return t;
	}

	if(temp->left == NULL && temp->right == NULL){


		int rand1 = (rand()%4) + 1;
		int rand2 = (rand()%4) + 1;

		temp->left = creer_arbre(rand1);
		temp->right = creer_arbre(rand2);

		temp->left->parent = temp;
		temp->right->parent = temp;

		int pos_diff;
		pos_diff = sqrt(pow((temp->parent->lieu->unique_id)-(temp->lieu->unique_id),2));

		if(temp->lieu->unique_id < 0){
			if((temp->lieu->unique_id)%128 == 0){
				temp->left->lieu->unique_id = (temp->lieu->unique_id)*2;
				temp->right->lieu->unique_id = (temp->lieu->unique_id) + (pos_diff/2);

			}else{

				temp->left->lieu->unique_id = (temp->lieu->unique_id) - (pos_diff/2);
				temp->right->lieu->unique_id = (temp->lieu->unique_id) + (pos_diff/2);
			}

		}else{

			if((temp->lieu->unique_id)%128 == 0){
				temp->right->lieu->unique_id = (temp->lieu->unique_id)*2;
				temp->left->lieu->unique_id = (temp->lieu->unique_id) - (pos_diff/2);

			}else{

				temp->right->lieu->unique_id = (temp->lieu->unique_id) + (pos_diff/2);
				temp->left->lieu->unique_id = (temp->lieu->unique_id) - (pos_diff/2);
			}
		}
		
	}
	return t;
}

BTree parcourir_arbre(Joueur j, BTree t)
{
	BTree temp = t;

	if(temp == NULL){
		return NULL;
	}
	if(j->lieu->unique_id == temp->lieu->unique_id){
		return t;
	}
	if(j->lieu->unique_id < temp->lieu->unique_id){
		parcourir_arbre(j, temp->left);
	}else{
		parcourir_arbre(j, temp->right);
	}
}
