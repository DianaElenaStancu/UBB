import java.util.Arrays;
import java.util.Random;

import static java.lang.Math.min;

public class Main {
    private static class MyThread extends Thread {
        int id;
        int start;
        int end;
        int[] A;
        int[] B;
        int[] C;

        public MyThread(int id, int start, int end, int[] A, int[] B, int[] C) {
            this.id = id;
            this.start = start;
            this.end = end;
            this.A = A;
            this.B = B;
            this.C = C;
        }

        @Override
        public void run() {
            System.out.println("I am thread with the id = " + id);
            System.out.println("indexes: " + start + " " + end);
            for (int j = start; j <= end; j++) {
                C[j] = A[j] + B[j];
                System.out.println("I am thread " + id + " and I am at the position " + j);
            }
        }
    }

    public static void main(String[] args) {
        int p = 3;

        Thread[] threads = new MyThread[p];

        Random rand = new Random();

        int N = 14;
        int L = 1000;
        int PART = N/p;
        int R = N%p;

        int[] A = new int[N];
        int[] B = new int[N];
        int[] C = new int[N];
        int[] ANS = new int[N];

        for (int i = 0; i < A.length; i++) {
            A[i] = rand.nextInt(L) + 1;
            B[i] = rand.nextInt(L) + 1;
            C[i] = 0;
            ANS[i] = A[i] + B[i];
        }

        System.out.println(Arrays.toString(A));
        System.out.println(Arrays.toString(B));

        int start, end = -1;
        for (int i = 0; i < p; i++) {
            start = end + 1;
            end += PART;
            if (R > 0) {
                R--;
                end++;
            }
            threads[i] = new MyThread(i, start, end, A, B, C);
            threads[i].start();
        }


        for (int i = 0; i < p; i++) {
            try {
                threads[i].join();
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }
        }

        System.out.println("Final result: " + Arrays.toString(C));
        System.out.println("Answer: " + Arrays.toString(ANS));

    }
}

