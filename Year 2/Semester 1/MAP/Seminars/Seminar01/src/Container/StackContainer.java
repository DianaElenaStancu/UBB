package Container;

import Model.Task;
import Utils.Constants;

public class StackContainer implements Container{
    private Task[] tasks;
    private int size;

    public StackContainer() {
        tasks = new Task[Constants.INITIAL_TASK_SIZE];
        size = 0;
    }

    public int size() {
        return size;
    }

    public boolean isEmpty() {
        return size == 0;
    }

    public Task remove() {
        if (!isEmpty()) {
            --size;
            return tasks[size];
        }
        return null;
    }

    public void add(Task task) {
        if (tasks.length == size) {
            Task[] t = new Task[tasks.length * 2];
            System.arraycopy(tasks, 0, t, 0, tasks.length);
            tasks = t;
        }
        tasks[size] = task;
        ++size;
    }
}
