#pragma once
#include "IteratorColectie.h"
typedef int TElem;

//pentru perechea din vector (valoare, frecventa)
struct Pereche {
    TElem valoare;
    int frecventa;
};

typedef bool(*Relatie)(TElem, TElem);

//in implementarea operatiilor se va folosi functia (relatia) rel (de ex, pentru <=)
// va fi declarata in .h si implementata in .cpp ca functie externa colectiei
bool rel(TElem, TElem);

class IteratorColectie;

class Colectie {

	friend class IteratorColectie;

private:
	/* aici e reprezentarea */
    //capacitate
    int cp;
    //numarul de elemente
    int n;
    //elementul reprezentand o pereche de tipul (valoare, frecventa)
    Pereche *e;

    //redimensionarea vectorului dinamic
    void redim();

    int cautareBinara(Pereche* pereche, int stanga, int dreapta, TElem elem, bool& gasit) const;
public:
		//constructorul implicit
		Colectie();

		//adauga un element in colectie
		void adauga(TElem e);

		//sterge o aparitie a unui element din colectie
		//returneaza adevarat daca s-a putut sterge
		bool sterge(TElem e);

		//verifica daca un element se afla in colectie
		bool cauta(TElem elem) const;

		//returneaza numar de aparitii ale unui element in colectie
		int nrAparitii(TElem elem) const;


		//intoarce numarul de elemente din colectie;
		int dim() const;

		//verifica daca colectia e vida;
		bool vida() const;

		//returneaza un iterator pe colectie
		IteratorColectie iterator() const;

		// destructorul colectiei
		~Colectie();


};
