/**
 * \file main.c
 * \brief Programme permettant de jouer à Durableverse
 * \author Tony "Nitorac" Ranini
 * \version 1.0
 * \date 20 mars 2020
 *
 * Fichier principal pour jouer à Durableverse
 *
 */
#include <stdlib.h>
#include "../headers/carte.h"
#include "../headers/interface.h"
#include "../headers/plateau.h"



/**
 * Fonction principale qui permet de jouer à Durableverse
 *
 * @param argc Le nombre d'arguments
 * @param argv Le tableau des arguments
 * @return Renvoie 0 ou l'éventuel code d'erreur survenu
 */
int main(int argc, char* argv[]) {
    short stop = 0;
    int tours = 0;
    short codeFin = 0;

    /*
     *  AVANT LE DEBUT DES TOURS
     *  On crée l'ENSIIE et on pioche les n cartes (n défini par nbCartesNewPhase
     *  à qui on passe le nombre de tour de 0)
     */
    plateau ensiies[NB_JOUEURS];
    for(short i = 0; i < NB_JOUEURS; i++){
        ensiies[i] = createPlateau(i+1);
    }

    /*
     * Chaque itération de la boucle while ci-dessous correspond à un tour
     * Pour un arrêt propre de la boucle, on utilise un flag 'stop'
     */
    while(!stop){
        /*
         * On gère un nouveau tour
         */
        nouveauTour(ensiies, &tours);
        /*
         * On crée l'affichage du nouveau tour
         */
        dispNewTurn(tours);

        /*
         * Chaque joueurs joue dans l'ordre du tableau
         * Chaque itération de la boucle for ci-dessous correspond à une phase
         */
        for(short i = 0; i < NB_JOUEURS; i++){
            plateau current = ensiies[i];

            /*
             * On pioche n cartes avant l'affichage du board
             */
            for(int j = 0; j < nbCartesNewPhase(ensiies[i], tours); j++){
                piocherCarte(current);
            }

            /*
             * On affiche l'état du plateau avant de demander les cartes Eleves
             */
            dispNewPhase(tours, i, current);
            dispBoard(current);

            for(int j = 0; j < nbNewElevesNewPhase(current); j++){
                carte res = askEleve(current);
                if(res.type == 0){
                    break;
                }
                addEleve(current, res);
            }

            /*
             * On réaffiche le plateau pour montrer les changements
             */
            dispBoard(current);

            /*
             * On rentre ici dans la boucle d'action, on en sort uniquement quand
             * le joueur finit son tour
             * Chaque itération correspond à une demande de carte puis l'exécution de son action
             * avant l'affichage du tableau
             */
            while(1){
                carte card = askAction(current);
                if(card.type == 0){
                    break;
                }
                playCarte(current, card);
                /*
                 * On réaffiche le plateau pour montrer les changements
                 */
                dispBoard(current);
            }
        }

        finTour(ensiies);
        if((codeFin = finPartie(ensiies)) != -2){
            /*
             * On pourrait utiliser break directement, mais si on a besoin plus tard dans le futur d'arrêter la
             * boucle de manière propre autant utiliser ça
             */
            stop = 1;
        }
    }

    dispWinner(codeFin == -1 ? NULL : ensiies[codeFin]);

    for(int i = 0; i < NB_JOUEURS; i++){
        freePlateau(ensiies[i]);
    }
    return 0;
}
