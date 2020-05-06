#include "../headers/carte.h"
#include <stdlib.h>
#include <string.h>


int cout(carte c){
    switch (c.type){
        case CARTE_PERSONNEL:
            return c.spe.perso->cout;
        case CARTE_ACTION:
            return c.spe.action->cout;
    }
    return 0;
}

int getCardName(carte c){
    switch (c.type){
        case CARTE_PERSONNEL:
            return c.spe.perso->nom;
        case CARTE_ACTION:
            return c.spe.action->nom;
        case CARTE_ELEVE:
            return c.spe.eleve->nom;
    }
}

char* getEffet(carte c){
    char* res = calloc(24, sizeof(char));
    switch (c.type){
        case CARTE_PERSONNEL:
            strcpy(res, c.spe.perso->effets);
            strcat(res, "00000000000");
            return res;
        case CARTE_ACTION:
            strcpy(res, "00000000000000000000000");
            res[c.spe.action->numero - 9] = '1';
            return res;
    }
    return NULL;
}

int isInstanceOf(carte c, carte_type type){
    return c.type == type;
}

void freeCarte(carte c){
    switch (c.type){
        case CARTE_ELEVE:
            free(c.spe.eleve->nom);
            free(c.spe.eleve);
            break;
        case CARTE_PERSONNEL:
            free(c.spe.perso->nom);
            free(c.spe.perso->effets);
            free(c.spe.perso);
            break;
        case CARTE_ACTION:
            free(c.spe.action->nom);
            free(c.spe.action);
            break;
    }
}

void processPersonnel(carte_personnel p){
    int cout = 3;
    char* effets = "";
    char* nom = "";

    switch (p->numero) {
        case 1:
            nom = "Thomas Lim";
            effets = "100000000000";
            break;
        case 2:
            nom = "Marie Szafranski";
            effets = "010000000000";
            break;
        case 3:
            nom = "Alain Faye ♥";
            effets = "001000000000";
            break;
        case 4:
            nom = "Christophe Mouilleron";
            effets = "000100000000";
            break;
        case 5:
            nom = "Stefania Dumbrava";
            effets = "000010000000";
            break;
        case 6:
            nom = "Julien Forest";
            effets = "000001000000";
            break;
        case 7:
            nom = "Nicolas Brunel";
            effets = "000000100000";
            break;
        case 8:
            nom = "Laurence Bourard";
            effets = "000000010000";
            break;
        case 9:
            nom = "Dimitri Watel";
            cout = 5;
            effets = "101000000000";
            break;
        case 10:
            nom = "Vitera Y";
            cout = 5;
            effets = "010100000000";
            break;
        case 11:
            nom = "Kevin Goilard";
            cout = 5;
            effets = "000010100000";
            break;
        case 12:
            nom = "Vincent Jeannas";
            cout = 5;
            effets = "000001010000";
            break;
        case 13:
            nom = "Massinissa Merabet";
            cout = 7;
            effets = "000000000020";
            break;
        case 14:
            nom = "Anne-Laure Ligozat";
            cout = 8;
            effets = "000000002011";
            break;
        case 15:
            nom = "Catherine Dubois";
            cout = 8;
            effets = "000000000211";
            break;
        case 16:
            nom = "Eric Lejeune";
            cout = 10;
            effets = "110001000100";
            break;
        case 17:
            nom = "Christine Mathias";
            cout = 10;
            effets = "001100010100";
            break;
        case 18:
            nom = "Katrin Salhab";
            cout = 15;
            effets = "220000000001";
            break;
        case 19:
            nom = "Abass Sagna";
            cout = 15;
            effets = "002200000001";
            break;
        case 20:
            nom = "Laurent Prével";
            cout = 20;
            effets = "222200001112";
            break;

    }
    p->cout = cout;
    p->effets = effets;
    p->nom = nom;
}

void processAction(carte_action p){
    int cout = 0;
    int quantite = 0;
    char* nom = "";

    switch (p->numero) {
        case 21:
            nom = "Cours Développement Durable";
            cout = 2;
            quantite = 3;
            break;
        case 22:
            nom = "Recrutement";
            cout = 2;
            quantite = 3;
            break;
        case 23:
            nom = "Rentrée FISE";
            cout = 3;
            quantite = 2;
            break;
        case 24:
            nom = "Rentrée FISA";
            cout = 3;
            quantite = 2;
            break;
        case 25:
            nom = "Energie verte";
            cout = 4;
            quantite = 2;
            break;
        case 26:
            nom = "Diplomation";
            cout = 5;
            quantite = 2;
            break;
        case 27:
            nom = "Décharge";
            cout = 5;
            quantite = 4;
            break;
        case 28:
            nom = "Recyclage";
            cout = 10;
            quantite = 1;
            break;
        case 29:
            nom = "Zéro papier";
            cout = 10;
            quantite = 1;
            break;
        case 30:
            nom = "Repas végétarien";
            cout = 10;
            quantite = 1;
            break;
        case 31:
            nom = "Fermeture annuelle";
            cout = 10;
            quantite = 1;
            break;
    }
    p->nom = nom;
    p->quantite = quantite;
    p->cout = cout;
}

carte createCarte(int num){
    carte res;
    //Carte Vide
    if(num == 0 || num > 31){
        res.type = CARTE_VIDE;
        return res;
    }

    // Carte eleve FISE
    if(num < 0){
        res.type = CARTE_ELEVE;
        res.spe.eleve = malloc(sizeof(struct carte_eleve));
        // Eleve FISE = -1: Eleve FISA = -2
        res.spe.eleve->type = num == -1 ? ELEVE_FISE : ELEVE_FISA;
        res.spe.eleve->p_energie = num == -1 ? 1 : 2;
        res.spe.eleve->nom = num == -1 ? "Eleve FISE" : "Eleve FISA";
        res.spe.eleve->p_devel = 1;
        res.spe.eleve->p_dura = 1;
    }else if(num <= 20){
        res.type = CARTE_PERSONNEL;
        res.spe.perso = malloc(sizeof(struct carte_personnel));
        res.spe.perso->numero = num;
        processPersonnel(res.spe.perso);
    }else{
        res.type = CARTE_ACTION;
        res.spe.action = malloc(sizeof(struct carte_action));
        res.spe.action->numero = num;
        processAction(res.spe.action);
    }
    return res;
}