#ifndef CRAFT_H_INCLUDED
#define CRAFT_H_INCLUDED

/*!
* \file craft.h
* \brief Contient les en-têtes des fonctions relatives a la gestion des craft
* \version 1.0
* \date 25/12/2020
* \author Maxime SZYMANSKI Jules PETRY
*/

/**
 * \struct Proposition
 * \brief Contient les informations d'une proposition
 * Cette structure contient les informations d'une proposition (data , nom).
 *\n Cette structure nous facilite la gestion des propositions.
 */

typedef struct Proposition{

	bool data;	/*!< Valeur de la proposition ( VRAI ou FAUX ) */
	char *nom;	/*!< Nom de la proposition ( chaine de charactere ) */

}Proposition;

/**
 * \struct eleme
 * \brief Element de la liste chainée de proposition, qui est en fait la prémisse d'une regle.
 * Cette structure contient les informations d'une liste chainée de proposition (valeur de l'element , pointeur sur l'element suivant ).
 *\n Cette structure nous permet d'utiliser une liste chainée afin de traiter la prémisse de la regle.
 */

typedef struct eleme{

	Proposition valeur;	/*!< Valeur  de l'element de la prémisse ( Proposition ) */
	struct eleme *next;	/*!< Pointeur sur l'element suivant de la prémisse ( Pointeur sur une proposition ) */

}eleme;

typedef eleme* Liste;

/**
 * \struct Regle
 * \brief Regle d'une base de connaissance.
 * Cette structure contient les informations d'une Regle : son nom, sa conclusion et sa prémisse.
 *\n Cette structure nous permet de faciliter l'utilisation des regles en aillant acces facilement a sa conclusion.
 */

typedef struct Regle{

	char* nom_regle;	/*!< Nom de la regle ( Chaine de caractere ) */

	Proposition conclusion;	/*!< Conclusion de la regle ( Proposition ) */


Liste premisse;	/*!< Premisse de la regle ( Liste chainée de Proposition ) */

}Regle;

/**
 * \struct BC
 * \brief Base de connaissance
 * Cette structure contient les informations d'une base de connaissance sous forme de liste chainée : la valeur de l'element (ici une regle) et un pointeur sur l'element suivant.
 *\n Cette structure nous permet de faciliter l'utilisation des bases de connaissance sous forme de liste chainée.
 */

typedef struct BC{

	struct BC *next;	/*!< Pointeur sur l'element suivant de la liste de regle  ( Pointeur sur BC ) */
	Regle *regle;	/*!< Valeur de la regle  ( la valeur est de type *Regle pour faciliter sa gestion ) */

}BC;

typedef BC* liste_regle;

/**
 * \struct Base_fait
 * \brief Base de fait
 * Cette structure contient les informations d'une base de fait  sous forme de liste chainée de proposition.
 *\n Cette structure nous permet de faciliter l'utilisation des bases de fait sous forme de liste chainée.
 */

typedef struct Base_fait{

	struct Base_fait *next;	/*!< Pointeur sur l'element suivant de la base de fait ( Pointeur sur Base de fait ) */
	Proposition fait;	/*!< Valeur de la proposition de la base de fait  ( valeur de type proposition ) */


}Base_fait;

typedef Base_fait* liste_fait;

/**
 * \fn bool fait_deja_existant(char* nom, liste_fait base_fait);
 * \brief Fonction qui indique si un fait est deja présent dans une base de fait.
 * \param nom Chaine de caractere qui représente le nom du fait.
 * \param base_fait Base de fait ou l'on cherche le fait.
 * \return bool Retourne VRAI si le fait est deja dans la base de fait, FAUX sinon.
 */

bool fait_deja_existant(char* nom, liste_fait base_fait);

/**
 * \fn bool proposition_deja_existante(char* nom, Regle* R);
 * \brief Fonction qui indique si une proposition est deja présente dans la prémisse d'une regle.
 * \param nom Chaine de caractere qui représente le nom de la proposition.
 * \param R Regle ou l'on va chercher la presence de la proposition.
 * \return bool Retourne VRAI si une proposition a ce nom dans la prémisse, faux sinon.
 */

bool proposition_deja_existante(char* nom, Regle* R);

/**
 * \fn Regle* cherche_regle(char* nom, liste_regle BC);
 * \brief Fonction qui retourne la regle dont le nom est entrée, depuis la base de connaissance.
 * \param nom Chaine de caractere qui représente le nom de la regle a renvoyer.
 * \param BC Base de connaissance dans laquel l'on va chercher la regle.
 * \return Regle Retourne un pointeur sur la regle recherchée.
 */

Regle* cherche_regle(char* nom, liste_regle BC);

/**
 * \fn bool regle_deja_existante(char* nom, liste_regle BC);
 * \brief Fonction qui indique si une regle est dans une base de connaissance a partir du nom de cette regle.
 * \param nom Chaine de caractere qui représente le nom de la regle a rechercher.
 * \param BC Base de connaissance dans laquel on va rechercher la regle.
 * \return bool Retourne VRAI si la regle est deja dans la base de connaissance, FAUX sinon.
 */

