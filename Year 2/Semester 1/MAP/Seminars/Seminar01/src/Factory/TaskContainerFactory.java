package Factory;

import Container.Container;
import Container.Strategy;
import Container.StackContainer;

public class TaskContainerFactory implements Factory{
    public TaskContainerFactory() {} //--> singleton

    public Container createContainer (Strategy strategy) {
        if (strategy == Strategy.LIFO) {
            return new StackContainer();
        }
        //TO DO FIFO
        return null;
    }
}
