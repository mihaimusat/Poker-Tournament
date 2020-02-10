/*Musat Mihai-Robert-313CB*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "info.h"

//initializeaza o lista circulara simplu inlantuita 
void initLC(TLista *l) {
	*l = (TLista)(malloc(sizeof(struct celulag)));
	(*l) -> urm = *l;
}

//adauga in lista circulara l dupa pointerul p (daca p este null se insereaza la inceput)
void addLC(TLista *l, TLista p, void *inf, int s) {
	TLista nou = malloc(sizeof(struct celulag));
	nou -> info = malloc(s);
	memcpy(nou -> info, inf, s);
	if(p == *l) {
		TLista x = (*l) -> urm;
		nou -> urm = x;
		(*l) -> urm = nou;
	} else {
		TLista x = p -> urm;
		nou -> urm = x;
		p -> urm = nou;
	}
}

//adauga un jucator j in lista circulara l dupa pointerul p
void addLCjuc(TLista *l, TLista p, Jucator j) {
	addLC(l, p, j, sizeof(struct jucator));
}

//aloca structura unui jucator, il adauga la lista conform functiei anterioare si la sfarsit il elibereaza 
void allocLCjuc(TLista *l, TLista p, char *nume, int nrMaini) {
	Jucator j = malloc(sizeof(struct jucator));
	j -> nume = strdup(nume);
	j -> nrMaini = nrMaini;
	addLCjuc(l, p, j);
	free(j);
}

//sterge din lista circulara l ce se afla dupa pointerul p
void deleteLC(TLista *l, TLista p) {
	if(*l == NULL) {
		return;
	}
	if((*l) -> urm == *l) {
		return;
	}
	if(*l == p) {
		TLista x = (*l) -> urm;
		(*l) -> urm = x -> urm;
		Jucator j = (Jucator)(x -> info);
		free(j -> nume);
		free(j);
		free(x);
	} else {
		TLista x = p -> urm;
		p -> urm = x -> urm;
		Jucator j = (Jucator)(x -> info);
		free(j -> nume);
		free(j);
		free(x);
	}
}

//sterge din lista circulara jucatorul cu numele nume
void deleteLCjuc(TLista *l, char *nume) {
	if(*l == NULL) {
		return;
	}
	if((*l) == (*l) -> urm) {
		return;
	}
	TLista pre = *l;
	TLista x = (*l) -> urm;
	while(x != *l) {
		if(!strcmp(nume, ((Jucator)(x -> info)) ->nume)) {
			deleteLC(l, pre);
			break;
		}
		x = x -> urm;
		pre = pre -> urm;
	}
}

//decrementeaza toate elementele listei circulare 
void decLC(TLista *l) {
        TLista x = (*l) -> urm;
        while(x != *l) {
                ((Jucator)(x -> info)) -> nrMaini--;
                x = x -> urm;
        }
}

//invarte lista generica in sensul acelor de ceasornic si decrementeaza toate elementele listei 
void turaLC(TLista *l) {
	if(*l == NULL) {
		return;
	}
	if((*l) -> urm == *l) {
		return;
	}
	if(*l == (*l) -> urm -> urm) {
		decLC(l);
		return;
	}
	TLista x = (*l) -> urm;
	(*l) -> urm = x -> urm;
	x -> urm = NULL;
	TLista y = *l;
	while(y -> urm != *l) {
		y = y -> urm;
	}
	x -> urm = *l;
	y -> urm = x;
	decLC(l);
}

//sterge din lista circulara elementele pentru care functia f intoarce 1
int deleteLCf(TLista *l, int (*f)(void *)) {
	if(*l == NULL) {
		return 0;
	}
	if((*l) == (*l) -> urm) {
		return 0;
	}
	int nr = 0;
	TLista pre = *l;
	TLista curr = (*l) -> urm;
	while(curr != *l) {
		if(f(curr -> info) == 1) {
			nr++;
			deleteLC(l, pre);
			curr = pre -> urm;
		} else {
			pre = pre -> urm;
			curr = curr -> urm;
		}
	}
	return nr;
}

//functie care verifica daca numarul de maini al unui jucator este negativ
int neg(void *juc) {
	if(((Jucator) juc) -> nrMaini <= 0) {
		return 1;
	}
	return 0;
}

//sterge elementele negative dintr-o lista circulara folosind deleteLCf
int deleteNegLC(TLista *l) {
	return deleteLCf(l, neg);
}

//dezaloca o lista circulara
void dezalocLC(TLista *l) {
	while(*l != (*l) -> urm) {
		deleteLC(l, *l);
	}
	free((*l));
}

//dezaloca o masa
void dezalocM(Masa *m) {
	TLista l = (TLista)((*m) -> jucatori);
	dezalocLC(&l);
	free((*m) -> numeMasa);
	free(*m);
}

//initializare lista simplu inlantuita 
void initLS(TLista *l) {
	*l = NULL;
}

//adaugare element nou intr-o lista simplu inlantuita 
void addLS(TLista *l, TLista p, void *inf, int size) {
	TLista nou = malloc(sizeof(struct celulag));
	nou -> info = malloc(size);
	memcpy(nou -> info, inf, size);
	nou -> urm = NULL;
	if(*l == NULL) {
		*l = nou;
		return;
	} else {
		if(p == NULL) {
			nou -> urm = *l;
			*l = nou;
			return;
		} else {
			TLista x = p -> urm;
			nou -> urm = x;
			p -> urm = nou;
		}
	}
}

//stergerea elementelor din lista simplu inlantuita dupa pointerul p 
void deleteLS(TLista *l, TLista p) {
	if(*l == NULL) {
		return;
	}
	if(p == NULL) {
		TLista x = *l;
		*l = (*l) -> urm;
		x -> urm = NULL;
		Masa m = (Masa)(x -> info);
		dezalocM(&m);
		free(x);
	} else {
		if(p -> urm == NULL) {
			return;
		}
 		TLista x = p -> urm;
		p -> urm = x -> urm;
		x -> urm = NULL;
		Masa m = (Masa)(x -> info);
		dezalocM(&m);
		free(x);
	}
}

//dezaloca lista simplu inlantuita 
void dezalocLS(TLista *l) {
	while(*l != NULL) {
		deleteLS(l, NULL);
	}
}

//sterge din lista simplu inlantuita l masa cu numele numeMasa
void deleteLSm(TLista *l, char *numeMasa) {
	TLista x = *l;
	TLista y = NULL;
	while(x != NULL) {
		if(!strcmp(((Masa)(x -> info)) -> numeMasa, numeMasa)) {
			deleteLS(l, y);
			break;
		}
		x = x -> urm;
		if(y == NULL) {
			y = *l;
		} else {
			y = y -> urm;
		}
	}
}

//sterge din lista simplu inlantuita l toate elementele care nu mai contin informatie in campul info
void deleteNull(TLista *l) {
        if(*l == NULL) {
                return;
        }
        TLista pre = NULL;
        TLista nod = *l;
        while(nod != NULL) {
                Masa m = (Masa)(nod -> info);
                TLista juc = m -> jucatori;
                if(juc == NULL || juc == juc -> urm) {
                        deleteLS(l, pre);
                        if(pre == NULL) {
                                nod = *l;
                        } else {
                                nod = pre -> urm;
                        }
                } else {
                        if(pre == NULL) {
                                pre = *l;
                        } else {
                                pre = pre -> urm;
                        }
                        nod = nod -> urm;

                }
        }
}

//adauga ordonat intr-o lista circulara un jucator folosind o functie de comparare
void addOrdLC(TLista *l, char *nume, int maini, int (*comp)(char *, int, char *, int)) {
	TLista pre = *l;
	TLista curr = (*l) -> urm;
	if((*l) == (*l) -> urm) {
		allocLCjuc(l, pre, nume, maini);
		return;
	}
	while(curr != *l) {
		Jucator j1 = (Jucator)(curr -> info);
		if(comp(nume, maini, j1 -> nume, j1 -> nrMaini) == -1) {
			curr = curr -> urm;
			pre = pre -> urm;
		} else {
			allocLCjuc(l, pre, nume,  maini);
			break;
		}
	}
	if(curr == *l) {
		allocLCjuc(l, pre, nume, maini);
	}
}

//functie de comparare
int comp(char *s1, int a, char *s2, int b) {
	if(a < b) {
		return -1;
	}
	if(a > b) {
		return 1;
	}
	if(strcmp(s2, s1) < 0) {
		return 1;
	}
	return -1;
}

//ordoneaza o lista circulara l 
void ordLC(TLista lista, char *numeMasa, FILE *output) {
	TLista copy;
	initLC(&copy);
	TLista nod = lista -> urm;
	while(nod != lista) {
		Jucator j = (Jucator)(nod -> info);
		addOrdLC(&copy, j -> nume, j -> nrMaini, comp);
		nod = nod -> urm;
	}
	fprintf(output, "Clasament %s:\n", numeMasa);
	TLista l1 = copy -> urm;
	while(l1 != copy) {
		Jucator j = (Jucator)(l1 -> info);
		fprintf(output, "%s %d\n", j -> nume, j -> nrMaini);
		l1 = l1 -> urm;
	}
	dezalocLC(&copy);
}

//initializare masa
void initM(Masa *m, char *nume, int nrCrt, int nrMax) {
	*m = malloc(sizeof(struct masa));
	(*m) -> numeMasa = strdup(nume);
	(*m) -> nrMaxJucatori = nrMax;
	(*m) -> nrCrtJucatori = nrCrt;
	initLC(&((*m) -> jucatori));
}

//adauga un jucator la o masa
void addMjuc(Masa *m, char *nume, int nrMaini) {
	(*m) -> nrCrtJucatori++;
	int x = (*m) -> nrCrtJucatori;
	if(x > (*m) -> nrMaxJucatori) {
		return;
	}
	TLista juc = (*m) -> jucatori;
	TLista jucc = juc;
	TLista juc1 = juc -> urm;
	while(juc1 != juc) {
		juc1 = juc1 -> urm;
		jucc = jucc -> urm;
	}
	allocLCjuc(&juc, jucc, nume, nrMaini);
}

//sterge un jucator de la masa
void deleteMasaJucator(struct masa **m, char *nume) {
	(*m) -> nrCrtJucatori--;
	deleteLCjuc(&((*m) -> jucatori), nume);
}

//afiseaza situatia curenta a unei mese 
void printMasa(Masa m, FILE *output) {
	int s = m -> nrCrtJucatori;
	int t = 0;
	TLista x = m -> jucatori -> urm;
	fprintf(output, "%s:", m -> numeMasa);
	while(x != m -> jucatori) {
		t++;
		Jucator j = (Jucator)(x -> info);
		fprintf(output, " %s - %d", j -> nume, j -> nrMaini);
		if(t != s) {
			fprintf(output, ";");
		} else {
			fprintf(output, ".");
		}
		x = x -> urm;
	}
	fprintf(output, "\n");
}

//initializare sala
void initS(Sala *s, int mese, int nrCrt, int nrMax) {
	(*s) = malloc(sizeof(struct sala));
	(*s) -> nrMese = mese;
	(*s) -> nrLocCrt = nrCrt;
	(*s) -> nrLocMax = nrMax;
	initLS(&((*s) -> masa));
}

//adauga masa m la sala s
void addSalaMasa(Sala *s, Masa m) {
	(*s) -> nrMese++;
	TLista x = (*s) -> masa;
	TLista y = NULL;
	while(x != NULL) {
		x = x -> urm;
		if(y == NULL) {
			y = (*s) -> masa;
		} else {
			y = y -> urm;
		}
	}
	int size = sizeof(struct masa);
	addLS(&((*s) -> masa), y, m, size);
}

//functia print descrisa in enunt  
void printSala(Sala s, FILE *output) {
	if(s -> masa == NULL) {
		fprintf(output, "Sala este inchisa!\n");
	} else {
		TLista x = s -> masa;
		while(x != NULL) {
			Masa m = (Masa)(x -> info);
			printMasa(m, output);
			x = x -> urm;
		}
	}
}

//functia noroc descrisa in enunt
void noroc(Sala *s, char *numeM, char *numeJ, int n, FILE *out) {
	TLista masaC = (*s) -> masa;
	while(masaC != NULL && strcmp(((Masa)(masaC -> info)) -> numeMasa, numeM)) {
		masaC = masaC -> urm;
	}
	if(masaC == NULL) {
		fprintf(out, "Masa %s nu exista!\n", numeM);
		return;
	}
	Masa m = ((Masa)(masaC -> info));
	TLista juc = m -> jucatori -> urm;
	while(juc != m -> jucatori && strcmp(((Jucator)(juc -> info)) ->nume, numeJ)) {
		juc = juc -> urm;
	}
	if(juc == m -> jucatori) {
		fprintf(out, "Jucatorul %s nu exista la masa %s!", numeJ, numeM);
		fprintf(out, "\n");
		return;
	}
	Jucator j = (Jucator)(juc -> info);
	j -> nrMaini += n;
	if(j -> nrMaini <= 0) {
		m -> nrCrtJucatori--;
		deleteLCjuc(&(m -> jucatori), j -> nume);
	}
	if(m -> nrCrtJucatori == 0) {
		deleteNull(&((*s) -> masa));
	}
}

//functia tura descrisa in enunt
void turaS(Sala *s, char *nume, FILE *out) {
	TLista masaC = (*s) -> masa;
        while(masaC != NULL && strcmp(((Masa)(masaC -> info)) -> numeMasa, nume)) {
                masaC = masaC -> urm;
        }
        if(masaC == NULL) {
                fprintf(out, "Masa %s nu exista!\n", nume);
                return;
        }
        Masa m = ((Masa)(masaC -> info));
	turaLC(&(m -> jucatori));
	int x = deleteNegLC(&(m -> jucatori));
	m -> nrCrtJucatori -= x;
}

//functia tura_completa descrisa in enunt
void turaToataSala(Sala *s) {
	 TLista masaC = (*s) -> masa;
	 while(masaC != NULL) {
		Masa m = (Masa)(masaC -> info);
		turaLC(&(m -> jucatori));
		int x = deleteNegLC(&(m -> jucatori));
		m -> nrCrtJucatori -= x;
		masaC = masaC -> urm;
	}
}

//functia clasament descrisa in enunt 
void clasamentSala(Sala *s, char *nume, FILE *out) {
	TLista masaC = (*s) -> masa;
        while(masaC != NULL && strcmp(((Masa)(masaC -> info)) -> numeMasa, nume)) {
                masaC = masaC -> urm;
        }
        if(masaC == NULL) {
                fprintf(out, "Masa %s nu exista!\n", nume);
                return;
        }
        Masa m = ((Masa)(masaC -> info));
	ordLC(m -> jucatori, m -> numeMasa, out);
}

//numara cate locuri libere mai sunt in sala
int nrLibereS(Sala *s, char *nume) {
	TLista masaC = (*s) -> masa;
	int nr = 0;
        while(masaC != NULL) {
                Masa m = (Masa)(masaC -> info);
                int x = m -> nrMaxJucatori - m -> nrCrtJucatori;
		if(strcmp(m -> numeMasa, nume)) {
			nr += x;
		}
                masaC = masaC -> urm;
        }
	return nr;
}

//afla dimensiunea unei liste circulare
int sizeLC(TLista l) {
	int nr = 0;
	TLista x = l -> urm;
	while(x != l) {
		nr++;
		x = x -> urm;
	}
	return nr;
}

//distribuie elemtentele din lista circulara l in sala S
void distribuie(Sala *s, TLista l) {
	int sizelista = sizeLC(l);
	TLista masaC = (*s) -> masa;
	TLista curr = l -> urm;
        while(masaC != NULL) {
		if(sizelista <= 0) {
			break;
		}
                Masa m = (Masa)(masaC -> info);
                while(m -> nrCrtJucatori < m -> nrMaxJucatori && sizelista > 0) {
			sizelista--;
			Jucator j = (Jucator)(curr -> info);
			addMjuc(&m, j -> nume, j -> nrMaini);
			curr = curr -> urm;
		}
                masaC = masaC -> urm;
        }
}

//cauta masa in sala dupa nume
Masa cautaM(Sala *s, char *nume) {
	TLista masaC = (*s) -> masa;
        while(masaC != NULL) {
                Masa m = (Masa)(masaC -> info);
                if(!strcmp(m -> numeMasa, nume)) {
			return m;
		}
                masaC = masaC -> urm;
        }
	return NULL;
}

//copiaza o lista circulara
void copyLC(TLista *l1, TLista *l2) {
	initLC(l1);
	TLista final = *l1;
	TLista nod = (*l2) -> urm;
	while(nod != *l2) {
		Jucator j = (Jucator)(nod -> info);
		allocLCjuc(l1, final,j -> nume, j -> nrMaini);
		final = final -> urm;
		nod = nod -> urm;
	}
}

//dezaloca sala
void dezalocS(Sala *s) {
	TLista mese = (*s) -> masa;
	dezalocLS(&mese);
	free(*s);
}

