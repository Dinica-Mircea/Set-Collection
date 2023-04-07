#include "Multime.h"

Multime::Multime() {
	prim = -1;
	prim_liber = 0;
	capacitate = capacitate_maxima;
	urmator = new int[capacitate];
	valoare = new TElem[capacitate];
	for (int i = 0; i < capacitate; i++) {
		valoare[i] = NULL_TELEM;
		urmator[i] = i + 1;
	}
	urmator[capacitate - 1] = -1;
}

int Multime::diferentaMaxMin() const
{
	//complexitate thetha(n) in toate cazurile deoarece iteram prin toata multime
	IteratorMultime it = this->iterator();
	it.prim();
	auto max = it.element();
	auto min = it.element();
	while (it.valid())
	{
		if (it.element() > max)
			max = it.element();
		if (it.element() < min)
			min = it.element();
		it.urmator();
	}
	return max - min;
}

void Multime::asigura_capacitatea() {
	//complexitate thetha(n) in cazul favorabil in care dimensiunea este diferita de capacitate-1
	//complexitate thetha(2n) in cazul defavorabil in care dimensiunea este egala cu capacitate-1
	//complexitate generala thetha(n)
	if (capacitate-1 == dim())
	{
		int capacitate_noua = capacitate * 2;
		int *urmator_nou = new int[capacitate_noua];
		TElem* valoare_nou = new TElem[capacitate_noua];
		for (int i = 0; i < capacitate; i++)
		{
			urmator_nou[i] = urmator[i];
			valoare_nou[i] = valoare[i];
		}
		urmator_nou[capacitate - 1] = capacitate;
		for (int i = capacitate; i < capacitate_noua; i++)
		{
			urmator_nou[i] = i + 1;
			valoare_nou[i] = NULL_TELEM;
		}
		urmator_nou[capacitate_noua-1] = -1;
		delete(urmator);
		delete(valoare);
		urmator = urmator_nou;
		valoare = valoare_nou;
		capacitate = capacitate_noua;
	}
}
bool Multime::adauga(TElem elem) {
	//complexitate thetha(n) in cazul favorabil in care elem este valoarea primului elem din multime
	//complexitate thetha(2n) in cazul defavorabil in care elem nu este deja in multime
	//complexitate thetha(n) in caz general
	asigura_capacitatea();
	if (vida() == true)
	{
		valoare[prim_liber] = elem;
		prim = prim_liber;
		prim_liber = urmator[prim_liber];
		return true;
	}
	IteratorMultime it = this->iterator();
	it.prim();
	while (it.valid()==true)
	{
		if (it.element() == elem)
			return false;
		it.urmator();
	}
	valoare[prim_liber] = elem;
	prim_liber = urmator[prim_liber];
	return true;
}


bool Multime::sterge(TElem elem) {
	//complexitate thetha(1) in cazul favorabil in care elem este primul element din multime(complexitate cauta este O(n))
	//complexitate thetha(n) in cazul defavorabil in care elem nu se afla in multime
	//complexitate O(n) in caz general
	if(cauta(elem)==false)
		return false;
	IteratorMultime it = iterator();
	it.prim();
	if (it.element() == elem)
	{
		int prim_vechi = prim;
		if (dim()==1)
		{
			urmator[prim_vechi] = prim_liber;
			prim_liber = prim_vechi;
			prim = -1;
		}
		else {
			int noul_prim = urmator[prim];
			urmator[prim] = prim_liber;
			prim_liber = prim;
			prim = noul_prim;
		}
		valoare[prim_vechi] = NULL_TELEM;
		return true;
	}
	int prec = prim;
	it.urmator();
	while (it.valid())
	{
		if (it.element() == elem)
		{
			valoare[it.curent] = NULL_TELEM;
			if (urmator[it.curent] == prim_liber)
			{
				int noul_prim_liber = it.curent;
				urmator[it.curent] = prim_liber;
				prim_liber = noul_prim_liber;
			}
			else {
				urmator[prec] = urmator[it.curent];
				int noul_prim_liber = it.curent;
				urmator[it.curent] = prim_liber;
				prim_liber = noul_prim_liber;
			}
			return true;
			
		}
		prec = it.curent;
		it.urmator();
	}
	return false;
}


bool Multime::cauta(TElem elem) const {
	//complexitate thetha(1) in cazul favorabil daca elem este primul element din multime
	//complexitate theta(n) in cazul defavorabil in care elementul nu se afla in multime
	//complexitate O(n) in cazul general
	if(vida()==true)
		return false;
	IteratorMultime it = this->iterator();
	it.prim();
	while (it.valid())
	{
		if (it.element() == elem)
			return true;
		it.urmator();
	}
	return false;
}


int Multime::dim() const {
	//complexitate theta(n) in toate cazurile
	if(vida()==true)
		return 0;
	IteratorMultime it = this->iterator();
	it.prim();
	int nr_elem = 0;
	while (it.valid())
	{
		nr_elem++;
		it.urmator();
	}
	return nr_elem;
}

bool Multime::vida() const {
	//complexitate thetha(1) in toate cazurile
	if(prim==-1)
		return true;
	return false;
}


Multime::~Multime() {
	//complexitate thetha(1) in toate cazurile
	delete(urmator);
	delete(valoare);
	prim = -1;
	prim_liber = -1;
}

void Multime::reuniune(const Multime& b)
{
	//complexitatea este O(n*m) in toate cazurile unde m este nr de elem din b si n nr de elem din a
	IteratorMultime it = b.iterator();
	it.prim();
	while (it.valid())
	{
		adauga(it.element());
		it.urmator();
	}
}


IteratorMultime Multime::iterator() const {
	//complexitate thetha(1) in toate cazurile
	return IteratorMultime(*this);
}

