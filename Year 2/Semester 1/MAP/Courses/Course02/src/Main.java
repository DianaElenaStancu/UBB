import character.Adventure;
import character.Character;
import character.IronMan;

public class Main {
    public static void main(String[] args) {
        //Character ironMan = new IronMan();
        IronMan ironMan = new IronMan();
        Adventure.fightAdventure(ironMan);
        Adventure.flyAdventure(ironMan);
        Adventure.talkAdventure(ironMan);
        Adventure.fightCharacter(ironMan);
    }
}