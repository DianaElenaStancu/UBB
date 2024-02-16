%{
#include <iostream>
#include "analizator_lexical.cpp"
#include <fstream>
#include <vector>
#include <algorithm>
#include <regex>
#include <unordered_map>
#include <sstream>
#include <map>
using namespace std;

#define OTHER               -3
#define ENDLINE             -2
#define WHITESPACE          -1
#define ID                  1
#define CONST               2
#define KEYWORD             3
#define SEPARATOR           4
#define ALGEBRIC_OPERATOR   5
#define RELATIONAL_OPERATOR 6

ofstream fout("out.txt");

vector<string> keywords;
vector<string> separatorsAtoms;
vector<string> algebraicOperators;
vector<string> relationalOperators;


struct Atom {
    string atomValue;
    string atomType;
    int atomCode;
};

unordered_map<string, int> atomToCode;
int lastId = 2;

%}

ID                  [_a-zA-Z]([_a-zA-Z0-9]{0,7})
CONST_INT           0|([1-9]([0-9]*))
CONST_REAL          {CONST_INT}"."[0-9]+
CONST_BINARY        "0b"[01]+
CONST_HEXA          "0x"[0-9A-F]+
CONST_OCTAL         "0"[0-7]+
CONST               {CONST_INT}|{CONST_REAL}|{CONST_BINARY}|{CONST_HEXA}|{CONST_OCTAL}
KEYWORD             "#include <iostream> using namespace std; int main()"|"return"|"float"|"int"|"if"|"else"|"while"|"cin"|"cout"|"endl"|"while"|"repeta"|"panacand"|"sfrepeta"
SEPARATOR           ";"|"("|")"|"{"|"}"|"<<"|">>"
ALGEBRIC_OPERATOR   "+"|"-"|"*"|"/"|"%"|"="
RELATIONAL_OPERATOR   ">="|"=="|"!="|"<="|">"|"<"

%%
{KEYWORD}                   { return KEYWORD; }
{SEPARATOR}                 { return SEPARATOR; }
{ALGEBRIC_OPERATOR}         { return ALGEBRIC_OPERATOR; }
{RELATIONAL_OPERATOR}       { return RELATIONAL_OPERATOR; }
{ID}                        { return ID; }
{CONST}                     { return CONST; }
[\t ]+                      { return WHITESPACE; }
\n                          { return ENDLINE; }
.                           { return OTHER; }

%%

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

map<int, string> lexOutputToAtomType;

void populateLexOutputToAtomType() {
    lexOutputToAtomType[1] = "ID";
    lexOutputToAtomType[2] = "CONST";
    lexOutputToAtomType[3] = "KEYWORD";
    lexOutputToAtomType[4] = "SEPARATOR";
    lexOutputToAtomType[5] = "ALGEBRIC_OPERATOR";
    lexOutputToAtomType[6] = "RELATIONAL_OPERATOR";

}

vector<Atom> getAtoms() {
    vector<Atom> atoms;

    int lexOutput;
    int line = 0;
    while((lexOutput = yylex()) != 0) {
        if(lexOutput == -1) {
            continue;
        }
        else if(lexOutput == -2) {
            line++;
            continue;
        }else if(lexOutput == -3) {
            cout<<"Found unknown character: "<<yytext<<" on line: " <<line+1<<"\n";
            break;
        }else {
            string atomType = lexOutputToAtomType[lexOutput];
            string atomValue = yytext;
            int atomCode;
            if(atomType == "CONST")
                atomCode = 1;
            else if(atomType == "ID")
                atomCode = 0;
            else
                atomCode = atomToCode[atomValue];
            Atom atom = {atomValue, atomType, atomCode};
            atoms.push_back(atom);
        }
    }
    return atoms;
}

struct Node {
    Node *leftChild, *rightChild;
    string atomValue;
};


struct FipEntry {
    int atomCode;
    Node* TsPosition;
};

struct TsEntry {
    string atomValue;
};

Node* findValue(Node *tree, string value) {
    if(tree == NULL)
        return NULL;
    int comp = tree->atomValue.compare(value);
    if(comp == 0)
        return tree;
    if(comp < 0)
        return findValue(tree->rightChild, value);
    return findValue(tree->leftChild, value);
}

