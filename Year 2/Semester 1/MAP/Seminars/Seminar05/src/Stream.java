import java.util.Arrays;
import java.util.List;
import java.util.Optional;

public class Stream {
    public static void main(String[] args) {
        List<String> list = Arrays.asList("asf", "bcd", "asd", "bed", "bbb");
        String rez = list.stream()
                .filter(x -> {
                    return x.startsWith("b");
                })
                .map(x -> {
                    return x.toUpperCase();
                })
                .reduce("", (x,y)->x + y);
        System.out.println("A: ");
        System.out.println(rez);

        System.out.println("A: ");
        list.stream()
                .filter(x -> {
                    return x.startsWith("b");
                })
                .map(x -> {
                    return x.toUpperCase();
                })
                .forEach(System.out::println);

        System.out.println("C: ");
        Optional<String> rez1 = list.stream()
                .filter(x -> {
                    return x.startsWith("b");
                })
                .map(x -> {
                    return x.toUpperCase();
                })
                .reduce((x,y)->x + y);

        if (rez.isEmpty())
            System.out.println(rez1.get());
        rez1.ifPresent(x-> System.out.println(x));
    }
}
