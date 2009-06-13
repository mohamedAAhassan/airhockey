#ifndef __SEZNAM_H
#define __SEZNAM_H

#include "Vertex.h"

#include <iostream>

using namespace std;

	struct element // element v seznamu
	{
		//int key; // vrednost
		Vertex *key;
		int idx;
		element *prev, *next; // kazalca za naprej in nazaj
	};

class seznam  // razred seznam
{
private:


	int idx;


public:
	element *head;  // glava
	element *tail;  // rep

	seznam()  // konstruktor
	{
		head = NULL;  // inicializacija
		tail = NULL;
		idx = 0;
	}

	void vstaviVGlavo(Vertex *_key)
	{
		element *novi = new element;  // naredim nov element

		novi->next = head;   // kaze naprej na glavo
		novi->prev = NULL; // nazaj na NULL

		novi->key = _key;  // vstavim vrednost
		novi->idx = this->idx;
		this->idx++;

		if(head!=NULL)  // ce seznam ni prazen...
			head->prev = novi;
		else  // ce seznam je prazen
			tail = novi;

		head = novi;  // premaknem kazalec, da je spet glava na zacetku
	}

		void popraviIndexe()
	{
		int st = head->idx;

		for(element *p=head; p!=NULL; p=p->next)  // zacnem pri glavi in se pomikam naprej
		{
			p->idx = st-p->idx;
		}
	}


/*	void vstaviZaElement(element *el, int _key)
	{
		if(el == NULL)  // preverim, ce je el sploh v seznamu
		{
			cout<<"Napaka: podatka ni!"<<endl;  // ni -> napaka
			return;
		}
		// ok, torej naredim nov element
		element *novi = new element;
		novi->key = _key; // vstavim vrednost
		novi->idx = this->idx;
		this->idx++;

		novi->prev = el;  // prevezem kazalce
		novi->next = el->next;
		el->next = novi;

		if(novi->next != NULL) // ce naslednji el ne kaze na null
			novi->next->prev = novi;
		else  // ... v nasprotnem primeru
			tail = novi;

	}*/

	void izpisGlavaRep()
	{
		cout<<"Od glave proti repu:";
		for(element *p=head; p!=NULL; p=p->next)  // zacnem pri glavi in se pomikam naprej
		{

			p->key->point.dumpInfo();
		}
		cout<<endl<<endl;
	}

	Vertex *vrniElZMinY()
	{
	    element *minEl = this->head;
		for(element *p=head; p!=NULL; p=p->next)  // obhod
		{

			if(p->key->point.y < minEl->key->point.y)
                minEl = p;
		}

		return minEl->key;
	}

/*	void izpisRepGlava() // zacnem pri repu in se pomikam nazaj
	{
		cout<<"Od repa proti glavi:";
		for(element *p=tail; p!=NULL; p=p->prev)
		{
			cout<<p->key<<' '; // izpis vrednosti
		}
		cout<<endl<<endl;
	}*/

	/*element* najdi(int _key)
	{
		for(element *p=head; p!=NULL; p=p->next) // pomikam se po seznamu naprej
		{
			if(p->key == _key)  // ce najdem element
				return p;  // ga vrnem
		}

		return NULL; // v nasprotnem primeru vrnem NULL
	}*/

	void brisi(element *el)
	{
		if(el == NULL)  // ce podatka ni, zakljucim podprogram, saj nimam kaj za brisat
		{
			cout<<"Napaka: podatka ni!"<<endl;
			return;
		}

		if(el->prev == NULL && el->next == NULL)  // da se program ne sesuje ob brisanju zadnjega elementa
		{
			this->idx = 0;
			delete el;
			el = head = tail =  NULL;
			return;
		}

		if(el->prev != NULL)  // prevezem kazalce
			el->prev->next = el->next;
		else
		{
			head = el->next;
			head->prev = NULL;
		}

		if(el->next != NULL)
			el->next->prev = el->prev;
		else
		{
			tail = el->prev;
			tail->next = NULL;
		}

		this->idx--;
		delete el;  // pobrisem element

	}


    void zamenjaj(element **e1, element **e2)
	{
        Vertex  *tmp = (*e1)->key;
		(*e1)->key = (*e2)->key;
		(*e2)->key = tmp;
	}


    element* deli(element *dno, element *vrh)
	{
		double pe = dno->key->point.angle;
		element *l = dno, *d = vrh;
		bool konec = false;


		while(!konec)
		{
			while(l->key->point.angle <= pe)
			{
				l=l->next;
				if(l==vrh) break;
			}

			while(d->key->point.angle >= pe)
			{
				d=d->prev;
				if(d==dno) break;
			}

			if(l->idx<d->idx)
				zamenjaj(&l, &d);
			else
				konec = true;

		}

		zamenjaj(&dno, &d);


		return d;
	}

	void hitroUredi(element *dno, element *vrh)
	{
		element* j;
		if(dno!=NULL && vrh!=NULL)
		{
			if(dno->idx<vrh->idx)
			{
				j = deli(dno, vrh);
				hitroUredi(dno, j->prev);
				hitroUredi(j->next, vrh);
			}
		}
	}
};

#endif
