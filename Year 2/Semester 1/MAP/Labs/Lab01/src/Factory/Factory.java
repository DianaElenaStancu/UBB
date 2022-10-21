package Factory;

import Container.Container;
import Container.Strategy;

public interface Factory {
    public Container createContainer(Strategy strategy);
}
