/**
 * \file interface.c
 * \brief Implémentation de interface.h
 * \author Pierre-Marie Lefrançois
 * \date 24/04/2020
 *
 * Interface programme <-> utilisateur
 * qui permet d'afficher des informations
 * ou de récupérer des entrées utilisateur
 */

#include "../headers/interface.h"
#include "../headers/plateau.h"
#include "../headers/carte.h"
#include "../headers/structures.h"

void dispNewTurn(int turnNumber) {
    printf("\n--- DÉBUT DU TOUR N°%d ---\n", turnNumber);
    if (turnNumber == 6) printf("Vous pouvez maintenant avoir 2 cartes Personnel en même temps !\n");
    else if (turnNumber == 11) printf("Vous pouvez maintenant avoir 3 cartes Personnel en même temps !\n");
    printf("\n");
}

void dispNewPhase(int turnNumber, int phaseNumber, plateau board) {
    printf("- Tour %d - Phase %d\nC'est à l'ENSIIE n°%d de jouer -\n", turnNumber, phaseNumber, getUID(board));
}

void dispBoard(plateau board) {
    int nPE = getPE(board);
    int nDD = getDD(board);
    liste FISECards = getFISE(board);
    int nFISE = countFISE(board);
    liste FISACards = getFISA(board);
    int nFISA = countFISA(board);
    liste hand = getMain(board);
    liste ground = getPJ(board);

    printf("- Plateau de l'ENSIIE n°%d -\n", getUID(board));
    printf("|\n");
    printf("↳ Points DD : %d\n", nDD);
    printf("↳ Points d'énergie : %d\n", nPE);
    printf("|\n");
    if (nFISE > 0 && nFISA > 0) printf("↳ Cartes élève (%d FISE et %d FISA) :\n", nFISE, nFISA);

    while (!isEmpty(FISECards)) {
        int pDevel = FISECards->c.spe.eleve->p_devel;
        int pDura = FISECards->c.spe.eleve->p_dura;
        int pEnergie = FISECards->c.spe.eleve->p_energie;
        printf("| ↳ FISE - développement : %d, durabilité : %d, énergie : %d\n", pDevel, pDura, pEnergie);
        FISECards = FISECards->next;
    }
    while (!isEmpty(FISACards)) {
        int pDevel = FISACards->c.spe.eleve->p_devel;
        int pDura = FISACards->c.spe.eleve->p_dura;
        int pEnergie = FISACards->c.spe.eleve->p_energie;
        printf("| ↳ FISA - développement : %d, durabilité : %d, énergie : %d\n", pDevel, pDura, pEnergie);
        FISACards = FISACards->next;
    }

    printf("|\n");
    printf("↳ Cartes dans la main :\n");
    while (!isEmpty(hand)) {
        printf("| ↳ %s - Coût : %d\n", getCardName(hand->c), cout(hand->c));
        hand = hand->next;
    }
    printf("|\n");
    printf("↳ Cartes sur le terrain :\n");
    while (!isEmpty(ground)) {
        printf("| ↳ %s\n", getCardName(ground->c));
        ground = ground->next;
    }

    printf("\n");
}

carte askEleve(plateau board) {
    printf("Eh, ENSIIE n°%d, tu veux quel type de carte élève ?\n", getUID(board));
    printf("↳ 1 : FISE\n");
    printf("↳ 2 : FISA\n");

    int res = 0;

    while (res == 0) {
        scanf("%d", &res);
        if (res == 1) {
            printf("Une FISE, ça marche !\n");
        } else if (res == 2) {
            printf("Une FISA, ça marche !\n");
        } else {
            printf("J'ai pas compris. Reessaye.\n");
            res = 0;
        }
    }

    return createCarte(-res);
}

carte askAction(plateau board) {
    liste hand = getMain(board);
    int handLength = len(hand);
    carte* menu = malloc((handLength + 1) * sizeof(carte*));
    menu[0] = createCarte(0);
    int bPE = getPE(board);

    printf("Bon, maintenant il est temps de choisir une carte.\nQue veux-tu ?\n");
    printf("↳ 0 : Terminer la phase\n");

    int menuIndex = 1;
    while (!isEmpty(hand)) {
        int cout_ = cout(hand->c);
        if (bPE <= cout_) {
            printf("↳ %d : %s, coût : %d PE\n", menuIndex, getCardName(hand->c), cout_);
            menu[menuIndex] = hand->c;
            menuIndex++;
        }
        hand = hand->next;
    }

    int choice;
    int status = 0;
    while (status != 1 || choice < 0 || choice >= menuIndex) {
        status = scanf("%d", &choice);
    }

    carte ret = menu[choice];
    free(menu);
    return ret;
}

void dispWinner(plateau board) {
    printf("Super partie ! Mais qui a gagné ? ...\n");
    if (board == NULL) printf("Ah... c'est un match nul.\n")
    else printf("C'est l'ENSIIE n°%d bien sûr !\n", getUID(board));
}

void dispError(int errorId) {
    switch(errorId) {
        case 1:
            printf("Et hop, tu as joué une carte.");
            break;
        case -1:
            printf("Oups, tu n'as pas assez de PE !");
            break;
        case -2:
            printf("Mince, cette carte n'en est pas une. Enfin, elle est vide quoi.");
            break;
        default:
            break;
    }
}