void insertValue(Node **tree, string value) {
    if(*tree == NULL) {
        Node* newNode = new Node();
        newNode -> leftChild = NULL;
        newNode -> rightChild = NULL;
        newNode -> atomValue = value;
        *tree = newNode;
        return;
    }
    int comp = (*tree)->atomValue.compare(value);
    if(comp == 0)
        return;
    if(comp < 0)
        return insertValue(&((*tree)->rightChild), value);
    return insertValue(&((*tree)->leftChild), value);
}

struct Output {
    vector<FipEntry> fip;
    Node* SymbolTableIds;
    Node* SymbolTableConsts;
};

Output createFipAndTs(vector<Atom> atoms) {
    Node *binarySearchTreeIds = NULL;
    Node *binarySearchTreeConsts = NULL;

    for(Atom atom : atoms) {
        if(atom.atomType == "ID") {
            if(findValue(binarySearchTreeIds, atom.atomValue) == NULL) {
                insertValue(&binarySearchTreeIds, atom.atomValue);
            }
        }
        else if(atom.atomType == "CONST") {
            if(findValue(binarySearchTreeConsts, atom.atomValue) == NULL) {
                insertValue(&binarySearchTreeConsts, atom.atomValue);
            }
        }
    }
    vector<FipEntry> fip;

    for(Atom atom : atoms) {
        if(atom.atomType == "ID") {
            Node* pos = findValue(binarySearchTreeIds, atom.atomValue);
            FipEntry fipEntry;
            fipEntry.atomCode = atom.atomCode;
            fipEntry.TsPosition = pos;
            fip.push_back(fipEntry);
        }
        else if(atom.atomType == "CONST") {
            Node* pos = findValue(binarySearchTreeConsts, atom.atomValue);
            FipEntry fipEntry;
            fipEntry.atomCode = atom.atomCode;
            fipEntry.TsPosition = pos;
            fip.push_back(fipEntry);
        }
        else{
            FipEntry fipEntry;
            fipEntry.atomCode = atom.atomCode;
            fipEntry.TsPosition = NULL;
            fip.push_back(fipEntry);
        }
    }

    return {fip, binarySearchTreeIds, binarySearchTreeConsts};
}

void printRecTree(Node* tree) {
    if(tree == NULL)
        return;
    printRecTree(tree->leftChild);
    fout<<tree<<" "<<tree->atomValue<<"\n";
    printRecTree(tree->rightChild);
}

void printTree(Node* tree, string tableName) {
    fout<<tableName<<"\n";
    printRecTree(tree);
}


int yywrap() {
    return 1; // Returning 1 indicates there are no more files to process.
}

int main() {
    keywords.push_back("#include <iostream> using namespace std; int main()");
    keywords.push_back("return");
    keywords.push_back("float");
    keywords.push_back("int");
    keywords.push_back("if");
    keywords.push_back("else");
    keywords.push_back("while");
    keywords.push_back("cin");
    keywords.push_back("cout");
    keywords.push_back("endl");

    separatorsAtoms.push_back(";");
    separatorsAtoms.push_back("(");
    separatorsAtoms.push_back(")");
    separatorsAtoms.push_back("{");
    separatorsAtoms.push_back("}");
    separatorsAtoms.push_back("<<");
    separatorsAtoms.push_back(">>");

    algebraicOperators.push_back("+");
    algebraicOperators.push_back("-");
    algebraicOperators.push_back("*");
    algebraicOperators.push_back("/");
    algebraicOperators.push_back("%");
    algebraicOperators.push_back("=");

    relationalOperators.push_back(">=");
    relationalOperators.push_back("==");
    relationalOperators.push_back("!=");
    relationalOperators.push_back("<=");
    relationalOperators.push_back(">");
    relationalOperators.push_back("<");


    populateAtomToCodeMap();
    populateLexOutputToAtomType();
    vector<Atom> atoms = getAtoms();

    for(auto atom:atoms)
        fout<<atom.atomValue<<" "<<atom.atomType<<" "<<atom.atomCode<<"\n";
    fout<<"\n";

    auto output = createFipAndTs(atoms);
    printTree(output.SymbolTableIds, "Symbol Table IDS");
    fout<<"\n";
    printTree(output.SymbolTableConsts, "Symbol Table CONSTS");
    fout<<"\n";
    fout<<"FIP\nAtom Code | TS Position\n";
    for(FipEntry entry : output.fip) {
        fout << entry.atomCode << " " << entry.TsPosition << " ";
        if(entry.TsPosition != NULL)
            fout<<(*entry.TsPosition).atomValue;
        fout<<"\n";
    }

    return 0;
}