bool regle_deja_existante(char* nom, liste_regle BC);

/**
 * \fn liste_regle creer_base_vide(void);
 * \brief Fonction qui crée une liste de regle vide.
 * \return liste_regle Retourne la liste de regle vide.
 */

liste_regle creer_base_vide(void);

/**
 * \fn void afficher_bc(liste_regle lr);
 * \brief Fonction qui affiche la liste des regles de la base de connaissance donnée.
 * \param liste_regle Liste de regles a afficher.
 */

void afficher_bc(liste_regle lr);

/**
 * \fn bool appartient_premisse(Liste premisse, Proposition prop);
 * \brief Fonction qui indique si proposition appartient a la premisse d'une regle.
 * \param premisse Liste de proposition qui représente la premisse de la regle.
 * \param prop Proposition a rechercher.
 * \return bool Retourne VRAI si la proposution est deja dans la prémisse, FAUX sinon.
 */

bool appartient_premisse(Liste premisse, Proposition prop);

/**
 * \fn Regle* creer_regle(char* nom_R);
 * \brief Fonction qui crée une regle vide.
 * \param nom_R Nom de la regle a creer.
 * \return Regle*  Retourne un pointeur sur la regle créee.
 */

Regle* creer_regle(char* nom_R);

/**
 * \fn Regle* Ajout_proposition_premisse(Regle* r, Proposition prop);
 * \brief Fonction qui ajoute une proposition a la prémisse d'une regle.
 * \param r Regle ou l'on veut ajouter une proposition a la prémisse.
 * \param prop Proposition a ajouter en premisse.
 * \return Regle*  Retourne un pointeur sur la regle.
 */

Regle* Ajout_proposition_premisse(Regle* r, Proposition prop);

/**
 * \fn Regle* creer_conclusion(char* nom_ccl, Regle* r);
 * \brief Fonction qui crée la conclusion d'une regle.
 * \param r Regle ou l'on veut ajouter la conclusion.
 * \param nom_ccl Nom de la conclision.
 * \return Regle*  Retourne un pointeur sur la regle.
 */

Regle* creer_conclusion(char* nom_ccl, Regle* r);

/**
 * \fn liste_fait ajouter_ccl_fait(Regle* R, liste_fait BF, bool *test);
 * \brief Fonction qui ajoute la conclusion d'une regle a une base de fait si la conclusion est vraie.
 * \param R Regle dont on veut la conclusion.
 * \param BF Base de fait ou l'on veut ajouter la conclusion de la regle.
 * \param test Booléen qui vaut vrai si la conclusion est vrai et faux sinon. Il sert a determiner si l'on a deduit un fait ou pas.
 * \return liste_fait  Retourne la base de fait avec la conclusion rajouté si elle est vrai.
 */

liste_fait ajouter_ccl_fait(Regle* R, liste_fait BF, bool *test);

/**
 * \fn liste_regle ajout_Regle(liste_regle *bc, Regle* r);
 * \brief Ajoute une regle a une base de connaissance.
 * \param bc Pointeur sur la base de connaissance a remplir.
 * \param r Pointeur sur la regle a rajouter.
 * \return liste_regle  Retourne la base de connaissance avec la nouvelle regle ajouté en queue.
 */

liste_regle ajout_Regle(liste_regle *bc, Regle* r);

/**
 * \fn liste_fait ajouter_ccl_deduction(Regle* R, liste_fait *deduction);
 * \brief Ajoute la conclusion d'une regle dans la liste de fait "deduction". Déduction est la liste composé seulement des deductions du moteur d'inference.
 * \param R Pointeur sur la regle dont on veut la conclusion.
 * \param deduction Pointeur sur la deduction a remplir.
 * \return liste_fait  Retourne liste de fait deduis.
 */

liste_fait ajouter_ccl_deduction(Regle* R, liste_fait *deduction);

/**
 * \fn bool premisse_est_vide( Liste premisse );
 * \brief Test si la prémisse d'une regle est vide.
 * \param premisse Premisse de la regle. C'est une liste chainée de proposition.
 * \return bool  Retourne VRAI si la prémisse est vide et FAUX sinon.
 */

bool premisse_est_vide( Liste premisse );

/**
 * \fn Proposition tete_premisse( Liste premisse );
 * \brief Fonction qui retourne la tete de la prémisse.
 * \param premisse Premisse dont on veut la récuperer la valeur de la tete.
 * \return Proposition  Retourne la proposition en tete de prémisse, donc de liste.
 */

Proposition tete_premisse( Liste premisse );

/**
 * \fn liste_fait moteur_inference(liste_regle BC, liste_fait base_fait, liste_fait *deduction,   bool* repetition);
 * \brief Fonction qui déduit des fait et les stocks dans la base de fait et dans la déduction, a partir d'une base de fait et d'une liste de regle.
 * \param BC Base de connaissance qui contient une liste chainée de regle.
 * \param base_fait Base de fait que l'on va etudier et on l'on va ajouter les déductions.
 * \param deduction Pointeur sur la déduction. On va ajouter dans cette liste seulement les faits déduit par le moteur d'inference.
 * \param repetition Booléen qui vaut VRAI si l'on a déduit au moins un fait et FAUX sinon. Il sert a relancer le moteur d'inference si au moins un fait a été déduit.
 * \return liste_fait  Retourne la liste de fait constaté avec les déductions ajoutées.
 */

