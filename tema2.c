/* OLARU Gabriel-312CB */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include "lista.h"
#include "coada.h"
#include "stiva.h"

void AfiS(char antet[], TF1 AfiElem, void *a)
{
	/* afiseaza antet si apoi aplica functia de afisare AfiElem tuturor elementelor */
	printf ("%s", antet);          	/* afiseaza antetul */
  	if (VIDAS (a))
      printf ("Stiva vida!");
  	else
       Prel_V_B(a, AfiElem);        	/* afiseaza elementele in ordinea introducerii */
  	printf("\n");
}


void AfiQ(char antet[], TF1 AfiElem, void *a)
{
	/* afiseaza antet si apoi aplica functia de afisare AfiElem tuturor elementelor */
	printf ("%s", antet);          	/* afiseaza antetul */
  	if (VidaQ (a))
      printf ("Coada vida!");
  	else
	  PrelQ (a, AfiElem); 	/* afiseaza elementele in ordinea introducerii */
  	printf("\n");
}

int AfiEp(void * durata)
{
	int d;
	d = *(int*)durata;
	printf("[ %d ]", d);
	return 1;
}

int AfiSz(void * ae)
{
	int d;
	d = ((TSezon*)ae)->nr_ep;
	printf("Sz [ %d ]", d);
	return 1;
}

int AfiSr(void * ae)
{
	char * nume;
	float rating;
	nume = ((TSerial*)ae)->numes;
	rating = ((TSerial*)ae)->rating;
	printf("Serial [ %s,%.1f ]", nume, rating);
	return 1;
}

int MutaCW(TLG *L, char * numeS, TStiva *s, int durataw, TStiva *sh)
{
	TSerial * sr;
	TLG p;
	TLG ant;
	int duratas = 0;
	
	for( ant = NULL, p = *L; p != NULL   ; ant = p, p = p->urm)
		{
			if ( (strcmp(((TSerial*)(p->info))->numes, numeS) == 0)  ) //l=a gasit in coada
				{
					duratas = DurataSerial(((TSerial*)(p->info))->sezoane);
					if(duratas > durataw)
						{
						sr = (TSerial*)(p->info);
						sr->vizionat=durataw;

						if(Push(s,sr) == 0) return 1;
						if(ant == NULL)		//se insereaza la inceputul listei
							*L = p->urm;
						else
							ant->urm = p->urm;
							
						return 1; //mai are de vizionat
						}
					else
						{
						sr = (TSerial*)(p->info);
						sr->vizionat = durataw;

						if(Push(sh,sr) == 0) return 1;
						if(ant == NULL)		//se insereaza la inceput
							*L = p->urm;
						else
							ant->urm = p->urm;
							
						return 0;
						}
				}
		}
	return 1;
}

int MutaCWQ(TCoada *cs, char * numeS, TStiva *s, int durataw, TStiva *sh)
{
	TSerial * sr;
	TLG p = IC(cs);
	TLG ant ;
	int duratas = 0;
	for( ant = NULL; p != NULL ; ant = p, p = p->urm)
		{
			if (strcmp(((TSerial*)(p->info))->numes, numeS) == 0 ) //l-a gasit in coada

				{	
					duratas = DurataSerial(((TSerial*)(p->info))->sezoane);
					if( duratas > durataw )
					{
						sr = (TSerial*)(p->info);
						sr->vizionat = durataw;

						if(Push(s,sr) == 0)	return 1;
//elimin din coada watch_later
						if( p->urm == NULL ) 
						{
							if( ant != NULL )
							{
								ant->urm = NULL;
								SC(cs) = ant;
								return 1;
							}
							else
							{
								IC(cs) = NULL;
								SC(cs) = NULL;
								return 1;
							}
						}
						if(ant == NULL)	//este inceputul cozii
								IC(cs) = p->urm;
						else
							ant->urm = p->urm;
						if(IC(cs) == NULL) 
							SC(cs) = NULL;
						return 1;
					}
					else
						{
						sr = (TSerial*)(p->info);
						if(Push(sh,sr) == 0) return 1;

						if( p->urm == NULL ) 
						{
							if(ant != NULL)
							{
								ant->urm = NULL;
								SC(cs) = ant;
								return 0;
							}
							else
							{
								IC(cs) = NULL;
								SC(cs) = NULL;
								return 0;
							}
						}
						if(ant == NULL)		//este ic coada
							IC(cs) = p->urm;
						else				//este in coada
							ant->urm = p->urm;

						if( IC(cs) == NULL ) SC(cs) = NULL;
						return 0;
						}
				}
		}
	return 1;
}

