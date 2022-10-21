package Container;

import Model.Task;
import Utils.Constants;

public abstract class DynamicContainer implements Container {
    Task[] tasks;
    int size;
    public DynamicContainer(){
        tasks = new Task[Constants.INITIAL_TASK_SIZE];
        size = 0;
    }

    public int size() {
        return size;
    }
    public boolean isEmpty() {
        return size == 0;
    }

    public void add(Task task) {
        if (size == tasks.length) {
            Task[] t = new Task[tasks.length * 2];
            System.arraycopy(tasks, 0, t, 0, tasks.length);
            tasks = t;
        }
        tasks[size] = task;
        size++;
    }

    public abstract Task remove();
}
