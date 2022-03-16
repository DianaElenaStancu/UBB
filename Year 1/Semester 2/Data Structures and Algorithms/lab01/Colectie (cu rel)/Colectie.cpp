#include "Colectie.h"
#include "IteratorColectie.h"
#include <iostream>

using namespace std;

bool rel(TElem e1, TElem e2) {
	/* de adaugat */
    if (e1 <= e2)
        return true;
	return false;
}


Colectie::Colectie() {
	/* de adaugat */
    this -> cp = 1;
    element = new TElem[cp];
    this -> n = 0;
}


void Colectie::redim() {
    TElem* elemNou = new TElem[2*cp];
    for (int i = 0; i < n; i++)
        elemNou[i] = element[i];
    delete[] element;
    element = elemNou;
    this -> cp *= 2;
}

void Colectie::adauga(TElem e) {
	/* de adaugat */
    if (n == cp)
        redim();
    int i = 0;
    while (i < n && rel(element[i], e))
        i++;

    int pi = i;
    i = n;
    while (i > pi) {
        element[i] = element[i - 1];
        i--;
    }

    this -> element[pi] = e;
    n++;
}


bool Colectie::sterge(TElem e) {
	/* de adaugat */
    if (n == 0)
        return false;

    int p, st, dr;
    p = -1;
    st = 0;
    dr = n;
    while(st <= dr) {
        int m = (st+dr)/2;
        if (element[m] == e) {
            p = m;
            break;
        }
        if (element[m] > e)
            dr = m - 1;
        if (element[m] < e)
            st = m + 1;
    }

    if (p == -1)
        return false;
    else {
        for (int j = p; j < n; j++) {
            element[j] = element[j + 1];
        }
        n--;
    }
    return true;
}

bool Colectie::cauta(TElem elem) const {
	/* de adaugat */
    if (n == 0)
        return false;

    int p, st, dr;
    p = -1;
    st = 0;
    dr = n;
    while(st <= dr) {
        int m = (st+dr)/2;
        if (element[m] == elem) {
            p = m;
            break;
        }
        if (element[m] > elem)
            dr = m - 1;
        if (element[m] < elem)
            st = m + 1;
    }
    if (p == -1)
	    return false;
    return true;
}


int Colectie::nrAparitii(TElem elem) const {
	/* de adaugat */
    if (n == 0)
        return false;
    
    int c = 0;
    int p, st, dr;
    p = -1;
    st = 0;
    dr = n;
    while(st <= dr) {
        int m = (st+dr)/2;
        if (element[m] == elem) {
            p = m;
            break;
        }
        if (element[m] > elem)
            dr = m - 1;
        if (element[m] < elem)
            st = m + 1;
    }
    if (p == -1)
        return c;
    else {
        int i = p;
        while (element[p] == element[i])
            c++, i++;
        while (element[p] == element[i])
            c++, i--;
        return c;
    }
}



int Colectie::dim() const {
	/* de adaugat */
	return n;
}


bool Colectie::vida() const {
	/* de adaugat */
    if (n == 0)
	    return true;
    return false;
}


IteratorColectie Colectie::iterator() const {
	return  IteratorColectie(*this);
}


Colectie::~Colectie() {
	/* de adaugat */
    delete[] element;
}
