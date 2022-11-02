package grades;

public class NotaDTO {
    private String studentName;
    private String profesor;
    private double nota;
    private String temaId;

    public NotaDTO(String studentName, String profesor, String temaId, double nota ) {
        this.studentName = studentName;
        this.profesor = profesor;
        this.nota = nota;
        this.temaId = temaId;
    }

    @Override
    public String toString() {
        return "NotaDTO{" +
                "studentName='" + studentName + '\'' +
                ", profesor='" + profesor + '\'' +
                ", nota=" + nota +
                ", temaId='" + temaId + '\'' +
                '}';
    }
}
