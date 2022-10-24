import Repository.StudentFileRepository;
import domain.Student;
import domain.Validator.StudentValidator;

public class TestStudent {
    public static void main(String[] args) {
        StudentFileRepository studentFileRepository = new StudentFileRepository(new StudentValidator(), "data/student.csv");
        studentFileRepository.findAll().forEach(System.out::println);
    }
}
