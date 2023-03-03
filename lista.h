/* OLARU Gabriel-312CB */

/*-- lista.h --- LISTA SIMPLU INLANTUITA GENERICA ---*/
#ifndef _LISTA_GENERICA_
#define _LISTA_GENERICA_

typedef struct celulag
{
  void* info;           /* adresa informatie */
  struct celulag *urm;   /* adresa urmatoarei celule */
} TCelulaG, *TLG; /* tipurile Celula, Lista  */

typedef struct coada
{
	size_t dime; 		// dim.element
	TLG ic, sc;		// adr.prima, ultima celula
}TCoada, *AQ;

typedef struct stiva
{
  size_t dime;
  TLG vf;
} TStiva, *ASt;

typedef struct serial
{
  int id;
  char * numes;
  float rating;
  int nr_sez;
  int vizionat;
  TCoada  *sezoane;
} TSerial;

typedef struct sez
{
  int nr_ep;
  TCoada *TEp;
} TSezon;



typedef int (*TFElem)(void*);     /* functie prelucrare element */
typedef int (*TFCmp)(void*, float, char*); /* functie de comparare doua elemente */
typedef void (*TF)(void*);     /* functie afisare/eliberare un element */

/* functii lista generica */
void AfisareSeriale(void * element);
int ordS(void * e1, float e2, char *e3); //stabileste conditiile de inserare in lista
int AdaugaSerial(TLG *L, int id, char *numeS, char *ratingS, char *nr_Sez, void *sez, TFCmp fcmp); /* adauga serial in lista generica*/
int AdaugaSerialTop(TLG *L, int id, char *numeS, char *ratingS, char *nr_Sez, void *sez);
int InsLG(TLG*, void*);  /*- inserare la inceput reusita sau nu (1/0) -*/
void Distruge(TLG* aL, TF fe); /* distruge lista */
size_t LungimeLG(TLG*);   /* numarul de elemente din lista */
int Pozitie(TLG* a, char *numes); //pozitia
/* afiseaza elementele din lista, folosind o functie de tip TFAfi */
void Afisare(TLG*, TF);
int InsSfLG(TLG* aL, void* ae);
int InsInainteLG(TLG* aL, void* ae, TLG* aA);

#endif
