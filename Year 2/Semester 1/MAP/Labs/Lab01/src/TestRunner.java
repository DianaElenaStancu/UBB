import Container.Strategy;
import Model.MessageTask;
import Model.SortingTask;
import Model.Task;
import Runner.*;
import Utils.BubbleSort;
import Utils.QuickSort;

import java.time.LocalDateTime;
import java.util.Vector;

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

    public static void runSort(String[] args) {
        int[] numbers = {3, 6, 2, 3, 9, 2, 1, 8, 3};
        System.out.println("Bubble Sort\n");
        SortingTask sortingTask1 = new SortingTask("4", "sorter1", new BubbleSort(), numbers);
        sortingTask1.execute();
        System.out.println("\nMerge Sort");
        SortingTask sortingTask2 = new SortingTask("5", "sorter2", new QuickSort(), numbers);
        sortingTask2.execute();

        System.out.println("\nSorting tasks");

        MessageTask[] messages = getMessages();
        TaskRunner taskRunner = new StrategyTaskRunner(Strategy.LIFO);
        taskRunner.addTask(messages[0]);
        taskRunner.addTask(messages[1]);
        taskRunner.addTask(messages[2]);
        taskRunner.addTask(sortingTask1);
        taskRunner.addTask(sortingTask2);
        PrinterTaskRunner printerTaskRunner = new PrinterTaskRunner(taskRunner);
        printerTaskRunner.executeAll();

    }

    public static void runPrinter(String[] args) {
        MessageTask[] messages = getMessages();

        TaskRunner taskRunner = new StrategyTaskRunner(Strategy.LIFO);
        taskRunner.addTask(messages[0]);
        taskRunner.addTask(messages[1]);
        taskRunner.addTask(messages[2]);
        PrinterTaskRunner printerTaskRunner = new PrinterTaskRunner(taskRunner);

        printerTaskRunner.executeAll();
    }

    public static void runStrategyTaskRunner(String[] args) {
        // cerinta 13
        StrategyTaskRunner runner = new StrategyTaskRunner(Strategy.LIFO);
        MessageTask[] messages = getMessages();
        runner.addTask(messages[0]);
        runner.addTask(messages[1]);
        runner.addTask(messages[2]);
        runner.executeAll();

        PrinterTaskRunner printerRunner = new PrinterTaskRunner(runner);
        printerRunner.executeAll();
    }

    public static void runAll(String[] args) {
        // cerinta 14
        MessageTask[] messages = getMessages();
        System.out.println("\nStrategy runner");
        StrategyTaskRunner strategyRunner;
        if (args[0].equals("LIFO"))
            strategyRunner  = new StrategyTaskRunner(Strategy.LIFO);
        else {
            strategyRunner  = new StrategyTaskRunner(Strategy.FIFO);
        }
        strategyRunner.addTask(messages[0]);
        strategyRunner.addTask(messages[1]);
        strategyRunner.addTask(messages[2]);
        strategyRunner.executeAll();

        System.out.println("\nPrinter runner");
        strategyRunner.addTask(messages[0]);
        strategyRunner.addTask(messages[1]);
        strategyRunner.addTask(messages[2]);
        PrinterTaskRunner printerRunner = new PrinterTaskRunner(strategyRunner);
        printerRunner.executeAll();

        System.out.println("\nDelay runner");
        strategyRunner.addTask(messages[0]);
        strategyRunner.addTask(messages[1]);
        strategyRunner.addTask(messages[2]);
        DelayTaskRunner delayRunner = new DelayTaskRunner(strategyRunner);
        delayRunner.executeAll();
    }
}