int MutaWatchLater(TLG *L, char * numeS, TCoada *cs)
{
	TSerial * sr;
	TLG p;
	TLG ant = NULL;
	p = *L;
	for(ant = NULL, p = *L; p != NULL; ant = p, p = p->urm)
		{
			if (strcmp(((TSerial*)(p->info))->numes,numeS) == 0)
				{
					sr = (TSerial*)(p->info);
					if(InsCoadaWL(cs, sr) == 0) return 1;
	
					if(ant == NULL)		//se insereaza la inceputul listei
						*L = p->urm;
					else
						ant->urm = p->urm;

				return 0;
				}
		}
	return 1;
}

int AdaugaSezonQ(TCoada *cw, char * numeS, TCoada *c, int index)
{
	TCoada * cs;
	TLG L = IC(cw);

	for ( ; L != NULL; L = L->urm)
	{ 
		if (strcmp( ((TSerial*)(L->info))->numes,numeS) == 0)
			{
					TSezon  * sz = malloc(sizeof(TSezon));
					if (sz == NULL) return 1;
					sz->nr_ep = index;
					sz->TEp = (TCoada*)c;
					cs = ((TSerial*)(L->info))->sezoane;
					if(InsCoadaSz(cs, sz) == 0) return 1;
					return 0;
			}
	}
	return 1;
}
//Distruge serial
void DistrugeSerial(TLG* aL) /* distruge lista */
{

	while(*aL != NULL)
    {
//		
		TLG aux = *aL;     /* adresa celulei eliminate */
        if (!aux)
            return;
//		printf("DistrugeSerial (TSerial*)(aux->info))->sezoane=%p\n",((TSerial*)(aux->info))->sezoane);

		DistrugeSezon( ((TSerial*)(aux->info))->sezoane );
		free(((TSerial*)(aux->info))->numes);
		*aL = aux->urm;    /* deconecteaza celula din lista */
        free(aux);   /* elibereaza spatiul ocupat de celula */
	}
//	free(*aL);
	return ;
}

//adauga sezon in liste
int AdaugaSezon(TLG L, char * numeS, TCoada *c, int index)
{
	TCoada * cs;
	for ( ; L != NULL; L = L->urm)
	{ 
		if (strcmp( ((TSerial*)(L->info))->numes,numeS) == 0)
			{
					TSezon  * sz = malloc(sizeof(TSezon));
					if (sz == NULL) return 1;
					sz->nr_ep = index;
					sz->TEp = (TCoada*)c;
					cs = ((TSerial*)(L->info))->sezoane;
					if(InsCoadaSz(cs, sz) == 0) return 1;
					return 0;
			}
	}
	return 1;
}
void AfiSeriale(TLG L, char antet[], FILE *f_out)
{
	fprintf(f_out,"Categoria %s: ", antet);          	/* afiseaza antetul */
	if(L != NULL) 
	{
 	fprintf(f_out,"[(%s, %.1f)",  ((TSerial*)(L->info))->numes,((TSerial*)(L->info))->rating); 
	L = L->urm;
	for(; L != NULL; L = L->urm)
		{
	    	fprintf(f_out,", (%s, %.1f)",  ((TSerial*)(L->info))->numes,((TSerial*)(L->info))->rating); 
		}
	fprintf(f_out,"].\n");
	}
	else fprintf(f_out,"[].\n");
}

