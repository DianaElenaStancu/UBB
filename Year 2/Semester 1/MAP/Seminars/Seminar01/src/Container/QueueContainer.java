package Container;

import Model.Task;

public class QueueContainer extends DynamicContainer{

    @Override
    public Task remove() {
        if (!isEmpty()) {
            Task t = tasks[0];
            System.arraycopy(this.tasks, 1, this.tasks, 0, this.size - 1);
            --this.size;
            return t;
        }
        return null;
    }
}
