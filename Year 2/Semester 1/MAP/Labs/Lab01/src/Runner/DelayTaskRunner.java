package Runner;

import Utils.Constants;

import java.time.LocalDateTime;

public class DelayTaskRunner extends AbstractTaskRunner{
    public DelayTaskRunner(TaskRunner runner) {
        super(runner);
    }

    @Override
    public void executeOneTask() {
        try {
            Thread.sleep(3000);
            runner.executeOneTask();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        decorateExecuteOneTask();
    }

    private void decorateExecuteOneTask() {
        System.out.println("Task executat: " + LocalDateTime.now().format(Constants.DATE_TIME_FORMATTER));
    }
}
