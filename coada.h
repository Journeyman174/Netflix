/* OLARU Gabriel-312CB */

/*-- coada.h -- elementele cozii sunt memorate lista simplu inlantuita --*/
#ifndef _COADA_LISTA_
#define _COADA_LISTA_
typedef int (*TF1)(void *); //la functia AfiQ
typedef int (*TF2)(const void *, const void *);
typedef int (*TF3)( char * ,const void *,const void *);

void* InitQ(size_t d); /* creeaza coada vida cu elemente de dimensiune d*/
int InsCoadaEp(void *c, void * ae);
int InsCoadaSz(void *c, void *ae);
int InsCoadaWL(void *c, void * ae);
int ExtrQ (void *a, void *ae);
int PrimQ(void *a, void *ae);
size_t PrelQ(void *a, TF1 f);
int VidaQ(void *a) ;
size_t NrQ(void *a) ;
void ResetQ(void* a);         /* transforma coada in coada vida */
void DistrQ(void** aa);       /* elibereaza intregul spatiu ocupat de coada */
int DurataSerial(TCoada *cs);
void DistrugeSezon(TCoada *cs);
					

/*- macrodefinitii - acces campuri -*/
#define IC(a) 	(((AQ)(a))->ic)
#define SC(a) 	(((AQ)(a))->sc)
#define DIME(a) (((AQ)(a))->dime)

/*- teste si prelucrari -*/
/* verifica daca o coada este vida 										*/
#define VIDA(a) 		(IC(a) == NULL && SC(a)==NULL)

#endif
