package Factory;

import Container.Container;
import Container.Strategy;
import Container.StackContainer;
import Container.QueueContainer;

public class TaskContainerFactory implements Factory{
    private static TaskContainerFactory instance = null;
    private TaskContainerFactory() {} // nu se poate instantia

    public static TaskContainerFactory getInstance() {
        if (instance == null)
            instance = new TaskContainerFactory();
        return instance;
    }

    public Container createContainer (Strategy strategy) {
        return switch (strategy) {
          case LIFO -> new StackContainer();
          case FIFO -> new QueueContainer();
        };
    }
}
