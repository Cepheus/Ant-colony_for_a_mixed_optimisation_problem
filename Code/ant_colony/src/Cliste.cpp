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
Corps de la classe Cliste.
Cette classe permet de cr�er des listes d'�l�ments dont le 
type peut �tre fix� de fa�on centralis�e.
***********************************************************/

/*CLASSE Cliste
  DOCUMENTATION
	Attributs : uiLIStaille, entier, contient le nombre d'�l�ments dans la liste
			    pTeliste, pointeur, contient les �l�ments de la liste
	Structure : Cette classe contient des m�thodes permettant l'ajout, la suppression,
	            la modification et la consultation d'�l�ments dans la liste.
	M�thode : L'allocation de la liste est g�r�e dynamiquement par pointeur
	Modules internes :*/
		#include <fstream>
		#include <malloc.h>
		#include "Cliste.h"
		#include "Cexception.h"

//CORPS

/**************************************************************
Nom : Cliste
***************************************************************
Constructeur par d�faut de la classe Cliste : permet 
d'initialiser un objet
***************************************************************
Entr�e : rien
N�cessite : n�ant 
Sortie : rien
Entra�ne : la liste est initialis�e � vide 
***************************************************************/
Cliste::Cliste()
{
 uiLIStaille = 0;
 pTeLISliste = NULL;
 //la liste est vide
}

/**************************************************************
Nom : ~Cliste
***************************************************************
Destructeur de la classe Cliste : permet de d�truire un objet
***************************************************************
Entr�e : rien
N�cessite : n�ant 
Sortie : rien
Entra�ne : la liste est d�sallou�e 
***************************************************************/
Cliste::~Cliste()
{
 free(pTeLISliste);
 //la liste est d�sallou�e
}

/**************************************************************
Nom : Cliste (R)
***************************************************************
Constructeur de recopie de la classe Cliste : permet 
d'initialiser un objet par recopie � partir d'un autre
***************************************************************
Entr�e : l'objet que l'on recopie dans l'objet en cours
N�cessite : n�ant 
Sortie : rien
Entra�ne : L'objet en cours contient une copie de l'objet pass� en param�tre 
***************************************************************/
Cliste::Cliste(const Cliste & objet)
{
 unsigned int iBoucle;

 uiLIStaille = objet.uiLIStaille;
 pTeLISliste = (Telement *) malloc(uiLIStaille*sizeof(Telement));
 // pTeliste pointe sur une zone m�moire allou�e mais "vide"

 for (iBoucle=0;iBoucle<uiLIStaille; iBoucle++)
	 pTeLISliste[iBoucle]=objet.pTeLISliste[iBoucle];
 //la liste objet est recopi�e dans l'objet en cours
}

/**************************************************************
Nom : operator=
***************************************************************
Surcharge de l'op�rateur d'affectation
***************************************************************
Entr�e : l'objet que l'on affecte dans l'objet en cours
N�cessite : n�ant 
Sortie : L'objet en cours qui a �t� recopi�
Entra�ne : (L'objet en cours contient une copie de l'objet pass� en param�tre) ou
                 (Exception Ajout_impossible : pas assez de m�moire libre)
***************************************************************/
Cliste & Cliste::operator=(const Cliste & objet)
{
 unsigned int iBoucle;

 if (uiLIStaille!=0)
 { // Il faut vider la liste en cours
  uiLIStaille=0;
  free(pTeLISliste);
 }

 uiLIStaille=objet.uiLIStaille;
 pTeLISliste = (Telement *) malloc(uiLIStaille*sizeof(Telement));
 if (pTeLISliste==NULL)
 { // L'agrandissement de la liste est impossible : lev�e d'une exception
  Cexception pasmemoire;
  pasmemoire.EXCmodifier_valeur(Ajout_impossible);
  throw(pasmemoire);
 }
 // pTeliste pointe sur une zone m�moire allou�e mais "vide"

 for (iBoucle=0;iBoucle<uiLIStaille; iBoucle++)
	 pTeLISliste[iBoucle]=objet.pTeLISliste[iBoucle];
 //la liste objet est recopi�e dans l'objet en cours
 return *this;
}

/**************************************************************
Nom : LISajouter_element
***************************************************************
Cette fonction permet d'ajouter un �l�ment dans la liste � la position sp�cifi�e
***************************************************************
Entr�e : elem, la valeur � ajouter
	    pos, la position d'insertion
N�cessite : n�ant 
Sortie : rien
Entra�ne : (l'�l�ment est ajout� � la position requise) ou
                 (Exception Ajout_impossible : pas assez de m�moire libre) ou
                 (Exception Position_hors_liste : pos>taille)
***************************************************************/
void Cliste::LISajouter_element(Telement elem, unsigned int pos)
{
 Telement * pTetmp;
 unsigned int iBoucle;

 if (pos>uiLIStaille)
 { // L'insertion a lieu hors tableau : lev�e d'une exception
  Cexception horstableau;
  horstableau.EXCmodifier_valeur(Position_hors_liste);
  throw(Position_hors_liste);
 }
 pTetmp=(Telement *)realloc(pTeLISliste,(uiLIStaille+1)*sizeof(Telement));
 if (pTetmp==NULL)
 { // L'agrandissement de la liste est impossible : lev�e d'une exception
  Cexception pasmemoire;
  pasmemoire.EXCmodifier_valeur(Ajout_impossible);
  throw(pasmemoire);
 }

 pTeLISliste=pTetmp;
 for (iBoucle=uiLIStaille;iBoucle>pos;iBoucle--)
	 pTeLISliste[iBoucle]=pTeLISliste[iBoucle-1];
 pTeLISliste[pos]=elem; 
 uiLIStaille++;
 // L'�l�ment est ins�r� dans la liste � la position demand�e
}