void AfiSerialeS(TStiva *a, char antet[], FILE *f_out)
{
	fprintf(f_out,"Categoria %s: ", antet);          	/* afiseaza antetul */
  	if (!VIDAS (a))
	{

		TLG L = VF(a); 
		fprintf(f_out,"[(%s, %.1f)",  ((TSerial*)(L->info))->numes,((TSerial*)(L->info))->rating);
		L = L->urm;
		for(; L != NULL; L = L->urm)
	        fprintf(f_out,", (%s, %.1f)",  ((TSerial*)(L->info))->numes,((TSerial*)(L->info))->rating); 
		fprintf(f_out,"].\n");
	}
	else fprintf(f_out,"[].\n");

}

void AfiSerialeQ(TCoada *a, char antet[], FILE *f_out)
{
	fprintf(f_out,"Categoria %s: ", antet);          	/* afiseaza antetul */
  	if (!VidaQ (a))
	{
		TLG L = IC(a); 
		fprintf(f_out,"[(%s, %.1f)",  ((TSerial*)(L->info))->numes,((TSerial*)(L->info))->rating);
		L = L->urm;
		for(; L != NULL; L = L->urm)
	        fprintf(f_out,", (%s, %.1f)",  ((TSerial*)(L->info))->numes,((TSerial*)(L->info))->rating); 
		fprintf(f_out,"].\n");
	}
	else fprintf(f_out,"[].\n");          	

 }

void AfiSerialeX(TLG L, int id, FILE *f_out)
{
   	fprintf(f_out,"Categoria %d: [", id);
	fprintf(f_out,"(%s, %.1f)",  ((TSerial*)(L->info))->numes,((TSerial*)(L->info))->rating); 
	L = L->urm;
	for(; L != NULL; L = L->urm)
	        fprintf(f_out,", (%s, %.1f )",  ((TSerial*)(L->info))->numes,((TSerial*)(L->info))->rating); 
	fprintf(f_out,"].\n");
}
//*************************
//tema2 - Program principal
//*************************  

