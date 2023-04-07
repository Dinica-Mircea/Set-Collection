#pragma once
#include "IteratorMultime.h"
#define NULL_TELEM -99999
#define capacitate_maxima 10
typedef int TElem;

class IteratorMultime;

class Multime {
	friend class IteratorMultime;

private:
	/* aici e reprezentarea */
	int capacitate=capacitate_maxima;
	int *urmator;
	TElem *valoare;
	int prim_liber,prim;
	void asigura_capacitatea();

public:
	//constructorul implicit
	Multime();

	//adauga un element in multime
	//returneaza adevarat daca elementul a fost adaugat (nu exista deja in multime)
	bool adauga(TElem e);

	//sterge un element din multime
	//returneaza adevarat daca elementul a existat si a fost sters
	bool sterge(TElem e);

	//verifica daca un element se afla in multime
	bool cauta(TElem elem) const;


	//intoarce numarul de elemente din multime;
	int dim() const;

	//verifica daca multimea e vida;
	bool vida() const;

	//returneaza un iterator pe multime
	IteratorMultime iterator() const;

	//adauga toate elementele din multimea b in multimea curenta
	void reuniune(const Multime& b);

	int diferentaMaxMin() const;

	// destructorul multimii
	~Multime();
};




