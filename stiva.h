/* OLARU Gabriel-312CB */

/*-- TStiva.h --- tipul stiva ---*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>
#include "coada.h"


#ifndef STIVA
#define STIVA

/*- macrodefinitii - acces campuri */
#define DIMES(a) (((ASt)(a))->dime)
#define VF(a) 	(((ASt)(a))->vf)

/* functii stiva */
int GasitS(void *s, char *numeS);
void* InitS(size_t d);    /* initializeaza stiva cu elem.de dimensiune d;
				  					anumite implementari pot necesita si alti parametri */
int Push(void* a, void* ae);  /* pune element in varful stivei */
int Pop (void* a, void* ae);  /* extrage elementul din varful stivei la adresa ae */
/*- prelucrarea tuturor elementelor din stiva; 
    -> numar elemente pentru care f != 0 -*/
size_t Prel_V_B(void* a, TF1 f); /* prelucreaza de la Varf spre Baza */
size_t Prel_B_V(void* a, TF1 f); /* prelucreaza de la Baza spre Varf */
int AddDS(void *s, char *numeS, int d, TStiva *h);
int AdaugaSezonS(void *s, char *numeS, TCoada *c, int index);
void DistrS(void **aa);
void ResetS(void *a);

/*- teste -*/
/* verifica daca doua stive au elemente de dimensiuni diferite */
#define DIMDIFS(s, d)	(DIMES(s) != DIMES(d))
/* verifica daca o stiva este vida */
#define VIDAS(a)  	(VF(a) == NULL)


#endif
