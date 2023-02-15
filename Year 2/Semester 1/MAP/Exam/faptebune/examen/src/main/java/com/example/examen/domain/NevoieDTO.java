package com.example.examen.domain;

public class NevoieDTO {
    private Long id;
    private String omInNevoieNume;
    private String omSalvator;

    public NevoieDTO(Long id, String omInNevoieNume, String omSalvator) {
        this.id = id;
        this.omInNevoieNume = omInNevoieNume;
        this.omSalvator = omSalvator;
    }

    public Long getId() {
        return id;
    }

    public void setId(Long id) {
        this.id = id;
    }

    public String getOmInNevoieNume() {
        return omInNevoieNume;
    }

    public void setOmInNevoieNume(String omInNevoieNume) {
        this.omInNevoieNume = omInNevoieNume;
    }

    public String getOmSalvator() {
        return omSalvator;
    }

    public void setOmSalvator(String omSalvator) {
        this.omSalvator = omSalvator;
    }
}
