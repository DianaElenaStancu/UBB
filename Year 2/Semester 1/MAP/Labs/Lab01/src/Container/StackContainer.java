package Container;

import Model.Task;
import Utils.Constants;

public class StackContainer extends DynamicContainer{
    @Override
    public Task remove() {
        if (!isEmpty()) {
            --size;
            return tasks[size];
        }
        return null;
    }
}
