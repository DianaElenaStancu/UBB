package grades;

public class Tema {
    private String id;
    private String descriere;

    public Tema(String id, String descriere) {
        this.id = id;
        this.descriere = descriere;
    }

    public String getId() {
        return id;
    }

    public void setId(String id) {
        this.id = id;
    }

    public String getDescriere() {
        return descriere;
    }

    public void setDescriere(String descriere) {
        this.descriere = descriere;
    }

    @Override
    public String toString() {
        return "Tema{" +
                "id='" + id + '\'' +
                ", descriere='" + descriere + '\'' +
                '}';
    }
}
