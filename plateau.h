/**
 * \file plateau.h
 * \brief Module relatif à la creatio, gestion et destruction de chaque plateau
 * \author Jérémie Spiesser et Baptiste Signolle
 * \version 1.0
 * \date 06/03/2020
 */

#ifndef PCTUT_PLATEAU_H
#define PCTUT_PLATEAU_H
#include "carte.h"

typedef struct plateau* plateau;

/**
 * Bring a new platal in this world of sufferance dominated by HPC students
 *
 * @param uid identifiant unique permettant d'identifier l'ENSIIE/le plateau
 * @return un nouveau plateau
 */
plateau createPlateau(int uid);

/**
 * Libère la case mémoire associée au plateau passé en argument : p est un elfe liiiiiibre !
 *
 * /!\ : libèration de la case mémoire associée au plateau passé en argument
 * @param p plateau valide
 */
void freePlateau(plateau p);

/**
 * Permet la pioche d'une carte du deck et la met dans la main : c'est l'heure du dududuDUEL !
 *
 * /!\ : modifie le deck et la main
 * @param p plateau correct non vide
 */
void piocherCarte(plateau p);

/**
 * Prépare le plateau au terrible tour qui s'annonce, durant lequel il devra faire face aux ténébreuses forces ENSIIE adverses
 *
 * @param p tableaux de plateaux
 * @param n taille de p
 * @param nt numéro de tour
 */
void nouveauTour(plateau p[], short int n, int* pnt);

/**
 * Calcule le nombre de cartes piochées par une ENSIIE en début de phase
 *
 * @param p plateau correct non vide
 * @param nt numéro de tour (commence à 1)
 * @return le nombre de cartes piochées par une ENSIIE au début de sa phase
 */
int nbCartesNewPhase(plateau p, int nt);

/**
 * Ajoute une carte au plateau
 *
 * /!\ : ajoute la carte a la liste des cartes en jeu
 * @param p plateau valide
 * @param c carte
 * @param nt entier numéro de tour (commence à 1)
 * @return 0 en cas de succès, 1 sinon (si il y a déjà trop de carte personnel sur le terrain par example)
 */
int addCarte(plateau p, carte c, int nt);

/**
 * Ajoute une carte eleve au plateau
 *
 * /!\ : ajoute la carte eleve a la liste des cartes en jeu par le biais de la fonction addCarte
 * @param p plateau initialise
 * @param c carte de type 1 (cad de type eleve)
 */
void addEleve(plateau p, carte c);

/**
 * Cette fonction permet de jouer une carte
 *
 * /!\ : retire c de la main pour la placer sur le terrain
 * @param p plateau initialise
 * @param c carte de la main (de type action ou personnel)
 */
void playCarte(plateau p, carte c);

/**
 * Calcule le nombre de points d'énergie à la disposition de l'ENSIIE du plateau
 *
 * @param p plateau initialise
 * @return le nombre de points d'energie a la disposition de l'ENSIIE du plateau
 */
int nbPE(plateau p);

/**
 * Cette fonction permet de déterminer si la partie est terminée
 *
 * @param p tableau de plateaux
 * @param n taille de p
 * @return -2 si la partie n'est pas terminee, -1 si egalite et sinon renvoie l'indice du plateau gagnant (il ne peut y en avoir qu'un)
 */
short int finPartie(plateau p[], short int n);

/**
 * Cette fonction retourne le nombre de cartes eleve qui seront ajoutees au plateau
 *
 * @param p plateau initialise
 * @return le nombre de cartes eleve qui seront ajoutees au plateau
 */
int nbNewElevesNewPhase(plateau p);

/**
 * Cette fonction assure la cloture du tour, comprend le calcul des DD de chaque plateau
 *
 * @param p tableau de plateaux
 * @param n taille du tableau p
 */
void finTour(plateau p[], short int n);

#endif //PCTUT_PLATEAU_H

