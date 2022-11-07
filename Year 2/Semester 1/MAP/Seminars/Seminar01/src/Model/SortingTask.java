package Model;

import Utils.AbstractSorter;

import java.util.Arrays;

public class SortingTask extends Task{
    private final AbstractSorter sorter;
    int[] ints;

    public SortingTask(String taskId, String description, AbstractSorter sorter, int[] ints) {
        super(taskId, description);
        this.sorter = sorter;
        this.ints = ints;
    }

    @Override
    public void execute() {
        this.sorter.sort(this.ints);
        System.out.println(Arrays.toString(ints));
    }

    public int[] getSortedArray() {
        return this.ints;
    }
}
