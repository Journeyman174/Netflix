/* OLARU Gabriel-312CB */
/*--- functiiLG.c -- operatii de baza pentru lista simplu inlantuita generica---*/
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "lista.h"
#include "stiva.h"

//se foloseste la put ordonare dupa cheie in lista
int ordS(void * e1, float e2, char *e3)
{
	TSerial * ser = (TSerial *) e1;
	if ( ser->rating > e2) return 1;
	if ( ser->rating == e2)
		if (strcmp(ser->numes, e3) < 0)	return 1;
	return 0;
}

void AfisareSeriale(void * element)
{
	TSerial *serial = (TSerial*)element;
	printf("nume=%s,rating=%.1f", serial->numes, serial->rating);
}

int AdaugaSerialTop(TLG *L, int id, char *numeS, char *ratingS, char *nr_Sez, void *sez)
{
	int contor = 0;
	TLG p, u;
	TLG ant = NULL;
	TSerial *serial = malloc(sizeof(TSerial));
	if(serial == NULL) return 0;
	serial->numes = malloc(sizeof(char)*100);
	if(serial->numes == NULL) return 0;
	serial->id = id;
	serial->numes = strdup(numeS);
	serial->rating = atof(ratingS);
	serial->nr_sez = atoi(nr_Sez);
	serial->sezoane = (TCoada*)sez;
	if(*L == NULL)
	{
		InsLG(L, serial);
	}
	else
		{
			contor = 1;
			for( p = *L; p != NULL; ant = p, p = p->urm, contor++)
			{
					if(contor == serial->id)
					{
						if(ant == NULL)		//se insereaza la inceputul listei

							InsLG(L, serial);
						else
							InsInainteLG(&p, serial, &ant);
					break;
					}
			}
			if(p == NULL)
			{
				InsSfLG(&ant, serial);
			}	
		}
		contor = 0;
		
		for( p = *L; p != NULL; ant = p, p = p->urm, contor++)
		{
			if(contor == 9)
				{
					if(p->urm != NULL)
					{
					u = p->urm;
					DistrugeSezon(((TSerial*)(u->info))->sezoane);
					free(p->urm);
					p->urm = NULL;
					break;
					}
				}
		}
	return 1;
}


int InsLG(TLG* aL, void* ae)
{	
	TLG aux = malloc(sizeof(TCelulaG));
	if(!aux)
	    return 0; //esuare inserare in lista
	aux->info = ae;
	aux->urm = *aL;
	*aL = aux;
	return 1;	//inserare cu suscces
}


int AdaugaSerial(TLG *L, int id, char *numeS, char *ratingS, char *nr_Sez, void *sez, TFCmp fcmp)
{
	TLG p;
	TLG ant = NULL;
	TSerial *serial = malloc(sizeof(TSerial));
	if(serial == NULL) return 0;
	serial->numes = malloc(sizeof(char)*32);
	if(serial->numes == NULL) return 0;
	serial->id = id;
	serial->numes = strdup(numeS);
	serial->rating = atof(ratingS);
	serial->nr_sez = atoi(nr_Sez);
	serial->sezoane = (TCoada*)sez;

	if(*L == NULL)
	{
		InsLG(L, serial);
	}
	else
		{
			for(p = *L; p != NULL; ant = p, p = p->urm)
			{
					if(fcmp(p->info, serial->rating, serial->numes) == 0)
					{
						if(ant == NULL)		//se insereaza la inceputul listei
							InsLG(L, serial);
						else
						{
									InsInainteLG(&p, serial, &ant);
						}
						break;
					}
			}
			if(p == NULL)
			{
				InsSfLG(&ant, serial);
			}	
		}
	return 1;
}

int InsSfLG(TLG* aL, void* ae)
{	
	TLG aux = malloc(sizeof(TCelulaG));
	if(!aux)
	    return 0; //esuare inserare in lista
	aux->info = ae;
	aux->urm = NULL;
	(*aL)->urm = aux;
	return 1;	//inserare cu suscces
}

int InsInainteLG(TLG* aL, void* ae, TLG* aA)
{	
	TLG aux = malloc(sizeof(TCelulaG));
	if(!aux)
	    return 0; //esuare inserare in lista
	aux->info = ae;
	aux->urm = *aL;
	(*aA)->urm = aux;
	return 1;	//inserare cu suscces
}
void Distruge(TLG* aL, TF free_elem) /* distruge lista */
{
	while(*aL != NULL)
    {
        TLG aux = *aL;     /* adresa celulei eliminate */
        if (!aux)
            return;

        free_elem(aux->info);  /* elib.spatiul ocupat de element*/
        *aL = aux->urm;    /* deconecteaza celula din lista */
        free(aux);   /* elibereaza spatiul ocupat de celula */
    }
}

size_t LungimeLG(TLG* a)      /* numarul de elemente din lista */
{
	size_t lg = 0;
	TLG p = *a;
	for (; p != NULL; p = p->urm)
		{
        lg++;
		}
	return lg;
}

int Pozitie(TLG* a, char *numes)      /* numarul de elemente din lista */
{
	int poz = 1;
	TLG p = *a; //ant;
     /* parcurge lista, numarand celulele */
	if( p->urm == NULL) return poz;
	if (strcmp(((TSerial*)(p->info))->numes,numes) == 0   )  return poz;
	for (p = p->urm; p != NULL; p = p->urm)
		{
        	poz++;
			if (strcmp(((TSerial*)(p->info))->numes,numes) == 0   )  break;
		}
	return poz;
}

void Afisare(TLG* aL, TF afiEL)
{
	if(!*aL) 
	{
        printf("Afisare :Lista vida\n");
        return;
    }

	printf("[");
	for(; *aL ; aL = &(*aL)->urm)
	{
		afiEL((*aL)->info);
    }
	printf("]\n");
}

