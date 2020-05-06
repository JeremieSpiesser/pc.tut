//
// Created by Jeremie Spiesser on 16/04/2020.
//

#include <stdlib.h>
#include "../headers/plateau.h"
#include "../headers/structures.h"
#include "../headers/carte.h"



/**
 * @brief Definition de la structure plateau qui comprend le deck, la main, la liste des élèves en jeu, la liste des cartes action et personnel en jeu, l'identifiant de l'ENSIIE associée au plateau, ses PE et DD
 */
struct plateau{
    liste FISE;
    liste FISA;
    liste PJ;
    liste Defausse;
    liste Deck;
    liste Main;
    int DD; //Points de développement durable
    int PE;
    int UID;
    int tour;//Numero de tour
    int zeroPapier;
    int vegetarien;
    int nbElevesNewPhase;
};

/**
 * \fn plateau createPlateau(int uid)
 * Initialise un plateau
 *
 * @param uid identifiant unique permettant d'identifier l'ENSIIE/le plateau
 * @return un nouveau plateau
 */
plateau createPlateau(int uid){
    plateau p;
    p->FISE = vide();
    p->FISA = vide();
    p->PJ = vide();
    p->Defausse = vide();
    p->Deck = vide();

    //
    for (int i=1 ; i<= 20 ; i++ ){
        addHead(createCarte(i),&(p->Deck));
    }

    int[] limites = {3,3,2,2,2,2,4,1,1,1,1};
    for (int i=21 ; i<= 31 ; i++ ){
        for (int j = 0; j < limites[i-21] ; ++j) {
            addHead(createCarte(i), &(p->Deck));

        }
    }

    shuffle(&(p->Deck));


    p->Main = vide();
    p->DD   = 0;
    p->PE = 0;
    p->UID = uid;
    p->tour = 0;
    p->zeroPapier = 0;
    p->vegetarien = 0;
    p->nbEleveNewPhase = 1;
    return p;
}

/**
 * \fn void freePlateau(plateau p)
 * Libère la case mémoire associée au plateau passé en argument
 *
 * /!\ : libération de la case mémoire associée au plateau passé en argument
 * @param p plateau valide
 */
void freePlateau(plateau p){
    destruction(p->FISE);
    destruction(p->FISA);
    destruction(p->PJ);
    destruction(p->Defausse);
    destruction(p->Deck);
    destruction(p->Main);
}

/**
 * \fn void piocherCarte(plateau p)
 * Permet la pioche d'une carte du deck et la met dans la main
 *
 * /!\ : modifie le deck et la main
 * @param p plateau correct non vide
 */
void piocherCarte(plateau p){
    carte c = getIndice(0,&(p->Deck));
    if (c!=NULL){
        addHead(c,&(p->Main));
    }
}

/**
 * \fn void nouveauTour(plateau p[], short int n, int* pnt)
 * Prépare les plateaux pour le tour à venir, et met à jour le compteur de tour
 *
 * @param p tableau de plateaux
 * @param n taille de p
 * @param pnt pointeur vers le numéro de tour
 */
void nouveauTour(plateau p[], int* pnt){
    *pnt = *ptn + 1;
    for (int i = 0; i < NB_JOUEURS; i=i+1) {
        p[i].tour = *pnt;
        p[i].PE = 0;
    }
    if (*pnt == 1) {//Premier tour : on scramble
        shufflePlateaux(p,NB_JOUEURS);
    } else {//Premier tour, on scramble p
        plateau p1 = p[0];
        for (int i = 0; i < k-1; ++i) {
            p[i]=p[i+1];
        }
        p[NB_JOUEURS-1]=p1;
    }
}

void shufflePlateaux(plateau p[], int n) {
    for (int i = n-1; i > 0 ; i = i-1) {
        int j = rand() % (i+1);
        plateau tmp = p[i];
        p[i] = p[j];
        p[j] = tmp;
    }
}


/**
 * \fn int nbCartesNewPhase(plateau p, int nt)
 * Calcule le nombre de cartes piochées par une ENSIIE en début de phase
 * @param p plateau correct non vide
 * @param nt numéro de tour (commence à 0)
 * @return le nombre de cartes piochées par une ENSIIE au début de sa phase
 */
int nbCartesNewPhase(plateau p, int nt, int np){
    (nt  == 1 ? return 3 : return 1);
}

