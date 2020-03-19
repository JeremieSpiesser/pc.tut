//
// Created by pm on 09/03/2020.
//

#ifndef PCTUT_INTERFACE_H
#define PCTUT_INTERFACE_H
#include "plateau.h"

/* @requires Le numéro du nouveau tour turnNumber, entier positif.
   @assigns Rien
   @ensures Affiche en console un message signifiant qu’un nouveau tour commence ;
      avec toutes les informations utiles (notamment si un nouvel espace pour les cartes Personnel est apparu).
*/
void dispNewTurn(int turnNumber);

/* @requires Le numéro du nouveau tour turnNumber, entier positif. Le numéro de la phase phaseNumber (0 ou 1),
      l'ENSIIE tirée au sort pour commencer au début startedWith (de type plateau).
   @assigns Rien
   @ensures Affiche en console un message signifiant qu’une nouvelle phase commence
      et l’ENSIIE associée à cette phase.
*/
void dispNewPhase(int turnNumber, int phaseNumber, plateau startedWith);

/* @requires Le plateau d'une ENSIIE, qui doit être affiché, de type plateau.
   @assigns Rien
   @ensures Affiche en console le plateau : toutes les informations contenues dedans.
*/
void dispBoard(plateau board);

/* @requires Un entier ensiie correspondant à l'ENSIIE à qui on demande de choisir.
   @assigns Rien
   @ensures Demande au joueur le type de carte élève qu'il choisit et retourne la carte correspondant
      à son choix (FISE ou FISA).
*/
carte askEleve(int ensiie);

/* @requires Le plateau de l'ENSIIE qui joue, de type plateau.
   @assigns Rien
   @ensures Demande à un joueur de choisir une carte de sa main ou de finir sa phase.
      Retourne la carte correspondant au choix ou la carte vide si il finit sa phase.
*/
carte askAction(plateau board);

/* @requires Le plateau du joueur gagnant, de type plateau.
   @assigns Rien
   @ensures Affiche en console un message annonçant le gagnant, ou une égalité.
*/
void dispWinner(plateau board);

#endif //PCTUT_INTERFACE_H
