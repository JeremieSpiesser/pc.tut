/**
 * \file structures.h
 * \brief Module relatif à la gestion des structures de donnees utilisees
 * \author Baptiste Signolle
 * \version 1.0
 * \date 12/04/2020
 */

#ifndef PCTUT_STRUCTURES_H
#define PCTUT_STRUCTURES_H
#include "carte.h"

struct maillon{
	carte c;
	struct maillon* prev;
	struct maillon* next;
};

typedef struct maillon* liste;

/**
 * Permet la création d'une liste doublement chainée vide
 * @return une liste doublement chaînée vide (càd un pointeur null)
 */
liste vide();

/**
 * Indique si la liste est vide ou non
 * @param ldc liste doublement chaînée initialisée
 * @return 1 si la liste est vide (càd s'il s'agit d'un pointeur null), 0 sinon
 */
int isEmpty(liste ldc);

/**
 * Indique la longueur de la liste
 * @param ldc liste doublement chainée initialisée et ne possédant pas de cycle
 * @return le nombre d'éléments dans ldc
 */
int len(liste ldc);

/**
 * Permet l'ajout de la carte c dans la liste pointée par pldc de telle sorte que c se trouve à l'indice i. Si i=-1, l'ajout se fait en fin de liste
 * @param c carte initialisée
 * @param indice entier positif ou nul ou égal à -1
 * @param pldc pointeur vers une liste doublement chaînée initialisée et sans cycle
 * @return 1 si l'ajout est un succès, 0 en cas d'échec
 */
int addIndice(carte c, int indice, liste* pldc);

/**
 * Permet l'ajout de la carte c en tête de la liste pointée par pldc
 * @param c carte initialisée
 * @param pldc pointeur vers une liste doublement chaînée initialisée
 */
void addHead(carte c, liste* pldc);

/**
 * Permet l'ajout de la carte c à la fin de la liste pointée par pldc
 * @param c carte initialisée
 * @param pldc pointeur vers une liste doublement chaînée initialisée et sans cycle
 */
void addTail(carte c, liste* pldc);

/**
 * Renvoie la carte située à l'indice indice de la liste pointée par pldc
 * /!\ la carte est supprimée de la liste, mais n'est pas détruite
 * @param indice entier positif ou nul ou égal à -1
 * @param pldc pointeur vers une liste chainée initialisée sans cycle
 * @return la carte située à l'indice indice si celui-ci est inférieur à la longueur de la liste, le pointeur NULL sinon. Si indice vaut -1 on récupère la dernière carte de la liste, si la liste est vide le pointeur NULL est renvoyé
 */
carte getIndice(int indice, liste* pldc);

/**
 * Renvoie la carte située en tête de la liste pointée par pldc
 * /!\ la carte est supprimée de la liste, mais n'est pas détruite
 * @param pldc pointeur vers une liste chainée initialisée
 * @return la carte située en tête de liste, si la liste est vide le pointeur NULL est renvoyé
 */
carte getHead(liste* pldc);

/**
 * Renvoie la dernière carte de la liste pointée par pldc
 * /!\ la carte est supprimée de la liste, mais n'est pas détruite
 * @param pldc pointeur vers une liste chainée initialisée sans cycle
 * @return la dernière carte de la liste, si la liste est vide le pointeur NULL est renvoyé
 */
carte getTail(liste* pldc);

/**
 * Permet de remplacer la carte d'indice indice de la liste pointée par pldc par la carte c. Remplace la dernière carte si l'indice vaut -1
 * /!\  Attention la carte initialement à l'indice i existe toujours -> fuite mémoire si mal géré, la renvoyer à la place du int ?
 * @param c une carte initialisée
 * @param indice un entier positif ou nul ou égal à -1
 * @param pldc un pointeur vers une liste doublement chainée initialisée sans cycle
 * @return 1 si l'affectation de la nouvelle carte est un succès, 0 sinon (si l'indice est supérieur ou égal à la longueur de la liste, ou si indice vaut -1 et la liste est vide)
 */
int setIndice(carte c, int indice, liste* pldc);

/**
 * Permet de remplacer la première carte de la liste pointée par pldc par la carte c.
 * /!\  Attention la carte initialement à l'indice i existe toujours -> fuite mémoire si mal géré, la renvoyer à la place du int ?
 * @param c une carte initialisée
 * @param pldc un pointeur vers une liste doublement chainée initialisée
 * @return 1 si l'affectation de la nouvelle carte est un succès, 0 sinon (si la liste est vide) 
 */
int setHead(carte c, liste* pldc);

/**
 * Permet de remplacer la dernière carte de la liste pointée par pldc par la carte c.
 * /!\  Attention la carte initialement à l'indice i existe toujours -> fuite mémoire si mal géré, la renvoyer à la place du int ?
 * @param c une carte initialisée
 * @param pldc un pointeur vers une liste doublement chainée initialisée sans cycle
 * @return 1 si l'affectation de la nouvelle carte est un succès, 0 sinon (si la liste est vide) 
 */
