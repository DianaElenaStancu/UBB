package com.example.examen.service;

import com.example.examen.domain.Nevoie;
import com.example.examen.domain.NevoieDTO;
import com.example.examen.domain.Persoana;
import com.example.examen.repository.NevoiDbRepository;
import com.example.examen.repository.PersoaneDbRepository;
import com.example.examen.utils.observer.Observer;

import java.util.ArrayList;
import java.util.List;

public class Service {
    //repo
    //validator
    //constructor
    //functions
    private final PersoaneDbRepository persoaneDbRepository;
    private final NevoiDbRepository nevoiDbRepository;


    public Service(PersoaneDbRepository persoaneDbRepository, NevoiDbRepository nevoiDbRepository) {
        this.persoaneDbRepository = persoaneDbRepository;
        this.nevoiDbRepository = nevoiDbRepository;
    }

    public void savePerson(Persoana person) {
        this.persoaneDbRepository.save(person);
    }

    public List<Persoana> getPersoane() {
        List<Persoana> persoane = new ArrayList<>();
        this.persoaneDbRepository.findAll().forEach(
                persoane::add
        );
        return persoane;
    }


    //nevoi in afara persoanei si din orasul persoanei
    public List<NevoieDTO> getNevoieDTOinTown(Persoana persoana){
        List<NevoieDTO> nevoieDTOS = new ArrayList<>();
        this.nevoiDbRepository.findAll().forEach(
                nevoie -> {
                    if (nevoie.getOmInNevoie() != persoana.getId() &&
                    this.persoaneDbRepository.findOne(nevoie.getOmInNevoie()).getOras() == persoana.getOras()) {
                        String omSalvatorNume = "";
                        if (nevoie.getOmSalvator() != 0)
                            omSalvatorNume = this.persoaneDbRepository.findOne(nevoie.getOmSalvator()).getUsername();
                        nevoieDTOS.add(new NevoieDTO(nevoie.getId(), this.persoaneDbRepository.findOne(nevoie.getOmInNevoie()).getUsername(),
                                omSalvatorNume));
                    }
                }
        );
        return nevoieDTOS;
    }

    public List<NevoieDTO> getNevoieDTOOfPerson(Persoana persoana){
        List<NevoieDTO> nevoieDTOS = new ArrayList<>();
        this.nevoiDbRepository.findAll().forEach(
                nevoie -> {
                    if (nevoie.getOmSalvator() == persoana.getId() ) {
                        String omSalvatorNume = "";
                        if (nevoie.getOmSalvator() != 0)
                            omSalvatorNume = this.persoaneDbRepository.findOne(nevoie.getOmSalvator()).getUsername();
                        nevoieDTOS.add(new NevoieDTO(nevoie.getId(), this.persoaneDbRepository.findOne(nevoie.getOmInNevoie()).getUsername(),
                                omSalvatorNume));
                    }
                }
        );
        return nevoieDTOS;
    }
    public Nevoie findNevoie(Long nevoieId){
        return this.nevoiDbRepository.findOne(nevoieId);
    }

    public void updateNevoie(Nevoie nevoie) {
        this.nevoiDbRepository.update(nevoie);
    }

    public void saveNevoie(Nevoie nevoie) {
        this.nevoiDbRepository.save(nevoie);
    }

    public void addObserver(Observer observer) {
        this.nevoiDbRepository.addObserver(observer);
    }
}
