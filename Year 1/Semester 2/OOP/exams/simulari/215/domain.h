//
// Created by Diana-Elena Stancu on 19/05/2022.
//

#ifndef INC_215_DOMAIN_H
#define INC_215_DOMAIN_H
#include <string>
#include <sstream>
#include <strstream>
using std::string;
using std::istream;
using std::ostream;

class Joc {
private:
    int index;
    string titlu;
    int pret;
    string platforma;
    int rating;
public:
    Joc() = default;
    Joc(const int index, const string& titlu, const int pret, const string& platforma, const int rating) : index { index }, titlu { titlu }, pret { pret }, platforma { platforma }, rating { rating } {};
    int get_index() const;
    string get_titlu() const;
    int get_pret() const;
    string get_platforma() const;
    int get_rating() const;
    friend istream& operator >>(istream& in, Joc &joc);
    friend ostream& operator <<(ostream& out, Joc &joc);
    bool operator==(Joc &joc);
    string to_string() const;
};
void test_domain();

#endif //INC_215_DOMAIN_H
