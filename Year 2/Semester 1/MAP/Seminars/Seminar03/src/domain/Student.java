package domain;

import java.util.Objects;

public class Student extends Entity<Long>{
    private String nume;
    private float media;

    public Student(String nume, float media) {
        this.nume = nume;
        this.media = media;
    }

    public String getNume() {
        return nume;
    }

    public void setNume(String nume) {
        this.nume = nume;
    }

    public float getMedia() {
        return media;
    }

    public void setMedia(float media) {
        this.media = media;
    }

    @Override
    public String toString() {
        return nume + " " + media;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true; // verifica daca au aceeasi adresa
        if (o == null || getClass() != o.getClass()) return false; // verifica daca obiectul este nul sau daca cele doua obiecte sunt din clase diferite
        Student student = (Student) o; // Cast!!
        return Float.compare(student.media, media) == 0 && nume.equals(student.nume); // verifica daca atributele sunt egale
    }

    @Override
    public int hashCode() {
        return Objects.hash(nume, media);
    }

    public int getMediaRotunjita() {
        return Math.round(getMedia());
    }
}