//OLD
/*
  \fn int addCarte(plateau p, carte c, int nt)
  Ajoute une carte au plateau

  /!\ : ajoute la carte a la liste des cartes en jeu
  @param p plateau valide
  @param c carte
  @param nt entier numéro de tour (commence à 0)
  @return -1 en cas de succès, 1 sinon (si il y a déjà trop de carte personnel sur le terrain par exemple)
 */
//int addCarte(plateau p, carte c, int nt);

/**
 * \fn void addEleve(plateau p, carte c)
 * Ajoute une carte eleve au plateau
 *
 * /!\ : ajoute la carte eleve a la liste des cartes en jeu par le biais de la fonction addCarte
 * @param p plateau initialise
 * @param c carte de type 0 (cad de type eleve)
 */
void addEleve(plateau p, carte c){
    playCarte(&p,1,0,c);
}

/**
 * \fn void playCarte(plateau p, carte c)
 * Cette fonction permet de jouer une carte
 *
 * /!\ : retire c de la main pour la placer sur le terrain
 * @param p plateau initialise
 * @param n taille de p
 * @param i indice i de l'ensiie en jeu
 * @param c carte de la main (de type action ou personnel)
 * @return 1 si ok, -1 si pas assez de PE -2 si c'était une carte vide
 */
int playCarte(plateau[] p, short i, carte c){
    if (estNulle(c) == 1){
        return -2;
    }
    if (cout(c) > p[i]->PE){
        return -1;
    }
    p[i]->PE -= cout(c); // Si élève cout = 0 ça marche aussi

    if (c.type == 1){ // Carte eleve
        if (c.spe->type == 1){//FISE
            setHead(c,&(p[i]->FISE));
        }else if (c.spe->type == 2){//FISA
            setHead(c,&(p[i]->FISA));
        }else{
            return -2;
        }
    } else if (c.type == 2){ // Carte personnel TODO a modifier j'avais mal compris le jeu
        //Je suppose que "Ajouter X pts" ça modif les cartes actuellement sur le plateau de jeu de l'adversaire
        //On compte combien de cartes personnel sont sur le terrain et on vérifie si on a le droit de placer la carte
        int nPerso = 0;
        liste l = p->PJ;
        while (l!=NULL){
            if (l->head.type == 2){
                nPerso = nPerso + 1;
            }
            l = l->next;
        }
        if ((!(nPerso > 1 && nt < 6) || (nPerso > 2 && nt < 11) ) ){ // Si deja trop de carte
            //perso en jeu, on defausse la première qui a été jouée
            setHead(getLastInstanceOf()  );


            p[i]->PE = p[i]->PE - (c.spe)->cout;
            addHead(c,p->PJ);




        }

        char* effets = getEffet(c);
        for (int j = 0; j < 11; ++j) {
            char l = effets[j];
            int x = l - '0';
            //Quand on ajoute les points, on modif les cartes
            //Donc meme dans la defaussse, les cartes restent modif
            if (l!='0'){
            switch j
                {
                    case 1://AE1
                        liste ptr = p[i]->FISE;
                        while (ptr->next !=NULL){
                            carte tmp = ptr->c;
                            carte_eleve eleve = c.spe.eleve;
                            eleve->p_devel += x;
                            ptr = ptr->next;
                        }
                    break;
                    case 2://AE2
                        liste ptr = p[i]->FISE;
                        while (ptr->next !=NULL){
                            carte tmp = ptr->c;
                            carte_eleve eleve = c.spe.eleve;
                            eleve->p_dura += x;
                            ptr = ptr->next;
                        }
                        break;
                    case 3://AA1
                        liste ptr = p[i]->FISA;
                        while (ptr->next !=NULL){
                            carte tmp = ptr->c;
                            carte_eleve eleve = c.spe.eleve;
                            eleve->p_devel += x;
                            ptr = ptr->next;
                        }
                        break;
                    case 4://AA2
                        liste ptr = p[i]->FISA;
                        while (ptr->next !=NULL){
                            carte tmp = ptr->c;
                            carte_eleve eleve = c.spe.eleve;
                            eleve->p_dura += x;
                            ptr = ptr->next;
                        }
                        break;
                    case 5://RE1
                        for (int k = 0; k<n; ++k) {
                            if (k!=i){
                                liste ptr = p[k]->FISE;
                                while (ptr->next !=NULL){
                                    carte tmp = ptr->c;
                                    carte_eleve eleve = c.spe.eleve;
                                    eleve->p_devel += x;
                                    ptr = ptr->next;
                                }

                            }

                        }
                        break;
                    case 6://RE2
                        for (int k = 0; k<n; ++k) {
                            if (k!=i){
                                liste ptr = p[k]->FISE;
                                while (ptr->next !=NULL){
                                    carte tmp = ptr->c;
                                    carte_eleve eleve = c.spe.eleve;
                                    eleve->p_dura += x;
                                    ptr = ptr->next;
                                }

                            }

                        }
                        break;
                    case 7://RA1
                        for (int k = 0; k<n; ++k) {
                            if (k!=i){
                                liste ptr = p[k]->FISA;
                                while (ptr->next !=NULL){
                                    carte tmp = ptr->c;
                                    carte_eleve eleve = c.spe.eleve;
                                    eleve->p_devel += x;
                                    ptr = ptr->next;
                                }

                            }

                        }
                        break;
                    case 8://RA2
                        for (int k = 0; k<n; ++k) {
                            if (k!=i){
                                liste ptr = p[k]->FISA;
                                while (ptr->next !=NULL){
                                    carte tmp = ptr->c;
                                    carte_eleve eleve = c.spe.eleve;
                                    eleve->p_dura += x;
                                    ptr = ptr->next;
                                }

                            }

                        }
                        break;
                    case 9://ADD




                        break;
                    //J'interprète comme


                    //E -> += X dans nbEleveNewPhase


                }}

        }


    } else if (c.type == 3){//Carte action -> direction défausse
            char* effets = getEffet(c);

            for (int j = 12; j < 22 ; ++j) {
                char l = effets[j];
                if (l!='0'){
                switch (j) {
                    case 12://Cours DD
                        p[i]->DD +=1;
                        return 1;
                        break;
                    case 13://recrutement
                        piocherCarte(p[i]);
                        return 1;
                        break;
                    case 14://Rentree fise
                        playCarte(p,n,i,createCarte(1));
                        return 1;
                        break;
                    case 15://rentree fisa
                        playCarte(p,n,i,createCarte(2));
                        return 1;
                        break;
                    case 16://energie verte
                        p[i]->PE += 6;
                        return 1;
                        break;
                    case 17: //Diplomation
                        for (int k = 0; k < n; ++k) {
                            if (k != i) {
                                addHead(getHead(&(p[k]->FISE)), &(p[k]->Defausse));
                                addHead(getHead(&(p[k]->FISA)), &(p[k]->Defausse));
                            }
                        }
                        break;
                    case 18://Décharge
                        for (int k = 0; k < n; ++k) {
                            if (k!=i){
                                addHead($(p[k]->Defausse),getLastInstanceOf(&(p[k]->PJ), 2));
                                /*
                                //Récup de l'indice de la dernière carte personnel (donc la premiere qui a ete mise
                                // en jeu)
                                plateau adversaire = p[k];
                                liste ptr = seeHead(adversaire->PJ);

                                while (ptr->prev != NULL){
                                    if ((ptr->c).type == 2){ //type 2 = perso ?
                                        carte suppr = getHead(ptr);
                                        addHead(suppr,adversaire->Defausse);
                                        return 1;
                                    } else {
                                        ptr = ptr->prev;
                                    }
                                }
                                return -1;*/
                            }}
                        break;
                    case 19: //Recyclage
                       //"Votre pioche" -> ça doit être le deck
                       setHead(c,&(p[i]->Deck));
                       p[i]->Deck = merge(&(p[i]->Deck),&(p[i]->Defausse));
                       p[i]->Defausse = vide();
                       shuffle(&(p[i]->Deck));
                        break;
                    case 20: //Zero papier
                        p[i]->zeroPapier = 1;
                        break;
                    case 21: //Repas végé
                        p[i]->vegetarien = 1;
                        break;
                    case 22: //Fermeture annuelle
                        for (int k = 0; k < NB_JOUEURS ; ++k) {
                            plateau tmp = p[k];
                            tmp->Defausse = merge(&(tmp->Defausse),&(tmp->FISE));
                            tmp->Defausse = merge(&(tmp->Defausse),&(tmp->FISA));
                            tmp->FISE = vide();
                            tmp->FISA = vide();
                        }
                        break;
                }
            }}
        addHead(c,&(p[i]->Defausse));
    }
        return -1;
}

