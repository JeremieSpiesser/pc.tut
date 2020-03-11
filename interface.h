//
// Created by pm on 09/03/2020.
//

#ifndef PCTUT_INTERFACE_H
#define PCTUT_INTERFACE_H

void dispNewTurn(int turnNumber);

void dispNewPhase(int turnNumber, int phaseNumber, int startedWith);

void dispBoard(plateau board);

carte askEleve();

carte askAction(plateau board);

void dispWinner(plateau board);

#endif //PCTUT_INTERFACE_H
