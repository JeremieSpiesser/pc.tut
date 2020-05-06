/**
 * \file plateau.h
 * \brief Module relatif à la creation, gestion et destruction de chaque plateau
 * \author Jérémie Spiesser et Baptiste Signolle
 * \version 1.0
 * \date 06/03/2020
 */

#ifndef PCTUT_PLATEAU_H
#define PCTUT_PLATEAU_H
#include "carte.h"
#include "structures.h"

//! Le nombre de joueurs ici doit être < 32 760
#define NB_JOUEURS 2

/**
 * @brief Definition de la structure plateau qui comprend le deck, la main, la liste des élèves en jeu, la liste des cartes action et personnel en jeu, l'identifiant de l'ENSIIE associée au plateau, ses PE et DD
 */
typedef struct plateau* plateau;

/**
 * \fn plateau createPlateau(int uid)
 * Initialise un plateau
 *
 * @param uid identifiant unique permettant d'identifier l'ENSIIE/le plateau
 * @return un nouveau plateau
 */
plateau createPlateau(int uid);

/**
 * \fn void freePlateau(plateau p)
 * Libère la case mémoire associée au plateau passé en argument
 *
 * /!\ : libération de la case mémoire associée au plateau passé en argument
 * @param p plateau valide
 */
void freePlateau(plateau p);

/**
 * \fn void piocherCarte(plateau p)
 * Permet la pioche d'une carte du deck et la met dans la main
 *
 * /!\ : modifie le deck et la main
 * @param p plateau correct non vide
 */
void piocherCarte(plateau p);

/**
 * \fn void nouveauTour(plateau p[], short int n, int* pnt)
 * Prépare les plateaux pour le tour à venir, et met à jour le compteur de tour
 *
 * @param p tableau de plateaux
 * @param n taille de p
 * @param pnt pointeur vers le numéro de tour
 */
void nouveauTour(plateau p[], int* pnt);

/**
 * \fn int nbCartesNewPhase(plateau p, int nt)
 * Calcule le nombre de cartes piochées par une ENSIIE en début de phase
 *
 * @param p plateau correct non vide
 * @param nt numéro de tour (commence à 1)
 * @return le nombre de cartes piochées par une ENSIIE au début de sa phase
 */
int nbCartesNewPhase(plateau p, int nt);



/**
 * \fn void addEleve(plateau p, carte c)
 * Ajoute une carte eleve au plateau
 *
 * /!\ : ajoute la carte eleve a la liste des cartes en jeu par le biais de la fonction addCarte
 * @param p plateau initialise
 * @param c carte de type 1 (cad de type eleve)
 */
void addEleve(plateau p, carte c);

/**
 * \fn void playCarte(plateau p, carte c)
 * Cette fonction permet de jouer une carte
 *
 * /!\ : retire c de la main pour la placer sur le terrain
 * @param p plateau initialise
 * @param c carte de la main (de type action ou personnel)
 */
void playCarte(plateau p, carte c);

/**
 * \fn int nbPE(plateau p)
 * Calcule le nombre de points d'énergie à la disposition de l'ENSIIE du plateau
 *
 * @param p plateau initialise
 * @return le nombre de points d'energie a la disposition de l'ENSIIE du plateau
 */
int nbPE(plateau p);

/**
 * \fn short int finPartie(plateau p[], short int n)
 * Cette fonction permet de déterminer si la partie est terminée
 *
 * @param p tableau de plateaux
 * @param n taille de p
 * @return -2 si la partie n'est pas terminee, -1 si egalite et sinon renvoie l'indice du plateau gagnant (il ne peut y en avoir qu'un)
 */
short int finPartie(plateau p[]);

/**
 * \fn int nbNewElevesNewPhase(plateau p)
 * Cette fonction retourne le nombre de cartes eleve qui seront ajoutees au plateau
 *
 * @param p plateau initialise
 * @return le nombre de cartes eleve qui seront ajoutees au plateau
 */
int nbNewElevesNewPhase(plateau p);

/**
 * \fn void finTour(plateau p[], short int n)
 * Cette fonction assure la cloture du tour, comprend le calcul des DD de chaque plateau
 *
 * @param p tableau de plateaux
 * @param n taille du tableau p
 */
void finTour(plateau p[]);

/**
 * \fn liste getDeck(plateau p)
 * Cette fonction renvoie le deck du plateau
 * @param p plateau
 * @return deck de p
 */
liste getDeck(plateau p);

/**
 * \fn liste getPJ(plateau p)
 * Cette fonction renvoie le plateau de jeu (PJ) ou vont les cartes
 * @param p plateau
 * @return PJ de p
 */
liste getPJ(plateau p);

/**
 * \fn liste getMain(plateau p)
 * Cette fonction renvoie la main du plateau
 * @param p plateau
 * @return main de p
 */
liste getMain(plateau p);

/**
 * \fn liste getDefausse(plateau p)
 * Cette fonction renvoie la défausse du plateau
 * @param p plateau
 * @return défausse de p
 */
liste getDefausse(plateau p);

/**
 * \fn liste getFISE(plateau p);
 * Cette fonction renvoie le paquet de carte FISE
 * @param p
 * @return pile de FISE
 */
liste getFISE(plateau p);

/**
 * \fn liste getFISA(plateau p);
 * Cette fonction renvoie le paquet de carte FISA
 * @param p
 * @return pile de FISA
 */
liste getFISA(plateau p);

/**
 * \fn int getUID(plateau p)
 * Cette fonction renvoie l'UID du plateau
 * @param p plateau
 * @return UID de p
 */
int getUID(plateau p);

/**
 * \fn unsigned int countFISE(plateau p);
 * Cette fonction renvoie le nombre de cartes FISE de p
 * @param p plateau
 * @return nombre de FISE de p
 */
unsigned int countFISE(plateau p);

/**
 * \fn unsigned int countFISA(plateau p);
 * Cette fonction renvoie le nombre de cartes FISA de p
 * @param p plateau
 * @return nombre de FISA de p
 */
unsigned int countFISA(plateau p);

/**
 * \fn int getPE(plateau p);
 * Cette fonction renvoie le nombre de Points d'Energie du plateau
 * @param p
 * @return nombre de PE de p
 */
int getPE(plateau p);

/**
 * \fn int getPE(plateau p);
 * Cette fonction renvoie le nombre de Points de développement durable (DD) du plateau
 * @param p
 * @return nombre de DD de p
 */
int getDD(plateau p);

/**
 * \fn int getTourNb(plateau p)
 * Cette fonction renvoie le numéro de tour
 * @param p plateau
 * @return renvoie le numéro de tour
 */
int getTourNb(plateau p);

/**
 * \fn liste setUID(plateau p)
 * Cette fonction modifie l'UID du plateau
 * /!\ modification de l'UID du plateau
 * @param p plateau
 * @return rien
 */
void setUID(plateau p, int uid);


#endif //PCTUT_PLATEAU_H

