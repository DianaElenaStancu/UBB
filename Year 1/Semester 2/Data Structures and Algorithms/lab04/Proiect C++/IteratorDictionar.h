#pragma once
#include "Dictionar.h"

class IteratorDictionar
{
	friend class Dictionar;
private:

    	//constructorul primeste o referinta catre Container
    	//iteratorul va referi primul element din container
	IteratorDictionar(Dictionar& d);

	//contine o referinta catre containerul pe care il itereaza
	Dictionar& dict;
	/* aici e reprezentarea specifica a iteratorului */
    int curent;

public:

		//reseteaza pozitia iteratorului la inceputul containerului
		void prim();

		//muta iteratorul in container
		// arunca exceptie daca iteratorul nu e valid
		void urmator();

		//verifica daca iteratorul e valid (indica un element al containerului)
		bool valid() const;

		//returneaza valoarea elementului din container referit de iterator
		//arunca exceptie daca iteratorul nu e valid
		TElem element() const;

        //elimina si returneaza perechea curenta referita de iterator
        //dupa operatie, perechea curenta de iterator este elementul urmator dictionarului
        //sau in cazul in care elementul eliminat a fost ultimul, iteratorul este nevalid
        //arunca exceptie in cazul in care iteratorul este nevalid
        TElem elimina();
};
