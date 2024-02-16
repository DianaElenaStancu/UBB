#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <regex>
#include <unordered_map>
#include <sstream>
=
using namespace std;

ifstream fin("../in.txt");
ofstream fout("../out.txt");
ifstream fin_af_const("../automat_finit_constante_de_toate.txt");
ifstream fin_af_id("../automat_finit_identificatori.txt");

string getText() {
    string text;
    string line;
    while(getline(fin, line)) {
        text += line;
    }
    return text;
}

const vector<string> keywords = {"#include <iostream> using namespace std; int main()", "return", "float", "int", "if", "else", "while", "cin", "cout", "endl"};
const vector<string> separatorsAtoms = {";", "(", ")", "{", "}", "<<", ">>"};
const vector<string> algebraicOperators = {"+", "-", "*", "/", "%", "="};
const vector<string> relationalOperators = {">=", "==", "!=", "<=", ">", "<"};

struct Atom {
    string atomValue;
    string atomType;
    int atomCode;
};

unordered_map<string, int> atomToCode;
int lastId = 2;

void populateAtomToCodeMap() {
    for(string atom : separatorsAtoms) {
        atomToCode[atom] = lastId;
        lastId++;
    }
    for(string atom : algebraicOperators) {
        atomToCode[atom] = lastId;
        lastId++;
    }
    for(string atom : relationalOperators) {
        atomToCode[atom] = lastId;
        lastId++;
    }
    for(string atom : keywords) {
        atomToCode[atom] = lastId;
        lastId++;
    }
}

int findMatch(vector<string> values, string text) {
    for(auto value:values) {
        string sub = text.substr(0, min(value.size(), text.size()));
        if(sub == value)
            return sub.size();
    }
    return 0;
}

vector<Atom> getAtoms(string text) {
    AutomatFinit af_const(fin_af_const);
    AutomatFinit af_id(fin_af_id);

    vector<Atom> atoms;

    int matchLength;
    while(!text.empty()) {
        while(text[0] == ' ' && !text.empty()) {
            text = text.substr(1);
        }

        matchLength = findMatch(keywords, text);
        if(matchLength != 0) {
            string atomValue = text.substr(0, matchLength);
            string atomType = "Keyword";
            int atomCode = atomToCode[atomValue];
            Atom atom = {atomValue, atomType, atomCode};

            atoms.push_back(atom);
            text = text.substr(matchLength);
            continue;
        }
        matchLength = findMatch(separatorsAtoms, text);
        if(matchLength != 0) {
            string atomValue = text.substr(0, matchLength);
            string atomType = "Separator";
            int atomCode = atomToCode[atomValue];
            Atom atom = {atomValue, atomType, atomCode};

            atoms.push_back(atom);
            text = text.substr(matchLength);
            continue;
        }

        matchLength = findMatch(algebraicOperators, text);
        if(matchLength != 0) {
            string atomValue = text.substr(0, matchLength);
            string atomType = "AlgebricOperator";
            int atomCode = atomToCode[atomValue];
            Atom atom = {atomValue, atomType, atomCode};

            atoms.push_back(atom);
            text = text.substr(matchLength);
            continue;
        }

        matchLength = findMatch(relationalOperators, text);
        if(matchLength != 0) {
            string atomValue = text.substr(0, matchLength);
            string atomType = "RelationalOperator";
            int atomCode = atomToCode[atomValue];
            Atom atom = {atomValue, atomType, atomCode};

            atoms.push_back(atom);
            text = text.substr(matchLength);
            continue;
        }

        matchLength = findWithAutomatFinit(text, af_const);
        if(matchLength != 0) {
            string atomValue = text.substr(0, matchLength);
            string atomType = "Const";
            int atomCode = 1;
            Atom atom = {atomValue, atomType, atomCode};

            atoms.push_back(atom);
            text = text.substr(matchLength);
            continue;
        }

        matchLength = findWithAutomatFinit(text, af_id);
        if(matchLength != 0) {
            string atomValue = text.substr(0, matchLength);
            if(matchLength > 8)
                throw runtime_error("Identifier size > 8: " + atomValue);
            string atomType = "Id";
            int atomCode = 0;
            Atom atom = {atomValue, atomType, atomCode};

            atoms.push_back(atom);
            text = text.substr(matchLength);
            continue;
        }

        throw runtime_error("Cannot parse text:" + text);
    }

    return atoms;
}



int main() {
    string text = getText();
    populateAtomToCodeMap();
    vector<Atom> atoms = getAtoms(text);

    for(auto atom:atoms)
        fout<<atom.atomValue<<" "<<atom.atomType<<" "<<atom.atomCode<<"\n";

    auto fip = createFipAndTs(atoms);

    fout<<"FIP\nAtom Code | TS Position\n";
    for(FipEntry entry : fip) {
        fout << entry.atomCode << " " << entry.TsPosition << " ";
        if(entry.TsPosition != NULL)
            fout<<(*entry.TsPosition).atomValue;
        fout<<"\n";
    }

    return 0;
}
