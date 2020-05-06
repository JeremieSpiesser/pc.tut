/**
 * \file structures.c
 * \brief Module relatif à la gestion des structures de données utilisées
 * \author Baptiste Signolle
 * \version 1.0
 * \date 12/04/2020
 */

#include <stdio.h>
#include <stdlib.h>
#include "carte.h"
/*
typedef int* carte;
*/
struct maillon{
	carte head;
	struct maillon* prev;
	struct maillon* next;
};

typedef struct maillon* liste;

liste vide(){
	return NULL;
}

int isEmpty(liste ldc){
	return(NULL==ldc);
}

int len(liste ldc){
	int l=0;
	while (!isEmpty(ldc)){
		l++;
		ldc=ldc->next;
	}
	return l;
}

int addIndice(carte c, int indice, liste* pldc){
	liste cursor=*pldc;
	if (isEmpty(cursor) && indice!=0 && indice!=-1){return 0;}
	if (indice==-1){while (NULL!=cursor->next){cursor=cursor->next;}}
	if (indice!=0 && indice!=-1){
		for (int i=0; i<indice-1; i++){
			if (NULL==cursor->next){return 0;}
			cursor=cursor->next;
		}
	}
	liste newMaillon=malloc(sizeof(struct maillon));
	newMaillon->head=c;
	if (indice==0){
		newMaillon->next=cursor;
		newMaillon->prev=NULL;
		if (cursor!=NULL){cursor->prev=newMaillon;}
		*pldc=newMaillon;
	}
	else {
		newMaillon->next=cursor->next;
		newMaillon->prev=cursor;
		if (cursor->next!=NULL){cursor->next->prev=newMaillon;}
		cursor->next=newMaillon;
	}
	return 1;
}
void addHead(carte c, liste* pldc){addIndice(c, 0, pldc);}
void addTail(carte c, liste* pldc){addIndice(c, -1, pldc);}

carte getIndice(int indice, liste* pldc){
	if (isEmpty(*pldc)){return NULL;}
	liste cursor=*pldc;
	if (indice==-1){while (NULL!=cursor->next){cursor=cursor->next;}}
	if (indice!=0 && indice!=-1){
		for (int i=0; i<indice-1; i++){
			if (NULL==cursor->next){return NULL;}
			cursor=cursor->next;
		}
	}	
	carte c=cursor->head;
	cursor->head=NULL;
	if (indice==0){
		*pldc=cursor->next;
		if (NULL!=(*pldc)){(*pldc)->prev=NULL;}
	}
	else{
		cursor->prev->next=cursor->next;
		if (cursor->next!=NULL){cursor->next->prev=cursor->prev;}
	}
	free(cursor);
	return c;
}
carte getHead(liste* pldc){return getIndice(0, pldc);}
carte getTail(liste* pldc){return getIndice(-1, pldc);}

int setIndice(carte c, int indice, liste* pldc){
	if (isEmpty(*pldc)){return 0;}
	liste cursor=*pldc;
	if (-1==indice){while (NULL!=cursor->next){cursor=cursor->next;}}
	else {
		for (int i=0; i<indice; i++){
			if (NULL==cursor->next){return 0;}
			cursor=cursor->next;
		}
	}
	cursor->head=c;
	return 1;
}
int setHead(carte c, liste* pldc){return setIndice(c, 0, pldc);}
int setTail(carte c, liste* pldc){return setIndice(c, -1, pldc);}

carte seeIndice(int indice, liste ldc){
	if (isEmpty(ldc)){return NULL;}
	if (-1==indice){while (NULL!=ldc->next){ldc=ldc->next;}}
	else {
		for (int i=0; i<indice; i++){
			if (NULL==ldc->next){return NULL;}
			ldc=ldc->next;
		}
	}
	return ldc->head;
}
carte seeHead(liste ldc){return seeIndice(0, ldc);}
carte seeTail(liste ldc){return seeIndice(-1, ldc);}

void destruction(liste* pldc){while (!isEmpty(*pldc)){freeCarte(getHead(pldc));}}

void reverse(liste* pldc){
	if (!isEmpty(*pldc)){
		liste cursor=*pldc;
		liste tmp;
		while (cursor->next!=NULL){
			tmp=cursor->next;
			cursor->next=cursor->prev;
			cursor->prev=tmp;
			cursor=cursor->prev;
		}
		cursor->next=cursor->prev;
		cursor->prev=NULL;
		*pldc=cursor;
	}
}

carte getLastInstanceOf(liste* pldc, carte_type t){
	if (isEmpty(*pldc)) {return NULL;}
	int i=0;
	reverse(pldc);
	carte tmp=seeIndice(i, *pldc);
	while(!isInstanceOf(tmp, t) && NULL!=tmp){
		i++;
		tmp=seeIndice(i, *pldc);
	}
	if(NULL==tmp){return NULL;}
	tmp=getIndice(i, pldc);
	reverse(pldc);
	return tmp;
}

