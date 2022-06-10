//
// Created by Diana-Elena Stancu on 18/05/2022.
//

#ifndef SIMULARE_216_V1_DOMAIN_H
#define SIMULARE_216_V1_DOMAIN_H
#include <string>
#include <sstream>
#include <strstream>
using std::string;
using std::istream;
using std::ostream;

class Jucator {
private:
    string nume;
    string tara;
    int puncte;
    int rank;
public:
    Jucator() = default;
    Jucator(const string& nume, const string& tara, const int puncte, const int rank) : nume { nume }, tara { tara }, puncte { puncte }, rank { rank } {};
    string get_nume() const;
    string get_tara() const;
    int get_puncte() const;
    int get_rank() const;
    void set_puncte(const int puncte_noi);
    void set_ranking(const int rank_nou);
    bool operator==(Jucator& jucator);
    friend istream& operator >>(istream& in, Jucator& jucator);
    friend ostream& operator <<(ostream& in, const Jucator& jucator);
    string to_string() const;
};

void test_domain();

#endif //SIMULARE_216_V1_DOMAIN_H
