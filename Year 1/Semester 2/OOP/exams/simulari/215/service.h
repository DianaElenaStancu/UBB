//
// Created by Diana-Elena Stancu on 19/05/2022.
//

#ifndef INC_215_SERVICE_H
#define INC_215_SERVICE_H

#include "repository.h"
class Service {
private:
    Repository& repo;
public:
    Service(Repository& repo) : repo { repo } {};
    vector <Joc> get_all() const;
};


#endif //INC_215_SERVICE_H
