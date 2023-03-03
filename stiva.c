/* OLARU Gabriel-312CB */

/*-- functiiStiva-V.c -- elementele stivei sunt memorate intr-o lista generica simplu inlantuita --*/
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "lista.h"
#include "stiva.h"
#include "coada.h"

/* creeaza stiva vida cu elemente de dimensiune d; */
void *InitS(size_t d)      
{ 
	ASt s = (ASt)malloc(sizeof (TStiva));			/* adresa descriptor alocat */
   	if (!s) 
		return NULL;
  	s->dime = d;
  	/* actualizeaza adrese din descriptor */
  	s->vf = NULL;  
   	return (void *)s;
}
int AdaugaSezonS(void *s, char *numeS, TCoada *c, int index)	
{
	TLG p;
	p = VF(s);
	TCoada *cs;
	for(; p != NULL;  p = p->urm)
		if( strcmp( ((TSerial*)(p->info))->numes,numeS) == 0)
		{
			cs = ((TSerial*)(p->info))->sezoane;
			TSezon  * sz = malloc(sizeof(TSezon));
			if (sz == NULL) return 1;
			sz->nr_ep = index;
			sz->TEp = (TCoada*)c;
					cs = ((TSerial*)(p->info))->sezoane;
					if(InsCoadaSz(cs, sz) == 0) return 1;
					return 0;
		}
	return 1; //nu s-a gasit
}


//actualizeaza in stiva currently_watching durata vizionata + d
//data este mai mare ca durata serialului muta in stiva history
int AddDS(void *s, char *numeS, int d, TStiva *sh)	//intoarce nr. de minute vizionate
{
	TLG p, ant, q;
	p = VF(s);
	TSerial * sr;
	int d_viz = 0, d_serial = 0;
	for(ant = NULL; p != NULL; ant = p, p = p->urm)
		if( strcmp( ((TSerial*)(p->info))->numes, numeS) == 0)
		{
			((TSerial*)(p->info))->vizionat += d;
			d_viz = ((TSerial*)(p->info))->vizionat;
			d_serial = DurataSerial(((TSerial*)(p->info))->sezoane);

			if (d_serial <= d_viz) //muta in stiva history
				{
				sr = (TSerial*)(p->info);
				if(Push(sh, sr) == 0) //in history
					return -1;

				if(ant == NULL) //stiva are 1 element
					VF(s) = p->urm;
				else
					ant->urm = p->urm;
				return 1;
				}
			else
				{
					if(ant == NULL) return 0;
					if(p->urm == NULL)
						{
							q = VF(s);
							p->urm = q;
							VF(s) = p;
							ant->urm = NULL;
						}
					else 
						{
							q = VF(s);
							ant->urm = p->urm;
							p->urm = q;
							VF(s) = p;
						}
				}
		}
	return 0; //nu s-a gasit
}
//cauta in stiva numeS
int GasitS(void *s, char *numeS)
{
	TLG p;
	p = VF(s);
	if(VF(s) == NULL) return 0;
	for(; p != NULL; p = p->urm)
		if( strcmp( ((TSerial*)(p->info))->numes, numeS) == 0)
			return 1; //s-a gasit
	return 0; //nu s-a gasit
}

/* pune element in varful stivei */
int Push(void *s, void *ae)     
{ 
	TLG aux;
    aux = (TLG)malloc(sizeof(TCelulaG));
	if(!aux)
        return 0;
	aux->info = ae;
	if( ( (ASt)s )->vf == NULL) 
	{
		( (ASt)s)->vf = aux;
		return 1;
	}
    aux->urm = ( (ASt)s )->vf;
    ( (ASt)s)->vf = aux;
    return 1;
}

/* extrage elementul din varful stivei la adresa ae */
int Pop(void *s, void *ae)      
{ 
	TLG aux = VF(s);
    if(aux == NULL) 
        return 0;
    memcpy(ae, aux->info, DIMES(s));
    VF(s) = aux->urm;
    free(aux);
    return 1;
}

/* test stiva vida */
int VidaS(void *a)               
{ 
	return VF(a) == NULL; 
}

/* transforma stiva in stiva vida */
void ResetS(void *a)          
{ 
	Distruge(&VF(a), free);
	VF(a) = NULL; /*  = NULL */
}

/* elibereaza intregul spatiu ocupat de stiva */
void DistrS(void **aa)           
{ 
	ResetS(*aa);		/* elibereaza spatiul  */
	free(*aa); 			/* elibereaza spatiul alocat pentru descriptor */
  	*aa = NULL;         
}

/* prelucreaza de la Varf spre Baza */
size_t Prel_V_B(void *a, TF1 f)  
{ 
	size_t k = 0;                    /* contor elemente pentru care f != 0 */
  	TLG  p;
  	for(p = VF(a); p != NULL; p = p->urm )  /* incepand de la varf */
    	if(f(p->info)) 	k++;                  /* aplica functia f si, eventual, creste contor */
  	return k;
}

