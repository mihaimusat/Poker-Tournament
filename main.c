/*Musat Mihai-Robert-313CB*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "info.h"
#include "functii.h"

#define MAX_STRING 20 

int main(int argc, char *argv[]) {
	FILE *conf = fopen(argv[1], "r");
	FILE *operatii = fopen(argv[2], "r");
	FILE *output = fopen(argv[3], "w");
	Sala s1;
	initS(&s1, 100, 100, 100);

	int n;
	fscanf(conf, "%d", &n);
	int i, j;
	for(i = 0; i < n; i++) {
		int n1, dim1;
		char *numeMasa = malloc(MAX_STRING * sizeof(char));
		fscanf(conf, "%s", numeMasa);
		fscanf(conf, "%d", &n1);
		fscanf(conf, "%d", &dim1);
		Masa m;
		initM(&m, numeMasa, 0, dim1);
		free(numeMasa);
		for(j = 0; j < n1; j++) {
			int l;
			char *numeJucator = malloc(MAX_STRING * sizeof(char));
			fscanf(conf, "%s%d", numeJucator, &l);
			addMjuc(&m, numeJucator , l);
			free(numeJucator);
		}
		addSalaMasa(&s1, m);
		free(m);
	}
	char op[MAX_STRING];
	while(fscanf(operatii, "%s", op) != -1) {
		if(!strcmp(op, "print")) {
			printSala(s1, output);
		}
		if(!strcmp(op, "noroc")) {
			char *numeMasa = malloc(MAX_STRING * sizeof(char));
			char *numeJucator = malloc(MAX_STRING * sizeof(char));
			int noro;
			fscanf(operatii, "%s%s%d", numeMasa, numeJucator, &noro);
			noroc(&s1, numeMasa, numeJucator, noro, output);
			free(numeMasa);
			free(numeJucator);
		}
		if(!strcmp(op, "ghinion")) {
			char *numeMasa = malloc(MAX_STRING * sizeof(char));
            		char *numeJucator = malloc(MAX_STRING * sizeof(char));
            		int noro;
            		fscanf(operatii, "%s%s%d", numeMasa, numeJucator, &noro);
            		noroc(&s1, numeMasa, numeJucator, -noro, output);
			free(numeMasa);
			free(numeJucator);
		}
		if(!strcmp(op, "tura")) {
			char *numeMasa = malloc(MAX_STRING * sizeof(char));
			fscanf(operatii, "%s", numeMasa);
			turaS(&s1, numeMasa, output);
			deleteNull(&(s1 -> masa));
			free(numeMasa);
		}
		if(!strcmp(op, "tura_completa")) {
			turaToataSala(&s1);
			deleteNull(&(s1 -> masa));
		}
		if(!strcmp(op, "clasament")) {
			char *numeMasa = malloc(20 * sizeof(char));
			fscanf(operatii, "%s", numeMasa);
			clasamentSala(&s1, numeMasa, output);
			free(numeMasa);
		}
		if(!strcmp(op, "inchide")) {
			char *numeMasa = malloc(20 * sizeof(char));
			fscanf(operatii, "%s", numeMasa);
			Masa m = cautaM(&s1, numeMasa);
			if(m == NULL) {
				fprintf(output, "Masa %s nu exista!\n", numeMasa);
			} else {
				TLista copy;
				copyLC(&copy, &(m -> jucatori));
				int sizelista = sizeLC(copy);
				int loclib = nrLibereS(&s1, numeMasa);
				if(sizelista <= loclib) {
					deleteLSm(&(s1 -> masa), m -> numeMasa);
					distribuie(&s1, copy);
				} else {
					fprintf(output, "Nu exista suficiente locuri in sala!\n");
				}
				dezalocLC(&copy);
			}
			free(numeMasa);
		}		
	}
	dezalocS(&s1);
	fclose(operatii);
	fclose(conf);
	fclose(output);
	return 0;
}
