#include <iostream>
#include <fstream>
#include "gramatica.h"
using namespace std;
ifstream fin("../input.txt");

gramatica read(){
    gramatica gr;
    string reg;
    vector<string> reguliProductie;
    vector<char> neterminale;
    vector<char> terminale;
    while(fin>>reg) {
        reguliProductie.push_back(reg);
        for (int c = 0; c < reg.size(); c++) {
            if (isupper(reg[c])) {
                neterminale.push_back(reg[c]);
            } else if (islower(reg[c])) {
                terminale.push_back(reg[c]);
            }
        }
    }
    gr.setNeterminale(neterminale);
    gr.setTerminale(terminale);
    gr.setReguliProductie(reguliProductie);
    return gr;
}

void afiseazaReguliProdRecStg(gramatica gr){
    vector<string> reguliProductie = gr.getReguliProductie();
    for (auto reg : reguliProductie) {
        if (reg[0] == reg[3]) {
            cout << reg << endl;
        }
    }
}

int main() {
    gramatica gr = read();
    afiseazaReguliProdRecStg(gr);
    return 0;
}
