package com.example.examen.domain;

public class Client extends Entity<Long>{
    private String name;
    private int fidelityGrade;
    private int varsta;
    private Hobbies hobbies;

    public Client(Long clientId, String name, int fidelityGrade, int varsta, Hobbies hobbies) {
        super(clientId);
        this.name = name;
        this.fidelityGrade = fidelityGrade;
        this.varsta = varsta;
        this.hobbies = hobbies;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public int getFidelityGrade() {
        return fidelityGrade;
    }

    public void setFidelityGrade(int fidelityGrade) {
        this.fidelityGrade = fidelityGrade;
    }

    public int getVarsta() {
        return varsta;
    }

    public void setVarsta(int varsta) {
        this.varsta = varsta;
    }

    public Hobbies getHobbies() {
        return hobbies;
    }

    public void setHobbies(Hobbies hobbies) {
        this.hobbies = hobbies;
    }

    @Override
    public String toString() {
        return "Client{" +
                "name='" + name + '\'' +
                ", fidelityGrade=" + fidelityGrade +
                ", varsta=" + varsta +
                ", hobbies=" + hobbies +
                '}';
    }
}
