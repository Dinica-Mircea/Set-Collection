#include "IteratorMultime.h"
#include "Multime.h"
#include <stdexcept>

using namespace std;

IteratorMultime::IteratorMultime(const Multime& m) : multime(m) {
	//complexitate thetha(1) in toate cazurile
	curent=multime.prim;
}


void IteratorMultime::prim() {
	//complexitate thetha(1) in toate cazurile
	curent = multime.prim;
}


void IteratorMultime::urmator() {
	//complexitate thetha(1) in toate cazurile
	curent = multime.urmator[curent];
}


TElem IteratorMultime::element() const {
	//complexitate thetha(1) in toate cazurile
	if (valid() == false)
		throw exception();
	else return multime.valoare[curent];
}

bool IteratorMultime::valid() const {
	//complexitate thetha(1) in toate cazurile
	if(curent==-1 or multime.valoare[curent]==NULL_TELEM)
		return false;
	return true;
}
