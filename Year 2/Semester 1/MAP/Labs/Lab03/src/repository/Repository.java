package repository;

import domain.Entity;
import domain.exceptions.EntityAlreadyExistsException;
import domain.exceptions.EntityMissingException;
import domain.validators.ValidationException;

/**
 * CRUD operations repository interface
 * @param <ID> type E must have an attribute of type ID
 * @param <E>  type of entities saved in repository
 */

public interface Repository<ID, E extends Entity<ID>> {

    /**
     * Returns the entity that has the given id
     * @param id the id of the entity to be returned
     *           id must not be null
     * @return the entity with the specified id
     *          or null - if there is no entity with the given id
     * @throws IllegalArgumentException
     *                  if id is null.
     * @throws EntityMissingException
     *                  if the entity doesn't exist.
     */
    E findOne(ID id) throws IllegalArgumentException, EntityMissingException;

    /**
     *
     * @return Iterable<E> all entities
     */
    Iterable<E> findAll();

    /**
     * Adds an entity in repository
     * @param entity
     *         entity must be not null
     * @return null- if the given entity is saved
     *         otherwise returns the entity (id already exists)
     * @throws ValidationException
     *            if the entity is not valid
     * @throws IllegalArgumentException
     *             if the given entity is null.     *
     * @throws EntityAlreadyExistsException
     *             if the entity is already in repository
     */
    E save(E entity) throws ValidationException, IllegalArgumentException, EntityAlreadyExistsException;


    /**
     * Removes the entity with the specified id
     * @param id
     *      id must be not null
     * @return the removed entity or null if there is no entity with the given id
     * @throws IllegalArgumentException
     *                   if the given id is null.
     * @throws EntityMissingException
     *                  if there is no user with the given id.
     */
    E delete(ID id) throws IllegalArgumentException;

    /**
     * Updates the entity with the given id
     * @param entity
     *          entity must not be null
     * @return null - if the entity is updated,
     *                otherwise  returns the entity  - (e.g id does not exist).
     * @throws IllegalArgumentException
     *             if the given entity is null.
     * @throws ValidationException
     *             if the entity is not valid.
     * @throws EntityMissingException
     *              if the entity doesn't exist.
     */
    E update(E entity) throws IllegalArgumentException, ValidationException, EntityMissingException;

    /**
     * Clears the repository
     */
    void clear();

}

