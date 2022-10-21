package character;

public interface CanFight extends CanPlay{
    default void fight() {System.out.println("Fight");}
}