/**
 * \fn int nbPE(plateau p)
 * Calcule le nombre de points d'énergie à la disposition de l'ENSIIE du plateau
 *
 * @param p plateau initialise
 * @return le nombre de points d'energie a la disposition de l'ENSIIE du plateau
 */
int nbPE(plateau p){
    return p->PE;
}

/**
 * \fn short int finPartie(plateau p[], short int n)
 * Cette fonction permet de déterminer si la partie est terminée
 *
 * @param p tableau de plateaux
 * @param n taille de p
 * @return -3 si la partie n'est pas terminee, -1 si egalite et sinon renvoie l'indice du plateau gagnant (il ne peut y en avoir qu'un)
 */
short int finPartie(plateau p[]){
    int max = 0;
    short int indice = 0;
    //A la fin de la boucle : max : maximum des DD, indice : indice d'un des max
    for (int i = 0; i < NB_JOUEURS; i=i+1) {
        if (p[i]->DD > max){
            max = p[i]->DD;
            indice = i;
        }
    }
    //Si aucune des ENSIIE n'a atteind 20 points de DD
    if (max < 20){
        return -3;
    }
    //Vérifie si il y a égalité
    for (int i = 0; i < NB_JOUEURS; i=i+1){
        if (p[i]->DD = max && i != indice){
            return -1;
        }
    }
    //Pas d'égalité, on renvoie l'indice (qui ici correspond bien a un seul plateau : le vaincqueur)
    return indice;
}

