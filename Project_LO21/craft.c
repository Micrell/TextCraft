/*!
* \file craft.c
* \brief Fichier source des fonctions relative au craft
* \version 1.0
* \date 25/12/2020
* \author Maxime SZYMANSKI Jules PETRY
* -# Lecture des regles dans un fichier :
* Les regles sont lues dans un fichier afin de construire la base de connaissance. Les regles sont les items que le joueur peut craft avec les ressources necessaires.
* -# Moteur d'inference :
*\n Le moteur d'inference permet de donner les crafts possible en fonction de l'inventaire du joueur.
*/
/**
* \mainpage Jeux d'essai LO21
*  Projet de LO21 A20.
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "craft.h"
#include "all.h"
/* V1 du moteur qui deduit tous les crafts possible / A GARDER
liste_fait moteur_inference(liste_regle BC, liste_fait base_fait, bool* repetition)
{



    liste_fait tempa;
    liste_regle tempb;





    do
    {

        *repetition = false;

        tempb = BC;

        while(tempb != NULL)
        {

            if(tempb->regle->conclusion.nom != NULL)
            {
                if( fait_deja_existant(tempb->regle->conclusion.nom,base_fait)==false)
                {
                    tempb->regle = inference_regle(tempb->regle,base_fait);
                    tempb->regle = tester_ccl(tempb->regle);
                    base_fait = ajouter_ccl_fait(tempb->regle,base_fait,repetition);



                }

            }


            tempb = tempb->next;



        }





    }
    while(*repetition==true );

    return base_fait;




}
*/

liste_regle lire_fichier_regle(void )
{
    char temp[21];
    char temp_nom[21];
    char temp_symbole;
    liste_regle tete_base_connaissance;
    tete_base_connaissance = creer_base_vide();
    liste_regle base_connaissance_actuelle = tete_base_connaissance;



    Proposition nouvelle;




    FILE* fichier = NULL;
    fichier = fopen("regle.txt", "r"); // verifier qu'il est different de NULL


    while( fscanf(fichier, "%s %c",temp,&temp_symbole) != EOF )
    {
        switch(temp_symbole)
        {

        case '*' : //si c'est le nom de la regle
            /*
                Nouvelle Regle : Ajouter la regle en queue dans la base de connaissance, avec son nom.
            */
            strcpy(temp_nom,temp);

            base_connaissance_actuelle = ajout_Regle(&tete_base_connaissance,creer_regle(temp_nom));

            break;

        case ';' : // si c'est une proposition

            nouvelle.nom = malloc((strlen(temp)+1 )* sizeof(char));
            strcpy(nouvelle.nom,temp);
            nouvelle.data = true;
            base_connaissance_actuelle->regle = Ajout_proposition_premisse(cherche_regle(temp_nom,base_connaissance_actuelle),nouvelle);

            break;

        case ':' : // si c'est le nom de la conclusion

            nouvelle.nom = malloc((strlen(temp) +1 )* sizeof(char));
            strcpy(nouvelle.nom,temp );
            nouvelle.data = false;
            cherche_regle(temp_nom,base_connaissance_actuelle)->conclusion = nouvelle;

            break;

        }
    }
    fclose(fichier);

    return tete_base_connaissance;
}

liste_fait ajouter_ccl_deduction(Regle* R, liste_fait *deduction)
{

    if(R->conclusion.data == true)
    {
        deduction = ajouter_fait(R->conclusion.nom,deduction);
    }
    return deduction;
}



liste_fait ajouter_ccl_fait(Regle* R, liste_fait BF, bool* test)  //check
{
    if(R->conclusion.data == true && (fait_deja_existant(R->conclusion.nom,BF)==false))
    {
        BF =    ajouter_fait(R->conclusion.nom,BF);
        *test = true;
    }
    else
    {
        *test =false;
    }
    return BF;
}

Regle* tester_ccl(Regle* R)  // check
{

    bool test = true;
    Liste temp;
    temp = R->premisse;

    while(temp != NULL && test == true)
    {
        test = temp->valeur.data;

        temp = temp->next;
    }

    if(test == true)
    {
        R->conclusion.data = true;
    }
    else
    {
        R->conclusion.data = false;
    }
    return R;
}

Regle* activer_prop(Regle *R, Proposition prop)   //check
{

    Liste temp;
    temp = R->premisse;

    while(strcmp(prop.nom,temp->valeur.nom)!=0)
    {
        temp = temp->next;
    }

    if(strcmp(prop.nom,temp->valeur.nom)==0)
    {
        temp->valeur.data = true;
    }
    return R;
}

