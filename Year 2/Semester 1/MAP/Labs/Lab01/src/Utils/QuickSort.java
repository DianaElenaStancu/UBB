package Utils;

public class QuickSort extends AbstractSorter{
    @Override
    public int[] sort(int[] ints) {
        QuickSort(ints, 0, ints.length);
        return ints;
    }

    private void QuickSort(int[] ints, int left, int right) {
        int pivot = findPivot(ints, left, right);
        if (left < pivot - 1) {
            QuickSort(ints, left, pivot);
        }
        if (right > pivot + 1) {
            QuickSort(ints, pivot + 1, right);
        }
    }

    private int findPivot(int[] ints, int left, int right) {
        int i = left;
        int j = right - 1;
        int pivot = ints[i];
        while (i != j) {
            while (ints[j] >= pivot && j > i) {
                j--;
            }
            ints[i] = ints[j];
            while (ints[i] <= pivot && i < j) {
                i++;
            }
            ints[j] = ints[i];
        }
        ints[i] = pivot;
        return i;
    }
}
