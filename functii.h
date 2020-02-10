/*Musat Mihai-Robert-313CB*/

#include <stdio.h>
#include "info.h"

void initLC(TLista *l);
void addLC(TLista *l, TLista p, void *inf, int s);
void addLCjuc(TLista *l, TLista p, Jucator j);
void allocLCjuc(TLista *l, TLista p, char *nume, int nrMaini);
void deleteLC(TLista *l, TLista p);
void deleteLCjuc(TLista *l, char *nume);
void decLC(TLista *l);
void turaLC(TLista *l);
int deleteLCf(TLista *l, int (*f)(void *));
int neg(void *juc);
int deleteNegLC(TLista *l);
void dezalocLC(TLista *l);
void dezalocM(Masa *m);
void initLS(TLista *l);
void addLS(TLista *l, TLista p, void *inf, int size);
void deleteLS(TLista *l, TLista p);
void dezalocLS(TLista *l);
void deleteLSm(TLista *l, char *numeMasa);
void deleteNull(TLista *l);
void addOrdLC(TLista *l, char *nume, int maini, int (*comp)(char *, int, char *, int));
int comp(char *s1, int a, char *s2, int b);
void ordLC(TLista lista, char *numeMasa, FILE *output);
void initM(Masa *m, char *nume, int nrCrt, int nrMax);
void addMjuc(Masa *m, char *nume, int nrMaini);
void deleteMasaJucator(struct masa **m, char *nume);
void printMasa(Masa m, FILE *output);
void initS(Sala *s, int mese, int nrCrt, int nrMax);
void addSalaMasa(Sala *s, Masa m);
void printSala(Sala s, FILE *output);
void noroc(Sala *s, char *numeM, char *numeJ, int n, FILE *out);
void turaS(Sala *s, char *nume, FILE *out);
void turaToataSala(Sala *s);
void clasamentSala(Sala *s, char *nume, FILE *out);
int nrLibereS(Sala *s, char *nume);
int sizeLC(TLista l);
void distribuie(Sala *s, TLista l);
Masa cautaM(Sala *s, char *nume);
void copyLC(TLista *l1, TLista *l2);
void dezalocS(Sala *s);


































