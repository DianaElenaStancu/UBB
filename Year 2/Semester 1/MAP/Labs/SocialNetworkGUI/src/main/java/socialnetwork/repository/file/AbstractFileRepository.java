package socialnetwork.repository.file;

import socialnetwork.domain.Entity;
import socialnetwork.repository.memory.InMemoryRepository;

import java.io.*;

import java.util.Arrays;
import java.util.List;


public abstract class AbstractFileRepository<ID, E extends Entity<ID>> extends InMemoryRepository<ID,E> {
    String fileName;

    public AbstractFileRepository(String fileName) {
        super();
        this.fileName=fileName;
        loadData();
    }

    /**
     * Loads data from file
     */
    private void loadData(){
        try (BufferedReader br = new BufferedReader(new FileReader(fileName))) {
            String linie;
            while((linie = br.readLine()) != null){
                List<String> attr=Arrays.asList(linie.split(";"));
                E e = this.extractEntity(attr);
                super.save(e);
            }
        }  catch (IOException e) {
            e.printStackTrace();
        }
    }

    /**
     *  Extracts entity  - template method design pattern
     *  Creates an entity of type E having a specified list of @code attributes
     * @param attributes -
     * @return an entity of type E
     */
    public abstract E extractEntity(List<String> attributes);

    /**
     * Comverts the entity to String
     * @param entity E the entity that has to be converted to string
     * @return String - the entity in string format
     */
    protected abstract String createEntityAsString(E entity);

    @Override
    public E save(E entity){
        E e=super.save(entity);
        if (e!=null)
        {
            writeToFile();
        }
        return e;
    }

    @Override
    public E delete(ID id) {
        E e = super.delete(id);
        if (e!=null)
        {
            writeToFile();
        }
        return e;
    }

    @Override
    public E update(E entity) {
        E e = super.update(entity);
        if (e!=null)
        {
            writeToFile();
        }
        return e;
    }

    @Override
    public void clear() {
        super.clear();
        writeToFile();
    }

    protected void writeToFile(){
        try(BufferedWriter bufferedWriter = new BufferedWriter(new FileWriter(this.fileName))) {
            for(E entity : super.findAll()) {
                String entityString = this.createEntityAsString(entity);
                bufferedWriter.write(entityString);
            }
        } catch (IOException fileNotFoundException) {
            fileNotFoundException.printStackTrace();
        }
    }
}

