//
// Created by Diana-Elena Stancu on 24/05/2022.
//

#include "cosActivitati.h"
#include "domain.h"
#include "exceptions.h"
#include <algorithm>
#include <random>
#include <fstream>

void CosActivitati::append(const Activitate& c)
{
    std::vector<Activitate>::iterator it = find_if(v.begin(), v.end(), [c](Activitate x) {return x == c; });
    this->v.push_back(c);
    notify();
}

vector<Activitate> CosActivitati::getAll()
{
    return v;
}

void CosActivitati::clear()
{
    v.clear();
    notify();

}

void CosActivitati::generate(int nr)
{

}
/*
void CosActivitati::exportCSV(const string& fileN)
{
    ofstream fout(fileN);   //washRepo.getElems()
    for (const Activitate& c : v) {
        fout << c.getNrInmatr() << ',' << c.getProd() << ',' << c.getModel() << ',' << c.getTip() << endl;
    }
}
*/