Regle* remise_a_zero_regle(Regle *R) // check
{
    Liste temp;
    temp = R->premisse;

    while(temp != NULL)
    {
        temp->valeur.data = false;
        temp = temp->next;
    }
    R->conclusion.data = false;

    return R;
}

liste_regle Remise_a_zero_base_connaissance(liste_regle BC)  // check
{
    liste_regle temp;
    temp = BC;

    while(temp != NULL)
    {
        temp->regle = remise_a_zero_regle(temp->regle);
        temp = temp->next;
    }

    return BC;
}

Regle* inference_regle(Regle* R, liste_fait base_fait)  //check
{
    liste_fait temp;
    temp = base_fait;

    while(temp!=NULL)
    {
        if(appartient_premisse(R->premisse,temp->fait) == true)
        {
            R = activer_prop(R, temp->fait);
        }
        temp = temp->next;
    }

    return R;

}

liste_fait moteur_inference(liste_regle BC, liste_fait base_fait,liste_fait *deduction,  bool* repetition)
{
    liste_fait tempa;
    liste_regle tempb;

    do
    {
        *repetition = false;
        tempb = BC;

        while(tempb != NULL)
        {

            if(tempb->regle->conclusion.nom != NULL)
            {
                if( fait_deja_existant(tempb->regle->conclusion.nom,base_fait)==false)
                {
                    tempb->regle = inference_regle(tempb->regle,base_fait);
                    tempb->regle = tester_ccl(tempb->regle);
                    deduction = ajouter_ccl_deduction(tempb->regle, deduction);
                }
            }
            tempb = tempb->next;
        }
    }
    while(*repetition==true );

    return base_fait;
}



void afficher_fait(liste_fait base_fait)
{

    int i=0;
    liste_fait temp;
    temp = base_fait;

    if(base_fait == NULL )
    {
        printf("Vous ne pouvez rien crafter ! \n");
    }
    else
    {
        printf("Vous pouvez crafter : \n");
        while(temp != NULL)
        {
            i++;
            printf(" %s \n",temp->fait.nom);
            temp = temp->next;
        }
    }
}

liste_fait creer_liste_fait(void)
{
    return NULL;
}

liste_fait ajouter_fait(char* nom_fait, liste_fait base_fait)
{
    liste_fait newel;
    liste_fait temp;

    newel = malloc(sizeof(Base_fait));

    newel->fait.nom = malloc((strlen(nom_fait)+1)* sizeof(char));
    strcpy(newel->fait.nom,nom_fait);
    newel->fait.data = true;

    newel->next = NULL;

    if( base_fait == NULL)
    {
        base_fait = newel;

    }
    else
    {
        temp = base_fait;

        while(temp->next != NULL)
        {
            temp = temp->next;
        }

        temp->next = newel;
    }

    return base_fait;
}


Regle* Suppression_Proposition(Regle* r, Proposition prop)
{
    //SI L'ELEMENT APPARTIENT A LA LISTE ALORS ON PEUT LE SUPPRIMER
    if(appartient_premisse(r->premisse, prop) == true)
    {
        Liste temp;
        temp = r->premisse;

        //CAS OU LE MOT A SUPPRIMER EST LE PREMIER DE LA LISTE
        if(strcmp(r->premisse->valeur.nom, prop.nom) == 0)
        {
            temp = r->premisse->next;
            free(r->premisse);
            r->premisse = temp;
        }
        else
        {
            //CAS OU LE MOT A SUPPRIMER N'EST PAS LE PREMIER

            while(temp->next != NULL && strcmp(temp->next->valeur.nom, prop.nom) != 0 )   /*On parcours la liste jusqu'a ce que la prochaine proposition soit celle qui faut supp*/
            {
                temp = temp->next;
            }
            Liste temp2;
            temp2 = temp->next->next;
            free(temp->next);
            temp->next = temp2;
        }

        //SI L'ELEMENT N'APPARTIENT PAS A LA LISTE
    }
    else
    {
        printf("\nLa proposition n'est pas dans la liste\n");
    }
    return r;
}


void afficher_bc(liste_regle lr)
{
    int i = 1;

    if(lr == NULL)
    {
        printf("\nLa base de connaissance est vide");
    }
    else
    {
        liste_regle temp = lr;

        while(temp->next != NULL)
        {
            printf("%deme Regle : %s\n", i, temp->regle->nom_regle);
            temp=temp->next;
            i++;
        }
        printf("%deme Regle : %s\n", i, temp->regle->nom_regle);
    }
}