int setTail(carte c, liste* pldc);

/**
 * Renvoie la carte située à l'indice indice de la liste ldc. Renvoie la dernière si l'indice est -1
 * /!\ la carte n'est pas supprimée de la liste, toute action sur celle-ci peut avoir des conséquences désastreuses sur la liste et son fonctionnement. A utiliser avec sagesse
 * @param indice entier positif ou nul ou égal à -1
 * @param ldc liste doublement chaînée initialisée sans cycle
 * @return la carte située à l'indice indice, la dernière si indice vaut -1. Renvoie un pointeur NULL si l'indice est supérieur à la longueur de la liste ou si la liste est vide et l'indice vaut -1
 */
carte seeIndice(int indice, liste ldc);

/**
 * Renvoie la première carte de la liste ldc.
 * /!\ la carte n'est pas supprimée de la liste, toute action sur celle-ci peut avoir des conséquences désastreuses sur la liste et son fonctionnement. A utiliser avec sagesse
 * @param ldc liste doublement chaînée initialisée
 * @return la première carte de ldc, un pointeur NULL si la liste est vide 
 */
carte seeHead(liste ldc);

/**
 * Renvoie la dernière carte de la liste ldc.
 * /!\ la carte n'est pas supprimée de la liste, toute action sur celle-ci peut avoir des conséquences désastreuses sur la liste et son fonctionnement. A utiliser avec sagesse
 * @param ldc liste doublement chaînée initialisée sans cycle
 * @return la dernière carte de ldc, un pointeur NULL si la liste est vide 
 */
carte seeTail(liste ldc);

/**
 * Supprime tous les maillons de la liste et les éléments liés aux dits maillons
 * @param pldc pointeur vers une liste doublement chaînée initialisée
 */
void destruction(liste* pldc);

/**
 * Inverse l'ordre des éléments de la liste pointée par pldc
 * @param pldc pointeur vers une liste doublement chaînée initialisée sans cycle
 */
void reverse(liste* pldc);

/**
 * Supprime de la liste pointée par pldc la dernière carte de type t
 * @param pldc pointeur vers une liste doublement chaînée inittialisée sans cycle
 * @param t type de carte
 * @return la dernière carte d'instance t, le pointeur NULL si une telle carte n'est pas trouvée
 */
carte getLastInstanceOf(liste* pldc, carte_type t);

/**
 * Renvoie une liste qui fusionne les listes pointée par pldc1 et pldc2 en alternant les éléments. Si une liste est plus courte que l'autre, le reste de la liste la plus longue est directement ajoutée (vu que l'alternance n'a plus de sens par absence d'élément dans la liste la plus courte)
 * /!\ les éléments de la liste renvoyée ne sont pas des copies, toute action (de suppression notamment) sur une des trois liste aura un effet sur les deux autres
 * @param pldc1 pointeur vers une liste doublement chaînée initialisée sans cycle
 * @param pldc2 pointeur vers une liste doublement chaînée initialisée sans cycle
 * @return une liste fusionnant les éléments des deux listes pointées par les arguments
 */
liste merge(liste* pldc1, liste* pldc2);

/**
 * Fusionne les listes pointée par pldc1 et pldc2 en alternant les éléments dans la liste pointée par pldc1. Si une liste est plus courte que l'autre, le reste de la liste la plus longue est directement ajoutée (vu que l'alternance n'a plus de sens par absence d'élément dans la liste la plus courte)
 * /!\ les éléments de la liste pointée par pldc2 ne sont pas copiés, toute action (de suppression notamment) sur une des listes aura un effet sur l'autre
 * @param pldc1 pointeur vers une liste doublement chaînée initialisée sans cycle
 * @param pldc2 pointeur vers une liste doublement chaînée initialisée sans cycle
 */
void mergeIn(liste* pldc1, liste* pldc2);

void shuffle(liste* pldc);
void shuffledMerge(liste* pldc1, liste* pldc2);

/**
 * Supprime le i ème élément de la liste pointée par pldc
 * @param pldc pointeur vers une liste doublement chainée initialisée sans cycle
 * @param i indice de l'élément à supprimer
 * @reuturn 1 si l'élément est bel et bien supprimé, 0 sinon
 */
int pop(liste* pldc, int i);

/**
 * Supprime la carte c de la liste
 * /!\ il s'agit de la suppression de l'élément (égalité mémorielle), pas de la prmeière instance
 * @param pldc pointeur vers une liste doublement chaînée initialisée sans cycle
 * @param c carte initialisée
 * @return 1 si la suppression est un succès, 0 sinon
 */
int removeEqual(liste* pldc, carte c);

/**
 * Supprime la première instance de la carte c de la liste pointée par pldc
 * @param pldc pointeur vers une liste doublement chaînée initialisée sans cycle
 * @param c carte initialisée
 * @return 1 si la suppression est un succès, 0 sinon
 */
int removeInstance(liste* pldc, carte c);

#endif //PCTUT_STRUCTURES_H