liste merge(liste* pldc1, liste* pldc2){
	liste ldcm=vide();
	while (!isEmpty(*pldc1) && !isEmpty(*pldc2)){
		addTail(getHead(pldc1), &ldcm);
		addTail(getHead(pldc2), &ldcm);
	}
	if (!isEmpty(*pldc1)){
		reverse(&ldcm);
		ldcm->prev=*pldc1;
		(*pldc1)->prev=ldcm;
		reverse(&ldcm);
	}
	if(!isEmpty(*pldc2)){
		reverse(&ldcm);
		ldcm->prev=*pldc2;
		(*pldc2)->prev=ldcm;
		reverse(&ldcm);
	}
	return ldcm;
}

void mergeIn(liste* pldc1, liste* pldc2){*pldc1=merge(pldc1, pldc2);}

void shuffle(liste* pldc){
	int l=len(*pldc);
	liste nldc=vide()
	for (int i=0; i<l, i++){addHead(getIndice(rand()%(l-i), pldc), &nldc);}
	*pldc=nldc;
}

void shuffledMerge(liste* pldc1, liste* pldc2){
	mergeIn(pldc1, pldc2);
	shuffle(pldc1);
}

int pop(liste* pldc, int i){
	carte c=getIndice(i, pldc);
	if (NULL!=c){
		freeCarte(c);
		return 1;
	}
	return 0;
}

int removeEqual(liste* pldc, carte c){
	if (isEmpty(*pldc)){return 0;}
	liste cursor=*pldc;
	int indice=0;
	while (NULL!=cursor->next && cursor->head!=c){
		cursor=cursor->next;
		indice++;
	}
	if (NULL==cursor->next && cursor->head!=c){return 0;}
	freeCarte(cursor->head);
	if (indice==0){
		*pldc=cursor->next;
		if (NULL!=(*pldc)){(*pldc)->prev=NULL;}
	}
	else{
		cursor->prev->next=cursor->next;
		if (cursor->next!=NULL){cursor->next->prev=cursor->prev;}
	}
	free(cursor);
	return 1;
}

int removeInstance(liste* pldc, carte_type t){
	if (isEmpty(*pldc)){return 0;}
	liste cursor=*pldc;
	int indice=0;
	while (NULL!=cursor->next && !isInstanceOf(cursor->head, t)){
		cursor=cursor->next;
		indice++;
	}
	if (NULL==cursor->next && !isInstanceOf(cursor->head, t)){return 0;}
	freeCarte(cursor->head);
	if (indice==0){
		*pldc=cursor->next;
		if (NULL!=(*pldc)){(*pldc)->prev=NULL;}
	}
	else{
		cursor->prev->next=cursor->next;
		if (cursor->next!=NULL){cursor->next->prev=cursor->prev;}
	}
	free(cursor);
	return 1;
}


/*
void affiche(liste ldc){
	printf("Top <-> ");
	while (!isEmpty(ldc)){
		printf("[%i] <-> ", *ldc->head);
		ldc=ldc->next;
	}
	printf("Bottom\n");
}

int main(){
	printf("Vrai = %i et faux = %i\n", 1==1, 1==0);
	
	liste ldc=vide();
	printf("Liste vide, la fonction is_empty renvoie :%i\n",isEmpty(ldc));
	int i0=0;
	int i1=1;
	int i2=2;
	int i3=3;
	printf("Add 0 0 : %i\n", addIndice(&i0, 0, &ldc));
	affiche(ldc);
	printf("Add 1 1 : %i\n", addIndice(&i1, 1, &ldc));
	affiche(ldc);
	printf("Add 2 2 : %i\n", addIndice(&i2, 2, &ldc));
	affiche(ldc);
	printf("Add 3 3 : %i\n", addIndice(&i3, 3, &ldc));
	affiche(ldc);
	printf("AddHead 2 : %i\n", addIndice(&i2, 0, &ldc));
	affiche(ldc);
	reverse(&ldc);
	affiche(ldc);
	destruction(&ldc);
	printf("Fin destruction %i\n", isEmpty(ldc));
	affiche(ldc);
	printf("Add 0 0 : %i\n", addIndice(&i0, 0, &ldc));
	affiche(ldc);
	printf("Add 1 1 : %i\n", addIndice(&i1, 1, &ldc));
	affiche(ldc);
	printf("Add 2 2 : %i\n", addIndice(&i2, 2, &ldc));
	affiche(ldc);
	printf("Add 3 3 : %i\n", addIndice(&i3, 3, &ldc));
	affiche(ldc);
	printf("AddHead 2 : %i\n", addIndice(&i2, 0, &ldc));
	affiche(ldc);
	printf("getHead : %i\n", *getIndice(0, &ldc));
	affiche(ldc);
	printf("getHead : %i\n", *getIndice(0, &ldc));
	affiche(ldc);
	printf("getHead : %i\n", *getIndice(0, &ldc));
	affiche(ldc);
	printf("getHead : %i\n", *getIndice(0, &ldc));
	affiche(ldc);
	printf("getHead : %i\n", *getIndice(0, &ldc));
	affiche(ldc);
	return 0;
}*/
