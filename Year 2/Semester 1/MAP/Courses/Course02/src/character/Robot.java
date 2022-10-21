package character;

public class Robot extends Character implements CanTalk{
    @Override
    public void fight() {
        System.out.println("Robot can fight");
    }

    @Override
    public void play() {
        System.out.println("Robot can play");
    }

    @Override
    public void talk() {
        System.out.println("Robot can talk");
    }
}
