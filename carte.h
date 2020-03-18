//
// Created by Jérémie Spiesser on 06/03/2020.
//

#ifndef PCTUT_CARTE_H
#define PCTUT_CARTE_H

//On définit dans ce module ce qu'est une carte
//Elle peut soit être une carte élève, soit une carte personnel, soit une carte action
//On crée ces trois sous types

//NB : on travaille parfois avec des char car ce sont des entiers qui prennent moins de place en mémoire que des int classiques
//On les manipule donc comme des nombres, et non pas comme des caractères
struct carte_eleve{
    unsigned char type; //0 : Carte vide, 1 : FISE, 2 : FISA
    int p_devel; //points de développement
    int p_dura; //points de durabilité
    int p_energie; //points d'énergie
};

typedef struct carte_eleve* carte_eleve;

struct carte_personnel{
    unsigned int numero;//Le numéro de la carte personnel (de 1 à 20 dans le jeu de base). Si 0 : carte nulle
    int cout;
    //Pour stocker les différents effets de la carte, on utilise un char* noté effets
    //si effets[i] == 0 : c'est que la carte ne possède pas l'effet numéro i (on numérote les effets de 0 à 11)
    //si effets[i] == k avec k un entier : c'est que la carte possède l'effet numéro i avec comme "paramètre d'effet" k
    //Par exemple, Dimitri Watel a les effets AE1 (numéro 0) et AA1 (numéro 2)
    //le mot décrivant ses effets est : "101000000000\0"
    //Pour, Katrin Salhab a les effets AE1 (numéro 0) de paramètre 2, AE2 (numéro 1) de paramètre 2 et E (numéro 2) de paramètre 1
    //le mot décrivant ses effets est : "220000000001\0"
    char* effets;
};

typedef struct carte_personnel* carte_personnel;

struct carte_action{
    unsigned int numero;//Le numéro de la carte action (de 21 à 31 dans le jeu de base)
    int cout;
    int quantite;//Le nombre de fois que la carte existe dans le deck
};

typedef struct carte_action* carte_action;

//Puis on crée le type carte qui redirige en fonction du cas vers les structures précédemment définies

typedef struct carte {
    unsigned char type;//0 : carte nulle (les champs suivants sont ignorés et/ou valent NULL),
    // 1 : carte_eleve,
    // 2 : carte_personnel
    // 3 : carte_action
    carte_eleve eleve;//NULL si type != 1
    carte_personnel perso;//NULL si type != 2
    carte_action action;//NULL si type != 3
    //Il n'y a qu'un et un seul de ces pointeurs qui est non nul (et qui pointe vers la carte)
} carte;

//Fonctions disponibles

//@requires rien
//@assigne rien
//@ensures retourne le cout de la carte passée en argument (0 si c'est une carte_eleve)
int cout(carte c);

//@requires rien
//@assigns rien
//@ensures retourne un char* décrivant les effets de la carte. Il est obtenu par concaténation de deux mots, l'un pour
//les effets spécifiques aux cartes personnel, l'autre pour les cartes actions
//Exemple: pour la carte 21 (carte action) : "00000000000010000000000\0"
//pour la carte 9 (Dimitri Watel, carte personnel) : "22000000000100000000000\0"
//Comme pour le char* des cartes personnel, on numérote les effets des cartes actions
//Pour une carte élève on renvoie NULL
char* getEffet(carte c);

#endif //PCTUT_CARTE_H