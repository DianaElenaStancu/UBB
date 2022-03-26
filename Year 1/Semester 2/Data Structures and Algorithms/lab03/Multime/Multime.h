#pragma once

#define NULL_TELEM -1
typedef int TElem;

class IteratorMultime;
struct Nod {
    TElem valoare;
    Nod* urmator;
};
class Multime {
	friend class IteratorMultime;

    private:
		/* aici e reprezentarea */
        Nod* primul;
        Nod* ultimul;

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

        //returneaza diferenta dintre valoarea maxima si cea minima (presupunem valori intregi)
        //daca multimea este vida, se returneaza -1
        int diferentaMaxMin() const;

		//returneaza un iterator pe multime
		IteratorMultime iterator() const;

		// destructorul multimii
		~Multime();
};




