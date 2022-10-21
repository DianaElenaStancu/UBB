package character;

public class Adventure {
    public static void fightAdventure(CanFight x){
        x.fight();
    }

    public static void talkAdventure(CanTalk x) {
        x.talk();
    }

    public static void flyAdventure(CanFly x){
        x.fly();
    }

    public static void fightCharacter(Character x) {
        x.fight();
    }
}
