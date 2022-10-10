import Container.Strategy;
import Model.MessageTask;
import Runner.PrinterTaskRunner;
import Runner.StrategyTaskRunner;
import Runner.TaskRunner;

import java.time.LocalDateTime;

public class TestRunner {
    private static MessageTask[] getMessages() {
        MessageTask temaLab = new MessageTask("1",
                "doua probleme", "pentru seminar", "Mihai", "Florentina", LocalDateTime.now());
        MessageTask temaSeminar = new MessageTask("2",
                "trei probleme", "pentru laborator", "Andrei", "Andreea", LocalDateTime.now());
        MessageTask temaCurs = new MessageTask("3",
                "patru probleme", "pentru curs", "Diana", "Paula", LocalDateTime.now());
        return new MessageTask[]{temaLab, temaSeminar, temaCurs};
    }

    public static void run() {
        MessageTask[] messages = getMessages();
//        for (MessageTask message : messages) {
//            message.execute();
//        }
//        TaskRunner taskRunner = new StrategyTaskRunner(Strategy.LIFO);
//        taskRunner.addTask(messages[0]);
//        taskRunner.addTask(messages[1]);
//        taskRunner.addTask(messages[2]);
//        taskRunner.executeAll();

        TaskRunner taskRunner = new StrategyTaskRunner(Strategy.LIFO);
        taskRunner.addTask(messages[0]);
        taskRunner.addTask(messages[1]);
        taskRunner.addTask(messages[2]);
        PrinterTaskRunner printerTaskRunner = new PrinterTaskRunner(taskRunner);

        printerTaskRunner.executeAll();
    }
}
