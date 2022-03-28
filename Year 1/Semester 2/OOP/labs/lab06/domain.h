//
// Created by Diana-Elena Stancu on 27/03/2022.
//

#ifndef LAB06_DOMAIN_H
#define LAB06_DOMAIN_H
#include <string>

using std::string;
using std::istream;
using std::ostream;

typedef string TypeTitlu;
typedef string TypeDescriere;
typedef string TypeTip;
typedef int TypeDurata;

class Activitate {
private: //campuri: titlu, descriere, tip, durata
    TypeTitlu Titlu;
    TypeDescriere Descriere;
    TypeTip Tip;
    TypeDurata Durata = 0;
public:
    // constructori
    // constructor fara parametrii
    Activitate() = default;
    // constructor cu parametrii
    Activitate(const TypeTitlu& Titlu, const TypeDescriere& Descriere, const TypeTip& Tip, const TypeDurata& Durata) :
            Titlu(Titlu), Descriere(Descriere), Tip(Tip), Durata(Durata) {}
    // constructor de copiere
    Activitate(const Activitate&);

    // operator de atribuire
    Activitate& operator=(const Activitate&);

    // getteri
    TypeTitlu getTitlu() const;
    TypeDescriere getDescriere() const;
    TypeTip getTip() const;
    TypeDurata getDurata() const;

    // setteri
    void setTitlu(const TypeTitlu&);
    void setDescriere(const TypeDescriere &);
    void setTip(const TypeTip &);
    void setDurata(const TypeDurata &);

    // operatori de egalitate
    bool operator==(const Activitate&) const;
    bool operator!=(const Activitate&) const;

    // operatori relationali
    bool operator<(const Activitate&) const;
    bool operator<=(const Activitate&) const;
    bool operator>(const Activitate&) const;
    bool operator>=(const Activitate&) const;


    // operatori de intrare/iesire
    friend istream& operator>>(istream& in, Activitate& obj) {
        in>>obj.Titlu;
        in>>obj.Descriere;
        in>>obj.Tip;
        in>>obj.Durata;
        return in;
    }

    friend ostream& operator<<(ostream& out, const Activitate& obj) {
        out << obj.Titlu << ' ' << obj.Descriere << ' ' << obj.Tip << ' ' << obj.Durata;
        return out;
    }
};

#endif //LAB06_DOMAIN_H
