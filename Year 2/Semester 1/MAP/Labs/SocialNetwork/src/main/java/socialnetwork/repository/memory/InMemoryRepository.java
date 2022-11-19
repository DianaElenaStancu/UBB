package socialnetwork.repository.memory;

import socialnetwork.domain.Entity;
import socialnetwork.domain.exceptions.EntityMissingException;
import socialnetwork.domain.exceptions.UserAlreadyExistsException;
import socialnetwork.domain.exceptions.UserMissingException;
import socialnetwork.domain.validators.Validator;
import socialnetwork.repository.Repository;

import java.util.HashMap;
import java.util.Map;

public class InMemoryRepository<ID, E extends Entity<ID>> implements Repository<ID,E> {

    Map<ID,E> entities;

    public InMemoryRepository(Map<ID, E> entities) {
        this.entities = entities;
    }

    public InMemoryRepository(Validator<E> validator) {
        entities = new HashMap<ID,E>();
    }

    public InMemoryRepository() {
        entities = new HashMap<ID,E>();
    }

    /**
     * @return Iterable<E> object with all entities from the repository
     */
    @Override
    public Iterable<E> findAll() {
        return entities.values();
    }

    /**
     * Method that returns the map of the objects
     * @return a map object with all entities from the repository
     */
    public Map<ID, E> findAllMap() {
        return entities;
    }
    @Override
    public E findOne(ID id){
        if (id==null)
            throw new IllegalArgumentException("id must be not null.");
        if (entities.containsKey(id)) {
            return entities.get(id);
        }
        throw new EntityMissingException(id + " doesn't exist.");
    }


    @Override
    public E save(E entity) {
        if (entity==null)
            throw new IllegalArgumentException("entity must be not null");
        if (entities.containsKey(entity.getId()))
            throw new UserAlreadyExistsException(entity.getId() + " already exists.");
        entities.put(entity.getId(),entity);
        return entity;
    }

    @Override
    public E delete(ID id) {
        if (id == null)
            throw new IllegalArgumentException("entity must be not null");
        if (!entities.containsKey(id))
            throw new UserMissingException(id + " doesn't exist.");
        E entity = entities.get(id);
        entities.remove(id);
        return entity;
    }

    @Override
    public E update(E entity) {
        if(entity == null)
            throw new IllegalArgumentException("entity must be not null!");

        if (!entities.containsKey(entity.getId()))
            throw new UserMissingException(entity.getId() + " doesn't exist.");

        entities.put(entity.getId(),entity);

        return entity;
    }

    public void clear() {
        entities.clear();
    }
}
