package Utils;

public class BubbleSort extends AbstractSorter{
    @Override
    public int[] sort(int[] ints) {
        boolean isSorted = false;
        while (!isSorted) {
            isSorted = true;
            for (int i = 0; i < ints.length - 1; i++) {
                if (ints[i] > ints[i + 1]) {
                    isSorted = false;
                    int aux = ints[i];
                    ints[i] = ints[i + 1];
                    ints[i + 1] = aux;
                }
            }
        }
        return ints;
    }
}
