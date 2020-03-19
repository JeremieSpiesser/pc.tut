//
// Created by Jérémie Spiesser on 06/03/2020.
//

#ifndef PCTUT_PLATEAU_H
#define PCTUT_PLATEAU_H
#include "carte.h"

typedef struct plateau* plateau;

//@requires rien
//@asigns rien
//@ensures retourne un nouveau plateau
plateau createPlateau();

//@requires un plateau valide
//@assigns libèration de la case mémoire associée au plateau passé en argument
//@ensures libère la case mémoire associée au plateau passé en argument
void freePlateau(plateau p);

//@requires un plateau correct non vide
//@assigns le deck et la main
//@ensures pioche une carte du deck et la met dans la main
void piocherCarte(plateau p);

//@requires un tableaux de plateaux p, n taille de p, nt : numéro de tour
//@assigns rien
//@ensures signifie au plateau qu'un nouveau tour commence
void nouveauTour(plateau p[], int n, int nt);

//@requires un plateau correct non vide, pnt : pointe vers le numéro de tour (commence à 1)
//@assigns rien
//@ensures retourne nombre de cartes piochées par une ENSIIE au début de sa phase
int nbCartesNewPhase(plateau p, int* pnt);

//@requires un plateau p valide, une carte c et un entier nt numéro de tour (commence à 1)
//@assigns ajoute la carte a la liste des cartes en jeu
//@ensures l'ajout de la carte sur le plateau, renvoie 0 en cas de succès, 1 sinon (si il y a déjà trop de carte personnel sur le terrain par example)
int addCarte(plateau p, carte c, int nt);

//@requires un plateau p initialise et une carte c de type 1 (cad de type eleve)
//@assigns ajoute la carte eleve a la liste des cartes en jeu par le biais de la fonction addCarte
//@ensures l'ajout de la carte eleve au plateau
//La carte eleve est passee par le type carte, suivant l'usage il vaudrait peut-etre mieux la passer par le type carte_eleve
void addEleve(plateau p, carte c);

//@requires un plateau p initialise et une carte c de la main (de type action ou personnel)
//@assigns retire c de la main pour la placer sur le terrain
//@ensures la carte c est alors jouee
void playCarte(plateau p, carte c);

//@requires un plateau p initialise
//@assigns rien
//@ensures retourne le nombre de points d'energie a la disposition de l'ENSIIE du plateau
int nbPE(plateau p);

//@requires un tableau de plateaux p, n taille de p
//@assigns rien
//@ensures retourne -2 si la partie n'est pas terminee, -1 si egalite et sinon renvoie l'indice du plateau gagnant (il ne peut y en avoir qu'un) 
int finPartie(plateau p[], int n);

//@requires un plateau p initialise
//@assigns rien
//@ensures retourne le nombre de cartes eleve qui seront ajoutees au plateau
int nbNewElevesNewPhase(plateau p);

//@requires un tableau de plateaux p, n taille de p
//@assigns rien
//@ensures la cloture du tour, comprend le calcul des DD de chaque plateau 
void finTour(plateau p[], int n);

#endif //PCTUT_PLATEAU_H
