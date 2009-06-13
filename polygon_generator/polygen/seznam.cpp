#include <iostream>
#include <ctime>

using namespace std;

class seznam  // razred seznam
{
private:
	struct element // element v seznamu
	{
		int key; // vrednost
		int idx;
		element *prev, *next; // kazalca za naprej in nazaj
	};

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

	void vstaviVGlavo(int _key)
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


	void vstaviZaElement(element *el, int _key)
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

	}

	void izpisGlavaRep()
	{
		cout<<"Od glave proti repu:";
		for(element *p=head; p!=NULL; p=p->next)  // zacnem pri glavi in se pomikam naprej
		{

			cout<<p->key<<' '; // izpis vrednosti
		}
		cout<<endl<<endl;
	}

	void izpisRepGlava() // zacnem pri repu in se pomikam nazaj
	{
		cout<<"Od repa proti glavi:";
		for(element *p=tail; p!=NULL; p=p->prev)
		{
			cout<<p->key<<' '; // izpis vrednosti
		}
		cout<<endl<<endl;
	}

	element* najdi(int _key)
	{
		for(element *p=head; p!=NULL; p=p->next) // pomikam se po seznamu naprej
		{
			if(p->key == _key)  // ce najdem element
				return p;  // ga vrnem
		}

		return NULL; // v nasprotnem primeru vrnem NULL
	}

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

	void zamenjaj(element *e1, element *e2)
	{
		int tmp = e1->key;
		e1->key = e2->key;
		e2->key = tmp;
	}

	element* deli(element *dno, element *vrh)
	{
	//	int m = (dno+vrh)/2;
	//	zamenjaj(dno, m);
	//	dno = 0;
	//	vrh = dolzina;
		// a = tabela
		int pe = dno->key;
		element *l = dno, *d = vrh;
		bool konec = false;


		while(!konec)
		{
			while(l->key <= pe && l->next != vrh)
				l=l->next;

			while(d->key >= pe && d->prev != dno)
				d=d->prev;

			if(l->idx<d->idx)
				zamenjaj(l, d);
			else
				konec = true;

		}

		zamenjaj(dno, d);

	
		return d;
	}

	void hitroUredi(element *dno, element *vrh)
	{
		element* j;
		if(dno->idx<vrh->idx)
		{
			j = deli(dno, vrh);
			hitroUredi(dno, j->prev);
			hitroUredi(j->next, vrh);
		}
	}
};



int main()
{
	srand(time(NULL));
	seznam sz;

	short izbira;  // spremenljivka za izbiro
	int podatek;  // spremenljivke v katere berem uporabnikove podatke/zahteve
	int podatek2;

	while(izbira!=4)  // meni
	{
		cout<<"Menu"<<endl;
		cout<<"========="<<endl;
		cout<<"1 Generiraj nakljuèno zaporedje"<<endl;
		cout<<"2 Izpis"<<endl;
		cout<<"3 Uredi"<<endl;
		cout<<"4 Konec"<<endl;
		cout<<"========="<<endl;
		cout<<"izberi: ";
		cin>>izbira;
		cout<<endl;

		switch(izbira)  
		{
		case 4:
			cout<<"Adijo! :D"<<endl;
			break;

		case 1:
		{
			cout<<"Vnesite velikost zap.: ";
			cin>>podatek;
			cout<<endl;

			while(podatek>0)
			{
				sz.vstaviVGlavo(rand()%100);
				podatek--;
			}
			break;
		}


		case 2:
			sz.izpisGlavaRep();
			break;

		case 3:
			sz.hitroUredi(sz.head, sz.tail);
			break;



		default:
			break;
		}
	}

	system("pause");
	return 0;
}