Regle* creer_regle(char* nom_R)
{

    Regle *nv_regle;
    nv_regle = malloc(sizeof(Regle));
    nv_regle->nom_regle = malloc((strlen(nom_R)+1) * sizeof(char));

    strcpy(nv_regle->nom_regle, nom_R);

    nv_regle->conclusion.nom = NULL;
    nv_regle->conclusion.data = NULL;
    nv_regle->premisse = NULL;


    return nv_regle;


}


bool regle_deja_existante(char* nom, liste_regle BDC)
{

    liste_regle temp;
    temp = BDC;

    bool test = false;

    while(temp != NULL && test==false)
    {

        if(strcmp(nom,temp->regle->nom_regle) == 0 )
        {
            test = true;
        }
        else
        {
            temp = temp->next;
        }
    }
    return test;
}



bool proposition_deja_existante(char* nom, Regle* R)
{

    bool test = false;
    Liste temp;
    temp = R->premisse;

    if(R->premisse   == NULL)
    {
        return false;
    }
    else
    {
        while(temp != NULL && test==false)
        {
            if(strcmp(temp->valeur.nom,nom) == 0 )
            {
                test = true;
            }
            else
            {
                temp = temp->next;
            }
        }
        return test;
    }
}




bool fait_deja_existant(char* nom, liste_fait base_fait)
{

    bool testa = false;
    liste_fait temp;

    temp = base_fait;


    if(base_fait   == NULL)
    {
        return false;
    }
    else
    {
        while(temp != NULL && testa==false)
        {
            if(strcmp(temp->fait.nom,nom) == 0 )
            {
                testa = true;
            }
            else
            {
                temp = temp->next;
            }
        }
        return testa;
    }
}




bool appartient_premisse(Liste premisse, Proposition prop)
{


    if(premisse == NULL)
    {
        return false;
    }
    else if(strcmp(premisse->valeur.nom,prop.nom) == 0)
    {
        return true;
    }
    else
    {
        appartient_premisse(premisse->next, prop);
    }
}

Regle* creer_conclusion(char* nom_ccl, Regle* r)
{
    r->conclusion.nom = malloc((strlen(nom_ccl)+1)* sizeof(char));
    strcpy(r->conclusion.nom,nom_ccl);
    r->conclusion.data = false;

    return r;
}

Regle* Ajout_proposition_premisse(Regle* r, Proposition prop)
{

    Liste newel;
    Liste temp;
    newel = malloc(sizeof(elem));

    newel->valeur.nom = malloc((strlen(prop.nom)+1)* sizeof(char));
    newel->valeur = prop;
    newel->next = NULL;

    if(r->premisse == NULL)
    {
        r->premisse = newel;
    }
    else
    {
        temp = r->premisse;

        while(temp->next != NULL)
        {
            temp = temp->next;
        }

        temp->next = newel;
    }
    return r;
}



bool premisse_est_vide( Liste premisse )
{

    if(premisse == NULL)
    {
        return true;
    }
    else
    {
        return false;
    }

}


Proposition tete_premisse( Liste premisse )
{

    if(premisse_est_vide(premisse) == true)
    {
        printf(" La premisse est vide ! \n");
    }
    else
    {
        return premisse->valeur;
    }

}

Proposition conclusion_regle(  Regle *R)
{
    return R->conclusion;
}

Regle* cherche_regle(char* nom, liste_regle BC)
{

    liste_regle temp;
    temp = BC;

    while(strcmp(nom,temp->regle->nom_regle) != 0)
    {
        temp = temp->next;
    }
    return temp->regle;
}


liste_regle creer_base_vide(void)
{
    return NULL;
}

Regle* tete_bc(liste_regle bc)
{
    return bc->regle;
}

liste_regle ajout_Regle(liste_regle *bc, Regle* r)
{
    liste_regle newel;
    newel = malloc(sizeof(BC));

    newel->regle = r;
    newel->next = NULL;

    afficher_bc(*bc);

    if(*bc == NULL)
    {
        *bc = newel;
        return newel;
    }
    //si BC != NULL
    liste_regle temp = *bc;

    while(temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = newel;

    return newel;
}



void affiche_liste(Regle *R)
{
    int i=0;
    Liste temp;

    temp = R->premisse;

    if(R->premisse == NULL)
    {
        printf("La liste est vide ! \n");
    }
    else
    {
        while(temp != NULL)
        {
            i++;

            printf("Element numero %d qui vaut %s \n ", i, temp->valeur.nom);

            temp = temp->next;

        }
        if(R->conclusion.nom != NULL)
        {

            printf(" \n la conclusion est %s \n ", R->conclusion.nom);
        }
    }
}


