import Container.Strategy;
import Model.MessageTask;
import Runner.DelayTaskRunner;
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

    public static void run(String[] args) {
        /*MessageTask[] messages = getMessages();

        TaskRunner taskRunner = new StrategyTaskRunner(Strategy.LIFO);
        taskRunner.addTask(messages[0]);
        taskRunner.addTask(messages[1]);
        taskRunner.addTask(messages[2]);
        PrinterTaskRunner printerTaskRunner = new PrinterTaskRunner(taskRunner);

        printerTaskRunner.executeAll();*/
        /*
        // cerinta 13
        StrategyTaskRunner runner = new StrategyTaskRunner(Strategy.LIFO);
        MessageTask[] messages = getMessages();
        runner.addTask(messages[0]);
        runner.addTask(messages[1]);
        runner.addTask(messages[2]);
        runner.executeAll();

        PrinterTaskRunner printerRunner = new PrinterTaskRunner(runner);
        printerRunner.executeAll();*/
        // cerinta 14
        StrategyTaskRunner runner;
        if (args[0].equals("LIFO"))
           runner  = new StrategyTaskRunner(Strategy.LIFO);
        else {
            runner  = new StrategyTaskRunner(Strategy.FIFO);
        }
        MessageTask[] messages = getMessages();
        runner.addTask(messages[0]);
        runner.addTask(messages[1]);
        runner.addTask(messages[2]);
        DelayTaskRunner decorator = new DelayTaskRunner(runner);
        decorator.executeAll();

    }
}
