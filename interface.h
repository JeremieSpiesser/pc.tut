/**
 * \file interface.h
 * \brief Module d'échange avec l'utilisateur (interface)
 * \author Pierre-Marie Lefrançois
 * \date 09/03/2020
 *
 * Module d'interface programme <-> utilisateur
 * qui permet d'afficher des informations
 * ou de récupérer des entrées utilisateur
 */

#ifndef PCTUT_INTERFACE_H
#define PCTUT_INTERFACE_H
#include "carte.h"
#include "plateau.h"

/**
 * \fn void dispNewTurn(int turnNumber)
 * \brief Affiche en console un message signifiant qu’un nouveau tour commence,
 * avec toutes les informations utiles (notamment si un nouvel espace pour les cartes Personnel est apparu)
 *
 * @param turnNumber entier positif, le numéro du nouveau tour
 */
void dispNewTurn(int turnNumber);

/**
 * \fn void dispNewPhase(int turnNumber, int phaseNumber, plateau board)
 * \brief Affiche en console un message signifiant qu’une nouvelle phase commence
 * et l’ENSIIE associée à cette phase
 *
 * @param turnNumber entier positif, numéro du nouveau tour
 * @param phaseNumber 0 ou 1, numéro de la phase
 * @param board de type plateau, l'ENSIIE qui va jouer
 */
void dispNewPhase(int turnNumber, int phaseNumber, plateau board);

/**
 * \fn void dispBoard(plateau board)
 * \brief affiche en console le plateau : toutes les informations contenues dedans
 *
 * @param board de type plateau, le plateau de l'ENSIIE qui doit être affiché
 */
void dispBoard(plateau board);

/**
 * \fn carte askEleve(plateau board)
 * \brief demande au joueur le type de carte élève qu'il choisit
 *
 * @param board de type plateau, plateau correspondant à l'ENSIIE à qui on demande de choisir
 * @return la carte correspondant au choix du joueur
 */
carte askEleve(plateau board);

/**
 * \fn carte askAction(plateau board)
 * \brief demande à un joueur de choisir une carte de sa main ou de finir sa phase
 *
 * @param board de type plateau, le plateau de l'ENSIIE qui joue
 * @return la carte correspondant au choix ou la carte vide (type 0) si le joueur finit sa phase
 */
carte askAction(plateau board);

/**
 * \fn void dispWinner(plateau board)
 * \brief affiche un message annonçant le gagnant, ou une égalité
 *
 * @param board de type plateau, le plateau du joueur gagnant, peut être NULL en cas d'égalité
 */
void dispWinner(plateau board);

#endif //PCTUT_INTERFACE_H