/**
 * \fn int nbNewElevesNewPhase(plateau p)
 * Cette fonction retourne le nombre de cartes eleve qui seront ajoutees au plateau
 *
 * @param p plateau initialise
 * @return le nombre de cartes eleve qui seront ajoutees au plateau
 */
int nbNewElevesNewPhase(plateau p){
    return p->nbElevesNewPhase;
}

/**
 * \fn void finTour(plateau p[], short int n)
 * Cette fonction assure la cloture du tour, comprend le calcul des DD de chaque plateau
 *
 * @param p tableau de plateaux
 * @param n taille du tableau p
 */
 //Suppose 2**n joueurs
void finTour(plateau p[]){
    //Celui qui a le plus de points de développement gagne
    plateau gagnant = compare(p,NB_JOUEURS);
     for (int i = 0; i < NB_JOUEURS ; i = i+2) {
         play2(p[i],p[i+1]);
     }
}

void play2(plateau p1, plateau p2){
    int[2] dev = {0,0};
    int[2] dura = {0,0};
    for (int i = 0; i < 2; ++i) {
        liste le = p[i]->FISE;
        liste la = p[i]->FISA;
        while (le->next !=NULL){
            dev[i]+= ((le->c).spe.eleve)->p_devel + p[i]->zeroPapier;
            dura[i]+= ((le->c).spe.eleve)->p_dura + p[i]->vegetarien;
            le = le->next;
        }
        if (p[i]->tour%2 == 1){
            while (la->next !=NULL){
                dev[i]+= ((la->c).spe.eleve)->p_devel + p[i]->zeroPapier;
                dura[i] += ((la->c).spe.eleve)->p_dura + p[i]->vegetarien;
                la = la->next;
            }}
    }
    int d1 = dev[0]-dura[1];
    int d2 = dev[1]-dura[0];
    p1->DD+=(d1>=0) ? d1 : 0;
    p2->DD+=(d2>=0) ? d2 : 0;
}