int main(int argc, char* argv[])
{
	void *c, *cs, *watch_later;	//cozi
	void *currently_watching, *history; //stive
    FILE * f_in, *f_out; //argumente 1 si 2 linie comanda
    char* line = NULL;
    char *numefis_in, *numefis_out, *word;
	int i, id, index, id_cat, integral, durataW;
	size_t len = 0;
	//TLG Tendinte,Documentare,Tutoriale,Top10
    numefis_in = argv[1];
    numefis_out = argv[2];
    char *cmd1 = "add";
    char *cmd2 = "add_sez";
    char *cmd3 = "add_top";
    char *cmd4 = "later";
    char *cmd5 = "watch";
    char *cmd6 = "show";
	char *show1 = "later";
	char *show2 = "watching";
	char *show3 = "top10";
	char *show4 = "history";
    
  //deschid fis de intrare si fis de iesire 
    f_in = fopen(numefis_in,"rt");
    if(f_in == NULL)
    	return 1;
	 f_out = fopen(numefis_out,"w+");
    if(f_out == NULL)
    	return 1;

    TLG *categ ;
	categ = (TLG*)calloc(3,sizeof(TLG));
	if(!categ)
	{
		free(categ);
		return 1;
	}	
	watch_later = InitQ(sizeof(TSerial));	//initializare coada watch_later

	currently_watching = InitS(sizeof(TSerial));	//initailizare stive
	history = InitS(sizeof(TSerial));

	TLG * Top10;
	Top10 = calloc(1,sizeof(TLG));
	if(!Top10) return 1;
	line = malloc(sizeof(char)*1024);

    while (getline(&line,&len,f_in) != -1 && strlen(line) != 1)
    	{
    		if (line[strlen(line) - 1] =='\n')
   			line[strlen(line) - 1] = '\0' ; // se adauga \0 la sfarsit pentru parsare corecta

  		char * cmd = strtok(line," ");

//cautare comenzi din fisier f.in
//comanda add
 			if (strcmp(cmd, cmd1) == 0)
			{
				char * ID = strtok(NULL," ");
				char * numeS = strtok(NULL," ");
				char * ratingS = strtok(NULL," ");
				char * nr_Sez = strtok(NULL," ");	//nr. de sezoane
				word = strtok(NULL," ");		//nr. de episoade sezon 1

				cs = InitQ(sizeof(TSezon));	//initializare coada sezoane
				if (!cs) return 1;
				id = atoi(ID);				//nr intreg ID
				if(AdaugaSerial(&categ[id-1], id, numeS, ratingS, nr_Sez, cs, ordS) == 0)
					return 0;
				while(word)	//citesc linia pana la sfarsit
				{
					index = atoi(word);			//nr. de episoade
					c = InitQ(sizeof(int));		//initializare coada episoade
					if (!c) return 1;
					
					for(i = 0; i < index; i++)		//bucla generare coada episoade
					{
						word = strtok(NULL," ");

						if(InsCoadaEp(c,word) == 0) return 1;
					}

					TSezon * sz = malloc(sizeof(TSezon));
					if (sz == NULL) return 1;

					sz->nr_ep = index;
					sz->TEp = (TCoada*)c;

					if(InsCoadaSz(cs, sz) == 0) return 1;

					if(word != NULL)
						word = strtok(NULL," ");
				}
					len = LungimeLG(&categ[id-1]);
					int poz = Pozitie(&categ[id-1],numeS);
					fprintf(f_out,"Serialul %s a fost adaugat la pozitia %d.\n", numeS, poz);
			}

//comanda add_sez
			if (strcmp(cmd, cmd2) == 0)
			{

				char * nume_serial = strtok(NULL," ");		//nume serial
				char * word =strtok(NULL," ");
				index = atoi(word);			//nr. de episoade
				if(GasitS(history, nume_serial) == 1) return 0;	
								
				c = InitQ(sizeof(int));		//initializare coada episoade
				if (!c) return 1;
				for(i = 0; i < index; i++)		//bucla generare coada episoade
				{
					word = strtok(NULL," ");
					if(InsCoadaEp(c,word) == 0) return 1;
				}

				for(i = 0; i < 3; i++)
				{
					if (AdaugaSezon(categ[i], nume_serial, c , index) == 0) //c=coada de episoade
					{
						fprintf(f_out,"Serialul %s are un sezon nou.\n", nume_serial);
						break;
					}
				}
				if (AdaugaSezon(*Top10, nume_serial, c, index) == 0)		//adauga sezon in Top 10
				{
						fprintf(f_out,"Serialul %s are un sezon nou.\n", nume_serial);
				}
				if (AdaugaSezonQ( watch_later, nume_serial, c, index) == 0)		//adauga sezon in coada watch_later
				{
						fprintf(f_out,"Serialul %s are un sezon nou.\n", nume_serial);
				}
				if (AdaugaSezonS( currently_watching, nume_serial, c, index) == 0)		//adauga sezon in stiva_currently_watching
				{
						fprintf(f_out,"Serialul %s are un sezon nou.\n", nume_serial);
				}

			}

//comanda add_top
 			if (strcmp(cmd, cmd3) == 0)
			{
				char * ID = strtok(NULL," ");
				char * numeS = strtok(NULL," ");
				char * ratingS = strtok(NULL," ");
				char * nr_Sez = strtok(NULL," ");	//nr. de sezoane

				word = strtok(NULL," ");		//nr. de episoade sezon 1
				cs = InitQ(sizeof(TSezon));	//initializare coada sezoane
				if (!cs) return 1;
				id = atoi(ID);				//nr intreg ID
				len = LungimeLG(Top10);

				if(AdaugaSerialTop(Top10, id, numeS, ratingS, nr_Sez, cs) == 0) return 0;
				while(word)	//citesc linia pana la sfarsit
					{
						index = atoi(word);			//nr. de episoade
					
						c = InitQ(sizeof(int));		//initializare coada episoade
						if (!c) return 1;
					
						for(i = 0; i < index; i++)		//bucla generare coada episoade
						{
							word = strtok(NULL," ");

							if(InsCoadaEp(c, word) == 0) return 1;
						}

						TSezon * sz = malloc(sizeof(TSezon));
						if (sz == NULL) return 1;

						sz->nr_ep = index;
						sz->TEp = (TCoada*)c;

						if(InsCoadaSz(cs, sz) == 0) return 1;

						if(word != NULL)
							word = strtok(NULL," ");
					}
					 AfiSeriale(*Top10, "top10", f_out);
			}
//comanda later
 			if (strcmp(cmd, cmd4) == 0)
		 	{
				char * nume_serial = strtok(NULL," ");
				for(i = 0; i < 3; i++)
				{
					if (MutaWatchLater(&categ[i], nume_serial, watch_later) == 0)
					{
						break;
					}
				}
				MutaWatchLater(Top10, nume_serial, watch_later);		//adauga sezon in Top 10
				len = NrQ(watch_later);
				fprintf(f_out,"Serialul %s se afla in coada de asteptare pe pozitia %zu.\n", nume_serial, len);
			}

//comanda watch
 			if (strcmp(cmd, cmd5) == 0 )
			{
				char * nume_serial = strtok(NULL," ");
				char * durata_s = strtok(NULL," ");
				durataW = atoi(durata_s);
				int rasp = 0;
				integral = 0;
				rasp = AddDS(currently_watching, nume_serial, durataW, history);
				if( rasp == 0) //nu s-a gasit in stiva currently_watching,sau nu s-a vizualizat intreg
//								s-a actualizat stiva cu durata vizionata
				{
					for(i = 0; i < 3; i++)
					{
						if (MutaCW(&categ[i], nume_serial, currently_watching, durataW, history) == 0)
							{
								integral = 1;	
								break;
							}
					}
					if ( MutaCW(Top10, nume_serial, currently_watching, durataW, history) == 0)		// in Top 10
						 {
							integral = 1;
						}
					if (MutaCWQ(watch_later, nume_serial, currently_watching, durataW, history) == 0)		//din coada watch_later
						{
							integral = 1;	
						}
				}
				else integral = rasp;


				if(integral == 1)
					fprintf(f_out,"Serialul %s a fost vizionat integral.\n", nume_serial);					

			}

//comanda show
 			if (strcmp(cmd, cmd6) == 0)
 			{
				char * cat = strtok(NULL," ");
				if (isdigit(*cat))
					{
				 		id_cat = atoi(cat);
						AfiSeriale(categ[id_cat-1], cat, f_out);	
					}
				else
					{
					if (strcmp(cat, show1) == 0)
					{
						AfiSerialeQ(watch_later, cat, f_out);
					}
					if (strcmp(cat, show2) == 0)
						AfiSerialeS(currently_watching, cat, f_out);
					if (strcmp(cat, show3) == 0)
							AfiSeriale(*Top10, cat, f_out);
					if (strcmp(cat, show4) == 0)
						AfiSerialeS(history, cat, f_out);
					}
    		}
		line = realloc(line,sizeof(char)*1024);
    	}
	
	
	DistrS(&currently_watching);
	DistrS(&history);
	DistrQ(&watch_later);
	DistrugeSerial(Top10);
	for(i = 0; i < 3; i++)	 DistrugeSerial(&categ[i]);

	free(categ);
	free(Top10);
	free(line);	//eliberez buffer citire din fisier intrare
    fclose(f_in);	//inchid fisierele de intare si iesire
	fclose(f_out);
    return 0;
}