liste_fait moteur_inference(liste_regle BC, liste_fait base_fait, liste_fait *deduction,   bool* repetition);

/**
 * \fn Proposition conclusion_regle( Regle *R );
 * \brief Fonction qui renvoie la conclusion d'une regle.
 * \param R Pointeur sur la regle dont on veut la conclusion.
 * \return Proposition  Retourne la conclusion de la regle.
 */

Proposition conclusion_regle( Regle *R );

/**
 * \fn liste_fait ajouter_fait(char* nom_fait, liste_fait base_fait)
 * \brief Fonction qui ajoute un fait a la base de fait.
 * \param nom_fait Nom du fait a ajouter dans la base de fait.
 * \param base_fait Base de fait ou l'on veut ajouter le fait.
 * \return liste_fait  Retourne la liste de fait avec la nouvelle proposition.
 */

liste_fait ajouter_fait(char* nom_fait, liste_fait base_fait);

/**
 * \fn liste_regle lire_fichier_regle();
 * \brief Fonction qui rempli la base de connaissance en récuperant les valeurs des regles dans un fichier ".txt".
 * \return liste_regle  Retourne la base de connaissance remplie.
 */

liste_regle lire_fichier_regle();

/**
 * \fn Regle* activer_prop(Regle *R, Proposition prop)
 * \brief Fonction qui met la a vrai dans la prémisse de la regle la proposition entré dans la fonction.
 * \param R Regle ou l'on va mettre a vrai la proposition entré en parametre.
 * \param prop Proposition a mettre a vrai dans la prémisse.
 * \return Regle  Retourne un pointeur sur la Regle que l'on a modifie.
 */

Regle* inference_regle(Regle* R, liste_fait base_fait);

/**
 * \fn Regle* activer_prop(Regle *R, Proposition prop)
 * \brief Fonction qui met la a vrai dans la prémisse de la regle la proposition entré dans la fonction.
 * \param R Regle ou l'on va mettre a vrai la proposition entré en parametre.
 * \param prop Proposition a mettre a vrai dans la prémisse.
 * \return Regle  Retourne un pointeur sur la Regle que l'on a modifie.
 */

Regle* activer_prop(Regle *R, Proposition prop);

/**
 * \fn void affiche_liste(Regle *R)
 * \brief Fonction qui affiche le nom, la prémisse et la conclusion d'une regle.
 * \param R Regle a afficher.
 */

void affiche_liste(Regle *R);

/**
 * \fn  void afficher_fait(liste_fait base_fait)
 * \brief Fonction qui affiche la base de fait.
 * \param base_fait Base de fait a afficher.
 */

void afficher_fait(liste_fait base_fait);

/**
 * \fn liste_fait creer_liste_fait(void)
 * \brief Fonction qui crée une liste de fait vide.
 * \return liste_fait  Retourne une liste de fait vide.
 */

liste_fait creer_liste_fait(void);

/**
 * \fn liste_regle Remise_a_zero_base_connaissance(liste_regle BC)
 * \brief Fonction qui remet a FAUX toutes les prémisses et conclusions des regles de la base de connaissance.
 * \param BC Base de connaissance a remette a zero.
 * \return liste_regle  Retourne la base de connaissance.
 */

liste_regle Remise_a_zero_base_connaissance(liste_regle BC);

/**
 * \fn Regle* remise_a_zero_regle(Regle *R)
 * \brief Fonction qui remet a FAUX la prémisse d'une regle.
 * \param R Pointeur sur la regle a modifier.
 * \return Regle  Retourne la regle modififé.
 */

Regle* remise_a_zero_regle(Regle *R);

/**
 * \fn Regle* Suppression_Proposition(Regle* r, Proposition prop)
 * \brief Fonction qui supprime une proposition de la prémisse d'une regle.
 * \param r Pointeur sur la regle a modifier.
 * \param prop Proposition a supprimer.
 * \return Regle  Retourne la regle modififé.
 */

Regle* Suppression_Proposition(Regle* r, Proposition prop);

/**
 * \fn Regle* tester_ccl(Regle* R)
 * \brief Fonction qui met a VRAI la conclusion d'une regle si la prémisse est vrai, ou FAUX sinon.
 * \param R Pointeur sur la regle a modifier.
 * \return Regle  Retourne la regle modififé.
 */

Regle* tester_ccl(Regle* R);

/**
 * \fn Regle* tete_bc(liste_regle bc)
 * \brief Fonction qui renvoie la tete de la base de connaissance.
 *
 * \param bc Base de connaissance dont on veut la tete.
 * \return Regle  Retourne la regle en tete de liste de la base de connaissance.
 */

Regle* tete_bc(liste_regle bc);



#endif // CRAFT_H_INCLUDED
