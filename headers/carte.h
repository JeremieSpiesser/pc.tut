/**
 * \file carte.h
 * \brief Module de gestion des cartes
 * \author Jérémie Spiesser
 * \date 06/03/2020
 *
 * Module de gestion des cartes
 * On définit dans ce module ce qu'est une carte
 * Elle peut soit être une carte élève, soit une carte personnel, soit une carte action
 * On crée ces trois sous types
 *
 */
#ifndef PCTUT_CARTE_H
#define PCTUT_CARTE_H

typedef enum carte_type {
    CARTE_VIDE,
    CARTE_ELEVE,
    CARTE_PERSONNEL,
    CARTE_ACTION
} carte_type;

typedef enum eleve_type {
    ELEVE_VIDE,
    ELEVE_FISE,
    ELEVE_FISA
} eleve_type;
/// \struct carte_eleve
/// \brief champs possibles pour une carte élève
struct carte_eleve{
    eleve_type type;
    char* nom; /*!< Le nom de la carte */
    int p_devel; /*!< points de développement */
    int p_dura; /*!< points de durabilité */
    int p_energie; /*!< points d'énergie */
};

/// Carte eleve
/// \brief pointeur vers un struct carte_eleve
typedef struct carte_eleve* carte_eleve;

/// \struct carte_personnel
/// \brief champs possibles pour une carte personnel
struct carte_personnel{
    unsigned int numero; /*!< Le numéro de la carte personnel (de 1 à 20 dans le jeu de base). Si 0 : carte nulle */
    char* nom; /*!< Le nom de la carte */
    int cout; /*!< Cout de la carte */
    char* effets; /*!< //Pour stocker les différents effets de la carte, on utilise un char* noté effets
    si effets[i] == 0 : c'est que la carte ne possède pas l'effet numéro i (on numérote les effets de 0 à 11)
    si effets[i] == k avec k un entier : c'est que la carte possède l'effet numéro i avec comme "paramètre d'effet" k
    Par exemple, Dimitri Watel a les effets AE1 (numéro 0) et AA1 (numéro 2)
    le mot décrivant ses effets est : "101000000000\0"
    Pour, Katrin Salhab a les effets AE1 (numéro 0) de paramètre 2, AE2 (numéro 1) de paramètre 2 et E (numéro 2) de paramètre 1
    le mot décrivant ses effets est : "220000000001\0" */
};

/// Carte personnel
/// \brief pointeur vers un struct carte_personnel
typedef struct carte_personnel* carte_personnel;

/// \struct carte_action
/// \brief champs possibles pour une carte action
struct carte_action{
    unsigned int numero; /*!< Le numéro de la carte action (de 21 à 31 dans le jeu de base) */
    char* nom; /*!< Le nom de la carte */
    int cout; /*!< Cout de la carte action */
    int quantite; /*!< Le nombre de fois que la carte existe dans le deck */
};

/// Carte action
/// \brief pointeur vers un struct carte_action
typedef struct carte_action* carte_action;

///carte_spe
///union des 3 types de cartes
typedef union carte_spe {
        carte_eleve eleve; 
        carte_personnel perso; 
        carte_action action;
} carte_spe;

/// carte
/// \brief le type carte qui redirige en fonction du cas vers les structures appropriées
typedef struct carte {
    carte_type type;
    carte_spe spe;
} carte ;

//Fonctions disponibles

/// \fn cout(carte c)
/// Obtenir le cout de la carte passée en argument
/// \param c
/// \return le cout de la carte passée en argument (0 si c'est une carte_eleve)

int cout(carte c);

/// \fn getCardName(carte c)
/// Obtenir le nom de la carte passée en argument
/// \param c
/// \return le nom de la carte passée en argument

char* getCardName(carte c);

/// \fn char* getEffet(carte c)
/// \brief donne un char* décrivant les effets de la carte
/// \param c
/// \return retourne un char* décrivant les effets de la carte. Il est obtenu par concaténation de deux mots, l'un pour
/// les effets spécifiques aux cartes personnel, l'autre pour les cartes actions pris dans l'ordre du tableau donné dans le sujet
/// Exemple: pour la carte 21 (carte action) : "00000000000010000000000\0"
/// pour la carte 9 (Dimitri Watel, carte personnel) : "22000000000100000000000\0"
/// Comme pour le char* des cartes personnel, on numérote les effets des cartes actions
/// Pour une carte élève on renvoie NULL

char* getEffet(carte c);

/**
 * @fn void freeCarte(carte c)
 * @brief Libère une carte dans la mémoire
 * @param c La carte à libérer
 */
void freeCarte(carte c);

/**
 * @fn carte createCarte(int num)
 * @brief Alloue une carte dans la mémoire en fonction du numéro donné,
 *
 * Alloue une carte dans la mémoire en fonction du numéro donné tel que :
 * Eleve FISE = -1
 * Eleve FISA = -2
 * Cartes PERSONNELS : 1 à 20 inclus
 * Cartes ACTIONS : 21 à 31 inclus
 * @param num Le numéro de la carte
 * @return La carte créée
 */
carte createCarte(int num);

/**
 * @fn isInstanceOf(carte c, carte_type type)
 * @brief Vérifie si la carte est du type donné
 * @param c La carte à vérifier
 * @param type Le type à vérifier
 * @return Renvoie 1 si la carte donnée possède le type donné, 0 sinon
 */
int isInstanceOf(carte c, carte_type type);

#endif //PCTUT_CARTE_H
