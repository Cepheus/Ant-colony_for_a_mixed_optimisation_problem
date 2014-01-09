/**********************************************************
Titre : Classe pour la gestion de liste d'éléments d'un type de base
***********************************************************
Auteur  : V. T'kindt   
Version : 1.0
Date	: 10/07/2006
-------------------------
Lecteur : V. T'kindt     
Date	: 11/07/2006
***********************************************************
Auteur	: 
Version	:
Date	:
-------------------------
Lecteur : 
Date	: 
***********************************************************
Interface de la classe Cliste.
Cette classe permet de créer des listes d'éléments dont le 
type peut être fixé de façon centralisée.
***********************************************************/

#ifndef CLISTE_H
#include "Job.h"
#define CLISTE_H

// Définition des valeurs des exceptions pouvant être levées dans
// cette classe
#define Ajout_impossible 101
#define Suppression_impossible 102
#define Position_hors_liste 103

// Définition du type d'un élément de la liste
typedef Job Telement; 

class Cliste
{
 // Cette classe représente une ou plusieurs listes d'éléments

 // Attributs :
 private :
  unsigned int uiLIStaille; //Cet attribut contient le nombre d'éléments de la liste
  Telement * pTeLISliste; // Cet attribut contient la liste des éléments
  
 /* ETAT INITIAL
     uiLIStaille = 0
     pTeLISliste = NULL */

 // Primitives :
 public :
   Cliste();
   /* Constructeur par défaut de la classe 
	E : néant
	nécessite : néant
	S : néant
	entraîne : la liste est initialisée à vide */
   Cliste(const Cliste &);
   /* Constructeur de recopie de la classe 
	E : l'objet que l'on recopie dans l'objet en cours
	nécessite : néant
	S : néant
	entraîne : L'objet en cours contient une copie de l'objet passé en paramètre */
   ~Cliste();
   /* Destructeur de la classe
	E : néant
	nécessite : néant
	S : néant
	entraîne : l'exception est détruite*/
   Cliste & operator=(const Cliste &);
   /* Surcharge de l'opérateur d'affectation
	E : l'objet que l'on affecte dans l'objet en cours
	nécessite : néant
	S : L'objet en cours qui a été recopié
	entraîne : (L'objet en cours contient une copie de l'objet passé en paramètre) ou
                 (Exception Ajout_impossible : pas assez de mémoire libre) */
   void LISajouter_element(Telement elem, unsigned int pos);
   /* Cette fonction permet d'ajouter un élément dans la liste à la position spécifiée
	E : elem, la valeur à ajouter
	    pos, la position d'insertion
	nécessite : néant
	S : néant
	entraîne : (l'élément est ajouté à la position requise) ou
                 (Exception Ajout_impossible : pas assez de mémoire libre) ou
                 (Exception Position_hors_liste : pos>taille) */
   unsigned int LISlire_taille();
   /* Cette fonction permet de connaîter la taille de la liste 
	E : rien
	nécessite : néant
	S : la taille de la liste
	entraîne : (la taille de la liste est retournée) */
   Telement LISlire_element(unsigned int pos);
   /* Cette fonction permet de lire la valeur d'un élément dans la liste 
	E : la position de l'élément à lire
	nécessite : néant
	S : la valeur de l'élément
	entraîne : (la valeur de l'élément est retournée) ou
                 (Exception Position_hors_liste : pos>=taille) */
   void LISmodifier_element(Telement elem, unsigned int pos);
   /* Cette fonction permet de modifier la valeur d'un élément dans la liste 
	E : elem, la nouvelle valeur
	    pos, la position de l'élément à modifier
	nécessite : néant
	S : néant
	entraîne : (L'élément est modifié) ou
                 (Exception Position_hors_liste : pos>=taille) */
   Telement & operator[](unsigned int pos);
   /* Cette fonction permet d'accéder à la valeur d'un élément dans la liste 
	E : la position de l'élément à lire
	nécessite : néant
	S : l'élément
	entraîne : (l'élément est accessible) ou
                 (Exception Position_hors_liste : pos>=taille) */
   void LISsupprimer_element(unsigned int pos);
   /* Cette fonction permet de supprimer un élément dans la liste à la position spécifiée
	E : pos, la position de suppression
	nécessite : néant
	S : néant
	entraîne : (l'élément est supprimé à la position requise) ou
	         (Exception Suppression_impossible : taille=0) ou
                 (Exception Position_hors_liste : pos>=taille) */
    void LISvider_liste();
   /* Cette fonction permet de vider la liste
    E : néant
	nécessite : néant
	S : néant
	entraîne : (la liste est vide)*/
};
#endif
