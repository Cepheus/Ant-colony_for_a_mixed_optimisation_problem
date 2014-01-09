/**********************************************************
Titre : Classe pour la gestion de liste d'�l�ments d'un type de base
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
Cette classe permet de cr�er des listes d'�l�ments dont le 
type peut �tre fix� de fa�on centralis�e.
***********************************************************/

#ifndef CLISTE_H
#include "Job.h"
#define CLISTE_H

// D�finition des valeurs des exceptions pouvant �tre lev�es dans
// cette classe
#define Ajout_impossible 101
#define Suppression_impossible 102
#define Position_hors_liste 103

// D�finition du type d'un �l�ment de la liste
typedef Job Telement; 

class Cliste
{
 // Cette classe repr�sente une ou plusieurs listes d'�l�ments

 // Attributs :
 private :
  unsigned int uiLIStaille; //Cet attribut contient le nombre d'�l�ments de la liste
  Telement * pTeLISliste; // Cet attribut contient la liste des �l�ments
  
 /* ETAT INITIAL
     uiLIStaille = 0
     pTeLISliste = NULL */

 // Primitives :
 public :
   Cliste();
   /* Constructeur par d�faut de la classe 
	E : n�ant
	n�cessite : n�ant
	S : n�ant
	entra�ne : la liste est initialis�e � vide */
   Cliste(const Cliste &);
   /* Constructeur de recopie de la classe 
	E : l'objet que l'on recopie dans l'objet en cours
	n�cessite : n�ant
	S : n�ant
	entra�ne : L'objet en cours contient une copie de l'objet pass� en param�tre */
   ~Cliste();
   /* Destructeur de la classe
	E : n�ant
	n�cessite : n�ant
	S : n�ant
	entra�ne : l'exception est d�truite*/
   Cliste & operator=(const Cliste &);
   /* Surcharge de l'op�rateur d'affectation
	E : l'objet que l'on affecte dans l'objet en cours
	n�cessite : n�ant
	S : L'objet en cours qui a �t� recopi�
	entra�ne : (L'objet en cours contient une copie de l'objet pass� en param�tre) ou
                 (Exception Ajout_impossible : pas assez de m�moire libre) */
   void LISajouter_element(Telement elem, unsigned int pos);
   /* Cette fonction permet d'ajouter un �l�ment dans la liste � la position sp�cifi�e
	E : elem, la valeur � ajouter
	    pos, la position d'insertion
	n�cessite : n�ant
	S : n�ant
	entra�ne : (l'�l�ment est ajout� � la position requise) ou
                 (Exception Ajout_impossible : pas assez de m�moire libre) ou
                 (Exception Position_hors_liste : pos>taille) */
   unsigned int LISlire_taille();
   /* Cette fonction permet de conna�ter la taille de la liste 
	E : rien
	n�cessite : n�ant
	S : la taille de la liste
	entra�ne : (la taille de la liste est retourn�e) */
   Telement LISlire_element(unsigned int pos);
   /* Cette fonction permet de lire la valeur d'un �l�ment dans la liste 
	E : la position de l'�l�ment � lire
	n�cessite : n�ant
	S : la valeur de l'�l�ment
	entra�ne : (la valeur de l'�l�ment est retourn�e) ou
                 (Exception Position_hors_liste : pos>=taille) */
   void LISmodifier_element(Telement elem, unsigned int pos);
   /* Cette fonction permet de modifier la valeur d'un �l�ment dans la liste 
	E : elem, la nouvelle valeur
	    pos, la position de l'�l�ment � modifier
	n�cessite : n�ant
	S : n�ant
	entra�ne : (L'�l�ment est modifi�) ou
                 (Exception Position_hors_liste : pos>=taille) */
   Telement & operator[](unsigned int pos);
   /* Cette fonction permet d'acc�der � la valeur d'un �l�ment dans la liste 
	E : la position de l'�l�ment � lire
	n�cessite : n�ant
	S : l'�l�ment
	entra�ne : (l'�l�ment est accessible) ou
                 (Exception Position_hors_liste : pos>=taille) */
   void LISsupprimer_element(unsigned int pos);
   /* Cette fonction permet de supprimer un �l�ment dans la liste � la position sp�cifi�e
	E : pos, la position de suppression
	n�cessite : n�ant
	S : n�ant
	entra�ne : (l'�l�ment est supprim� � la position requise) ou
	         (Exception Suppression_impossible : taille=0) ou
                 (Exception Position_hors_liste : pos>=taille) */
    void LISvider_liste();
   /* Cette fonction permet de vider la liste
    E : n�ant
	n�cessite : n�ant
	S : n�ant
	entra�ne : (la liste est vide)*/
};
#endif
