//
// Created by Jérémie Spiesser on 06/03/2020.
//

#ifndef PCTUT_PLATEAU_H
#define PCTUT_PLATEAU_H

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

//@requires un plateau correct non vide, pnt : pointe vers le numéro de tour (commence à 1)
//@assigns rien
//@ensures signifie au plateau qu'un nouveau tour commence
void nouveauTour(plateau p, int* pnt);

//@requires un plateau correct non vide, pnt : pointe vers le numéro de tour (commence à 1)
//@assigns rien
//@ensures retourne nombre de cartes piochées par une ENSIIE au début de sa phase
int nbCartesNewPhase(plateau p, int* pnt)

#endif //PCTUT_PLATEAU_H