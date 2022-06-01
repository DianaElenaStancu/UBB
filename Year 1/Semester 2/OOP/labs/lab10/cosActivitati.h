//
// Created by Diana-Elena Stancu on 24/05/2022.
//

#ifndef LAB10_COSACTIVITATI_H
#define LAB10_COSACTIVITATI_H

#include "Observer.h"

#include "domain.h"
#include <vector>
#include "repository.h"
using std::vector;

class CosActivitati : public Observable
{
private:
    vector <Activitate> v;
public:
    CosActivitati() : Observable() {
    };
    void append(const Activitate& c);
    vector <Activitate> getAll();
    void clear();
    void generate(int count);
    //void exportCSV(const string& fileN);
};


#endif //LAB10_COSACTIVITATI_H
