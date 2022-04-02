#include "Dictionar.h"
#include <iostream>
#include "IteratorDictionar.h"
using namespace std;
Dictionar::Dictionar() {
	/* de adaugat */
    cp = 1;
    n = 0;
    elems = new TElem [cp];
    urm = new int [cp];
    prec = new int [cp];
    initSpatiuLiber(cp);
    prim = ultim = -1;

}

Dictionar::~Dictionar() {
	/* de adaugat */
    delete[] elems;
    delete[] urm;
    delete[] prec;
}

TValoare Dictionar::adauga(TCheie c, TValoare v){
	/* de adaugat */
    //caut in dictionar daca se afla deja un element cu cheia data
    int p = prim;
    while (p != -1 && elems[p].first != c) {
        p = urm[p];
    }
    if (p != -1) {
        //am gasit pozitia unde se afla cheia si inlocuiesc valoarea
        //returnez vechea valoare
        TValoare v_old = elems[p].second;
        elems[p].second = v;
        return v_old;
    }
    else {
        //adaug in lista noul element
        //cout << "adaug: " << c << ' ' << primLiber << ' ' << prim << ' ' << urm[primLiber] <<  endl;
        TElem e;
        e.first = c;
        e.second = v;
        int nou = creeazaNod(e);
        if (prim == -1)
            prim = nou;
        urm[ultim] = nou;
        prec[nou] = ultim;
        ultim = nou;
        urm[nou] = -1;
    }
	return NULL_TVALOARE;
}



//cauta o cheie si returneaza valoarea asociata (daca dictionarul contine cheia) sau null
TValoare Dictionar::cauta(TCheie c) const{
	/* de adaugat */
    if (n == 0)
        return NULL_TVALOARE;
    int i = prim;
    do {
        if(elems[i].first == c) {
            return elems[i].second;
        }
        i = urm[i];
    }while(i != -1);
	return NULL_TVALOARE;
}


TValoare Dictionar::sterge(TCheie c){
	/* de adaugat */
    int i = prim;
    while(i != -1 && elems[i].first != c) {
        i = urm[i];
    }
    if (i == -1)
        return NULL_TVALOARE;
    if (i == prim) {
        prim = urm[prim];
    } else {
        //elementul precedent va avea pozitia elementului urmator celui sters
        //iar elementul urmator celui sters va avea ca precedent elementul precedent celui sters
        urm[prec[i]] = urm[i];
        prec[urm[i]] = prec[i];
    }
    TValoare v_old = elems[i].second;
    elems[i].first = elems[i].second = 0;
    dealoca(i);
    return v_old;
}


int Dictionar::dim() const {
	return n;
}

bool Dictionar::vid() const{
	return n==0;
}


IteratorDictionar Dictionar::iterator() const {
	return  IteratorDictionar(*this);
}

int Dictionar::aloca() {
    //furnizeaza un spatiu liber de indice i
    //se sterge primul nod din lista spatiului liber
    if (primLiber == -1)
        redim(2*cp);
    int i = primLiber;
    primLiber = urm[primLiber];
    ++n;
    return i;
}

void Dictionar::initSpatiuLiber(int cp) {
    //creeaza o LDI de lungime cp - toate pozitiile din tablou sunt libere
    for (int i = 0; i < cp - 1; i++)
        urm[i] = i + 1;
    urm[cp-1] = -1;
    for (int i = 0; i < cp; i++)
        prec[i] = i - 1;
    primLiber = 0;
}

void Dictionar::dealoca(int i) {
    //trece pozitia i in lista spatiului liber
    //se adauga i la inceputul listei spatiului liber
    urm[i] = primLiber;
    primLiber = i;
    --n;
}

int Dictionar::creeazaNod(TElem e) {
    int i = aloca();
    elems[i] = e;
    urm[i] = -1;
    prec[i] = -1;
    return i;
}

void Dictionar::redim(int new_cp) {
    TElem* new_elems = new TElem [new_cp];
    int *new_urm = new int [new_cp], *new_prec = new int [new_cp];
    for (int i = 0; i < cp; i++) {
        new_urm[i] = urm[i];
        new_prec[i] = prec[i];
        new_elems[i] = elems[i];
    }
    for (int i = cp; i < new_cp - 1; i++) {
        new_urm[i] = i + 1;
        new_prec[i] = i - 1;
    }
    new_urm[new_cp - 1] = -1;
    new_prec[new_cp - 1] = new_cp - 1;
    delete[] elems;
    delete[] urm;
    delete[] prec;

    elems = new_elems;
    prec = new_prec;
    urm = new_urm;
    primLiber = cp;
    cp = new_cp;
}


