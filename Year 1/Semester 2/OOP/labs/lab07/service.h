//
// Created by Diana-Elena Stancu on 06/04/2022.
//

#ifndef LAB07_SERVICE_H
#define LAB07_SERVICE_H
#include "repository.h"
#include "validator.h"

class Service {
private:
    Repository& repository;
    //const Validator
public:
    Service()=delete;
    Service(const Service&) = delete;
    explicit Service(Repository& repository) noexcept :repository(repository){};
    void addSRV(const TypeTitlu &, const TypeDescriere &, const TypeTip&, const TypeDurata &);
    void removeSRV(const TypeTitlu &, const TypeDescriere &, const TypeTip &, const TypeDurata&);
    void modifySRV(const TypeTitlu & titlu, const TypeDescriere & descriere, const TypeTip& tip, const TypeDurata & durata,
                            const TypeTitlu & titlu_nou, const TypeDescriere & descriere_noua, const TypeTip& tip_nou, const TypeDurata & durata_noua);
    const DynamicArray<Activitate>& getAll() const noexcept;
    Activitate findSRV(const TypeTitlu& titlu);
    DynamicArray<Activitate> filterDescriere(const TypeDescriere & descriere);
    DynamicArray<Activitate> filterTip(const TypeTip & tip);
    DynamicArray<Activitate> sortTitlu();
    DynamicArray<Activitate> sortDescriere();
    DynamicArray<Activitate> sortTipDurata();
};


#endif //LAB07_SERVICE_H