//Compare récursivement un tableau de plateau et donne le plateau qui a gagné contre tous les opposants
//Si égalité, renvoie le premier
//Ajoute aussi les points
/*
plateau compare(plateau[] p, short int n){
    if (n==1){
        int dev = 0;
        while (le->next !=NULL){
            dev+= ((le->c).spe.eleve)->p_devel + p[i]->zeroPapier;
            le = le->next;
        }
        if (p[i]->tour%2 == 1){
            while (la->next !=NULL){
                dev+= ((la->c).spe.eleve)->p_devel + p[i]->zeroPapier;
                la = la->next;
            }}
        p[0]->tmp_win = dev;
        return p[0];
    }
    if (n==2){
        int[2] dev = {0,0};
        int[2] dura = {0,0};
        for (int i = 0; i < 2; ++i) {
            liste le = p[i]->FISE;
            liste la = p[i]->FISA;
            while (le->next !=NULL){
                dev[i]+= ((le->c).spe.eleve)->p_devel + p[i]->zeroPapier;
                dura[i]+= ((le->c).spe.eleve)->p_dura + p[i]->vegetarien;
                le = le->next;
            }
            if (p[i]->tour%2 == 1){
            while (la->next !=NULL){
                dev[i]+= ((la->c).spe.eleve)->p_devel + p[i]->zeroPapier;
                dura[i] += ((la->c).spe.eleve)->p_dura + p[i]->vegetarien;
                la = la->next;
            }}
        }
        if (dev[0]-dura[1] > dev[1]-dura[0]){//TODO it's a tie
            p[0]->tmp_win = dev[0]-dura[1];
            return p[0];
        }else if (dev[0]-dura[1] < dev[1]-dura[0]){
            p[1]->tmp_win = dev[1]-dura[0];
            return p[1];
        }else {
            return NULL;
        }
    }else{
        short int middle = (n%2 == 0) ? n/2 : (n-1)/2;
        plateau p1 = compare(p,middle) ;
        plateau p2 = compare(p+middle,n-middle);
        compare({p1,p2},2);
    }
}*/

/**
 * \fn liste getDeck(plateau p)
 * Cette fonction renvoie le deck du plateau
 * @param p plateau
 * @return deck de p
 */
liste getDeck(plateau p){
    return p->Deck;
}

/**
 * \fn liste getPJ(plateau p)
 * Cette fonction renvoie le plateau de jeu (PJ) ou vont les cartes
 * @param p plateau
 * @return PJ de p
 */
liste getPJ(plateau p){
    return p->PJ;
}

/**
 * \fn liste getMain(plateau p)
 * Cette fonction renvoie la main du plateau
 * @param p plateau
 * @return main de p
 */
liste getMain(plateau p){
    return p->Main;
}

/**
 * \fn liste getDefausse(plateau p)
 * Cette fonction renvoie la défausse du plateau
 * @param p plateau
 * @return défausse de p
 */
liste getDefausse(plateau p){
    return p->Defausse;
}

/**
 * \fn liste getFISE(plateau p);
 * Cette fonction renvoie le paquet de carte FISE
 * @param p
 * @return pile de FISE
 */
liste getFISE(plateau p){
    return p->FISE;
}

/**
 * \fn liste getFISA(plateau p);
 * Cette fonction renvoie le paquet de carte FISA
 * @param p
 * @return pile de FISA
 */
liste getFISA(plateau p){
    return p->FISA;
}

/**
 * \fn int getUID(plateau p)
 * Cette fonction renvoie l'UID du plateau
 * @param p plateau
 * @return UID de p
 */
int getUID(plateau p){
    return p->UID;
}

/**
 * \fn unsigned int countFISE(plateau p);
 * Cette fonction renvoie le nombre de cartes FISE de p
 * @param p plateau
 * @return nombre de FISE de p
 */
unsigned int countFISE(plateau p){
    unsigned int i = 0;
    liste l = p->FISE;
    while (l != NULL){
        i++;
        l = l->next;
    }
    return i;
}

/**
 * \fn unsigned int countFISA(plateau p);
 * Cette fonction renvoie le nombre de cartes FISA de p
 * @param p plateau
 * @return nombre de FISA de p
 */
unsigned int countFISA(plateau p) {
    unsigned int i = 0;
    liste l = p->FISA;
    while (l != NULL) {
        i++;
        l = l->next;
    }
    return i;
}
/**
 * \fn int getPE(plateau p);
 * Cette fonction renvoie le nombre de Points d'Energie du plateau
 * @param p
 * @return nombre de PE de p
 */
int getPE(plateau p){
    return p->PE;
}

/**
 * \fn int getPE(plateau p);
 * Cette fonction renvoie le nombre de Points de développement durable (DD) du plateau
 * @param p
 * @return nombre de DD de p
 */
int getDD(plateau p){
    return p->DD;
}

/**
 * \fn int getTourNb(plateau p)
 * Cette fonction renvoie le numéro de tour
 * @param p plateau
 * @return renvoie le numéro de tour
 */
int getTourNb(plateau p){
    return p->tour;
}

/**
 * \fn liste setUID(plateau p)
 * Cette fonction modifie l'UID du plateau
 * /!\ modification de l'UID du plateau
 * @param p plateau
 * @return rien
 */
void setUID(plateau p, int uid){
    p->UID = uid;
}
