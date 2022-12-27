package socialnetwork.domain;

import java.io.Serializable;
import java.util.Objects;

public class Entity<ID> implements Serializable {

//    @Serial
//    private static final long serialVersionUID = 7331115341259248461L;
    private ID id;

    public Entity(){}

    public Entity(ID id) {
        this.id = id;
    }

    public ID getId() {
        return id;
    }
    public void setId(ID id) {
        this.id = id;
    }

    @Override
    public int hashCode() {
        return Objects.hash(this.id);
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj)
            return true;
        if (obj == null || getClass() != obj.getClass())
            return false;
        Entity entity = (Entity) obj;
        return Objects.equals(entity.id, this.id);
    }
}