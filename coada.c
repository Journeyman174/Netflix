/* OLARU Gabriel-312CB */

/*-- functiiCoada-V.c -- elementele cozii sunt memorate intr-un vector --*/
//#include "TCoada-V.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "lista.h"
#include "coada.h"

void DistrugeSezon(TCoada *cs)
{
	TLG p=IC(cs),u;
	TCoada * c;

	for(; p !=NULL; )
		{
			u=p->urm;
			c=(TCoada*)(((TSezon*)(p->info))->TEp);
			TLG  e = IC(c),v;
			for(; e != NULL;)
			{
				v = e->urm;
				free(e->info);
				free(e);
				e = v;
			}
			free(p->info);
			free(p);
			p = u;
		}
}

int DurataSerial(TCoada *cs)
{
	int durataS = 0;
	TLG p = IC(cs);
	TCoada * c;
	for(; p != NULL; p = p->urm)
		{
			c = (TCoada*)(((TSezon*)(p->info))->TEp);
			TLG e = IC(c);
			for(; e != NULL;e = e->urm)
			{
				durataS = durataS+*(int*)(e->info);
			}
		}
	return durataS;
}
/* creeaza coada vida cu elemente de dimensiune d;
   este necesar si un al doilea parametru = numar maxim elemente in coada */
void* InitQ(size_t d)
{ 
	AQ a = (AQ)malloc(sizeof(TCoada));  	/* adresa descriptor alocat */
  
  	if (!a)	return NULL;

	a->dime = d;
	a->ic = NULL;
	a->sc = NULL;

  	return (void*)a;  
}
/* adauga element la sfarsitul cozii watch_later*/
int InsCoadaWL(void *c, void * ae)
{ 
	TLG aux;


	aux = (TLG)malloc(sizeof(TCelulaG));
	if(!aux) return 0;
	
	aux->info = malloc(sizeof(TSerial));
	aux->info = ae;
	aux->urm = NULL;
	if(VIDA(c))
		{
			IC(c) = aux;
			SC(c) = aux;
		}
	else
		{
			SC(c)->urm = aux;
			SC(c) = aux;
		}
	return 1;
}

/* adauga element la sfarsitul cozii Episoade*/
int InsCoadaEp(void *c, void * ae)
{ 
	TLG aux;

	aux = (TLG)malloc(sizeof(TCelulaG));
	if(!aux) return 0;
	
	aux->info = malloc(sizeof(int));
	*(int *)(aux->info) = atoi((char*)ae);
	aux->urm = NULL;

	if(VIDA(c))
		{
			IC(c) = aux;
			SC(c) = aux;
		}
	else
		{
			SC(c)->urm = aux;
			SC(c) = aux;
		}
	return 1;
}

/* adauga element la sfarsitul cozii Sezoane*/
int InsCoadaSz(void *c, void *ae)
{ 
	TLG aux;
	aux = (TLG)malloc(sizeof(TCelulaG));
	if(!aux) return 0;

	aux->info = malloc(sizeof(TSezon));
	if(!aux->info) return 0;
	aux->info = ae;
	aux->urm = NULL;
	if(VIDA(c))
		{
			IC(c) = aux;
			SC(c) = aux;
		}
	else
		{
			SC(c)->urm = aux;
			SC(c) = aux;
		}
	
	return 1;
}

/* prelucreaza elementele, folosind functia f;
	rezultat = numarul de elemente pentru care f != 0 */
size_t PrelQ(void *a, TF1 f)   
{ 
	TLG p = IC(a);               /* adresa element prelucrat = inceputul cozii */
  	size_t k = 0;                  /* contor */
  	for(; p != NULL; p = p->urm)  /* pentru fiecare element, pana la ultimul */
	 	{
    	if( f(p->info) ) 
			k++;              	   /* daca f intoarce rezultat != 0 -> contorizeaza */
		 }
	return k;
}

//numara elementele din coada
size_t NrQ(void *a)   
{ 
	TLG p = IC(a);               /* adresa element prelucrat = inceputul cozii */
  	size_t k = 0;                 /* contor */
  	for(; p != NULL; p = p->urm)  /* pentru fiecare element, pana la ultimul */
		k++;              	   	 /*contorizeaza */
	return k;
}

/* test coada vida */
int VidaQ(void *a)         
{ 
	return VIDA(a); 
}
/* transforma coada in coada vida */
void ResetQ(void *a)       
{ 
//	Distruge(&IC(a),free);
	SC(a) = IC(a) = NULL; /* inceput si sfarsit coada = NULL */
}  
/* elibereaza intregul spatiu ocupat de coada */
void DistrQ(void **aa)     
{ 
	ResetQ(*aa);  	/* elibereaza spatiul ocupat de vector 			*/
  	free(*aa);		/* elibereaza spatiul alocat pentru descriptor 	*/
  	*aa = NULL;
}