/**************************************************************
Nom : LISlire_element
***************************************************************
Cette fonction permet de conna�ter la taille de la liste 
***************************************************************
Entr�e : rien
N�cessite : n�ant 
Sortie : la taille de la liste
Entra�ne : (la taille de la liste est retourn�e)
***************************************************************/
unsigned int Cliste::LISlire_taille()
{
 return (uiLIStaille);
}

/**************************************************************
Nom : LISlire_element
***************************************************************
Cette fonction permet de lire la valeur d'un �l�ment dans la liste 
***************************************************************
Entr�e : la position de l'�l�ment � lire
N�cessite : n�ant 
Sortie : la valeur de l'�l�ment
Entra�ne : (la valeur de l'�l�ment est retourn�e) ou
                 (Exception Position_hors_liste : pos>=taille) 
***************************************************************/
Telement Cliste::LISlire_element(unsigned int pos)
{
 if (pos>=uiLIStaille)
 { // L'insertion a lieu hors tableau : lev�e d'une exception
  Cexception horstableau;
  horstableau.EXCmodifier_valeur(Position_hors_liste);
  throw(horstableau);
 }

 // La position est dans le tableau : on retourne l'�l�ment demand�
 return pTeLISliste[pos];
}

/**************************************************************
Nom : LISmodifier_element
***************************************************************
Cette fonction permet de modifier la valeur d'un �l�ment dans la liste 
***************************************************************
Entr�e : elem, la nouvelle valeur
	 pos, la position de l'�l�ment � modifier
N�cessite : n�ant 
Sortie : rien
Entra�ne : (L'�l�ment est modifi�) ou
           (Exception Position_hors_liste : pos>=taille)
***************************************************************/
void Cliste::LISmodifier_element(Telement elem, unsigned int pos)
{
 if (pos>=uiLIStaille)
 { // L'insertion a lieu hors tableau : lev�e d'une exception
  Cexception horstableau;
  horstableau.EXCmodifier_valeur(Position_hors_liste);
  throw(horstableau);
 }

 // La position est dans le tableau : on modifie l'�l�ment demand� 
 pTeLISliste[pos]=elem;
}

/**************************************************************
Nom : operator[]
***************************************************************
Cette fonction permet d'acc�der � la valeur d'un �l�ment dans la liste 
***************************************************************
Entr�e : la position de l'�l�ment � lire
N�cessite : n�ant 
Sortie : l'�l�ment
Entra�ne : (L'�l�ment est accessible) ou
            (Exception Position_hors_liste : pos>=taille)
***************************************************************/
Telement & Cliste::operator[](unsigned int pos)
{
 if (pos>=uiLIStaille)
 { // L'insertion a lieu hors tableau : lev�e d'une exception
  Cexception horstableau;
  horstableau.EXCmodifier_valeur(Position_hors_liste);
  throw(horstableau);
 }

 // La position est dans le tableau : on acc�de � l'�l�ment demand� 
 return(pTeLISliste[pos]);
}

/**************************************************************
Nom : LISsupprimer_element
***************************************************************
Cette fonction permet de supprimer un �l�ment dans la liste � la position sp�cifi�e
***************************************************************
Entr�e : la position de l'�l�ment � supprimer
N�cessite : n�ant 
Sortie : rien
Entra�ne : (l'�l�ment est supprim� � la position requise) ou
                (Exception Position_hors_liste : pos>=taille) 
***************************************************************/
void Cliste::LISsupprimer_element(unsigned int pos)
{
 unsigned int iBoucle;

 if (pos>=uiLIStaille)
 { // L'insertion a lieu hors tableau : lev�e d'une exception
  Cexception horstableau;
  horstableau.EXCmodifier_valeur(Position_hors_liste);
  throw(horstableau);
 }

 for (iBoucle=pos;iBoucle<uiLIStaille-1;iBoucle++)
	 pTeLISliste[iBoucle]=pTeLISliste[iBoucle+1];
 uiLIStaille--;

 // L'�l�ment est supprim�
}

/**************************************************************
Nom : LIS_vider_liste()
***************************************************************
Cette fonction permet de vider la liste
***************************************************************
Entr�e : n�ant
N�cessite : n�ant 
Sortie : rien
Entra�ne : (la liste est vide)
***************************************************************/
void Cliste::LISvider_liste()
{
	if(pTeLISliste != NULL)
		free(pTeLISliste);
	pTeLISliste = NULL;
	uiLIStaille = 0;
}
