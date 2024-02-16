//
// Created by Diana Stancu on 11/13/2023.
//

#include "AutomatFinit.h"

vector<string> split(string str, char del);

AutomatFinit::AutomatFinit(ifstream& fin) {
    string multime_stari_string;
    fin >> multime_stari_string;
    multime_stari = split(multime_stari_string, ';');

    fin >> stare_initiala;

    if (std::find(multime_stari.begin(), multime_stari.end(), stare_initiala) == multime_stari.end()) {
        throw runtime_error("Starea initiala nu exista in multimea starilor\n");
    }

    string multime_stari_finale_string;
    fin >> multime_stari_finale_string;
    multime_stari_finale = split(multime_stari_finale_string, ';');
    for (auto &stare : multime_stari_finale) {
        if (std::find(multime_stari.begin(), multime_stari.end(), stare) == multime_stari.end()) {
            throw runtime_error("Starea finala nu exista in multimea starilor\n");
        }
    }

    fin >> numar_tranzitii;

    for (int i = 0; i < numar_tranzitii; i++) {
        string tranzitie;
        fin >> tranzitie;

        vector<string> elem = split(tranzitie, ';');
        struct tranzitie tranz = {elem[0], elem[1], elem[2][0]};


        if (std::find(multime_stari.begin(), multime_stari.end(), tranz.stare_initiala) == multime_stari.end() ||
            std::find(multime_stari.begin(), multime_stari.end(), tranz.stare_finala) == multime_stari.end()) {
            throw runtime_error("Cel putin una din stari nu exista in multimea starilor\n");
        }

        tranzitii.push_back(tranz);
        alfabet.insert(tranz.valoare);
    }
}

vector<string> split(string str, char del) {
    stringstream ss(str);
    vector<string> res;
    string token;
    while (getline(ss, token, del)) {
        res.push_back(token);
    }
    return res;
}

int AutomatFinit::findPrefixMaximal(string secv) {
    string stare = stare_initiala;
    string s = "";
    string bestS = "";

    for (int i = 0; i < secv.size(); i++) {
        char ch = secv[i];
        bool gasit = 0;
        for (tranzitie &tr : tranzitii) {
            if (tr.stare_initiala == stare && tr.valoare == ch) {
                stare = tr.stare_finala;
                s+=ch;
                gasit = 1;
                break;
            }
        }
        if(std::find(multime_stari_finale.begin(), multime_stari_finale.end(), stare) != multime_stari_finale.end()) {
            bestS = s;
        }

        if (!gasit) {
            return bestS.size();
        }
    }
    return bestS.size();
}
