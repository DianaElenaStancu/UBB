import java.io.*;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class Main {
    private static int N, M, n, m, p, offset;
    private static int[][] matrix, kernel, finalMatrix;

    public static void read(String path) {
        try {
            File myObj = new File(path);
            Scanner myReader = new Scanner(myObj);

            N = 10;
            M = 10;

            matrix = new int[N][M];
            if (myReader.hasNextLine()) {
                for (int i = 0; i < N; i++) {
                    String data = myReader.nextLine();
                    String[] line = data.split(" ");
                    for (int j = 0; j < M; j++) {
                        matrix[i][j] = Integer.parseInt(line[j]);
                    }
                }
            }

            n = 3;
            m = 3;

            kernel = new int[n][m];
            if (myReader.hasNextLine()) {
                for (int i = 0; i < n; i++) {
                    String data = myReader.nextLine();
                    String[] line = data.split(" ");
                    for (int j = 0; j < m; j++) {
                        kernel[i][j] = Integer.parseInt(line[j]);
                    }
                }
            }
            myReader.close();
        } catch (FileNotFoundException e) {
            System.out.println("An error occurred.");
            e.printStackTrace();
        }
    }

    public static void write(String path, int[][] matrix) {
        try {
            BufferedWriter bw = new BufferedWriter(new FileWriter(path));
            for (int[] elem : matrix) {
                for (int i : elem) {
                    bw.write(i + " ");
                }
                bw.newLine();
            }
            bw.flush();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static boolean checkAnswer() throws Exception {
        File fileTest = new File("output.txt");
        Scanner scannerTest = new Scanner(fileTest);

        File fileAnswer = new File("answer0.txt");
        Scanner scannerAnswer = new Scanner(fileAnswer);

        while (scannerTest.hasNextLine() && scannerAnswer.hasNextLine()) {
            String test = scannerTest.nextLine();
            String answer = scannerAnswer.nextLine();
            test = test.substring(0, test.length() - 1);
            System.out.println(test + "\n" + answer);
            if (!answer.equals(test)) {
                throw new Exception("Invalid output");
            }
        }

        if (scannerTest.hasNextLine() || scannerAnswer.hasNextLine()) {
            throw new Exception("Invalid output");
        }

        return true;
    }

    public static int Convolution(int x, int y) {
        int output = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                int ii = x - offset + i;
                int jj = y - offset + j;

                if (ii < 0) ii = 0;
                else if (ii >= N) ii = N - 1;
                if (jj < 0) jj = 0;
                else if (jj >= M) jj = M - 1;

                output += matrix[ii][jj] * kernel[i][j];
            }
        }
        System.out.println(output);
        return output;
    }

    public static void sequentialConvolution() {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                finalMatrix[i][j] = Convolution(i, j);
            }
        }
    }

    public static void parallelConvolution() throws InterruptedException {
        Thread[] t = new Worker[p];

        int start, end = 0, chunk, rest;
        if (N > M) {
            chunk = N / p;
            rest = N % p;
        } else {
            chunk = M / p;
            rest = M % p;
        }

        long startTime = System.nanoTime();

        for (int i = 0; i < t.length; i++) {
            start = end;
            end = start + chunk;
            if (rest > 0) {
                end++;
                rest--;
            }
            t[i] = new Worker(M, start, end, finalMatrix);
            t[i].start();
        }

        for (Thread thread : t) {
            thread.join();
        }

        long stopTime = System.nanoTime();

        System.out.println((double) (stopTime - startTime) / 1E6);
    }

    public static class Worker extends Thread {
        int M, start, end;
        int[][] finalMatrix;

        public Worker(int M, int start, int end, int[][] finalMatrix) {
            this.M = M;
            this.start = start;
            this.end = end;
            this.finalMatrix = finalMatrix;
        }

        public void run() {
            if (N > M) {
                for (int i = start; i < end; i++) {
                    for (int j = 0; j < M; j++) {
                        this.finalMatrix[i][j] = Main.Convolution(i, j);
                    }
                }
            } else {
                for (int i = 0; i < N; i++) {
                    for (int j = start; j < end; j++) {
                        this.finalMatrix[i][j] = Main.Convolution(i, j);
                    }
                }
            }

        }
    }

    public static void blockDistr(List<Pair<Integer, Integer>> blocks, int start, int end) {
        System.out.println(start + " " +  end);
        for (int b = start; b < end; b++) {
            for (int i = blocks.get(b).first; i < blocks.get(b).first + 5; i++) {
                for (int j = blocks.get(b).second; j < blocks.get(b).second + 5; j++) {
                    System.out.println("si aici");
                    finalMatrix[i][j] = Convolution(i, j);
                }
            }
        }
    }

    public static void blockConvolution() {
        Thread[] threads = new Thread[p];
        List<Pair<Integer, Integer>> blocks = new ArrayList<>();
        for (int i = 0; i < N; i += 5) {
            for (int j = 0; j < M; j += 5) {
                blocks.add(new Pair<>(i, j));
            }
        }

        int len = blocks.size();
        int cat = len / p;
        int rest = len % p;
        int last = 0;
        for (int i = 0; i < p; i++) {
            int start = last;
            int end = start + cat;
            if (i < rest) {
                start += 1;
            }
            last = end;
            int finalStart = start;
            threads[i] = new Thread(() -> blockDistr(blocks, finalStart, end));
            threads[i].start();
        }

        for (int i = 0; i < p; i++) {
            try {
                threads[i].join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }

    public static Pair<Integer, Integer> getPosition(int index) {
        int row = index / M;
        int col = index % M;
        return new Pair<>(row, col);
    }

    public static void linearDistr(int startIndex, int endIndex) {
        for (int i = startIndex; i < endIndex; i++) {
            Pair<Integer, Integer> position = getPosition(i);
            int ii = position.first;
            int jj = position.second;
            finalMatrix[ii][jj] = Convolution(ii, jj);
        }
    }

    public static void linearConvolution() {
        Thread[] threads = new Thread[p];
        int cat = (N * M) / p;
        int rest = (N * M) % p;
        int last = 0;
        for (int i = 0; i < p; i++) {
            int start = last;
            int end = start + cat;
            if (i < rest) {
                end += 1;
            }
            last = end;
            int finalEnd = end;
            threads[i] = new Thread(() -> linearDistr(start, finalEnd));
            threads[i].start();
        }

        for (int i = 0; i < p; i++) {
            try {
                threads[i].join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }

    public static void jumpingDistr(int index, int jump) {
        for (int i = index; i < N * M; i += jump) {
            Pair<Integer, Integer> position = getPosition(i);
            int ii = position.first;
            int jj = position.second;
            finalMatrix[ii][jj] = Convolution(ii, jj);
        }
    }

    public static void jumpingConvolution() {
        Thread[] threads = new Thread[p];
        for (int i = 0; i < p; i++) {
            int finalI = i;
            threads[i] = new Thread(() -> jumpingDistr(finalI, p));
            threads[i].start();
        }

        for (int i = 0; i < p; i++) {
            try {
                threads[i].join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }


    public static void main(String[] args) throws Exception {
        read("data0.txt");
        finalMatrix = new int[N][M];

        p = 2;

        offset = (n - 1) / 2;
        System.out.println(p);
        long startTime = System.nanoTime();

        if (p == 1)
            sequentialConvolution();
        else {
            //parallelConvolution();
            //blockConvolution();
            //linearConvolution();
            jumpingConvolution();
        }

        long endTime = System.nanoTime();
        double difference = (endTime - startTime) / 1E6;
        System.out.println(difference);

        write("output.txt", finalMatrix);

        if (checkAnswer() == false) {
            System.out.println("Tests failed\n");
        } else {
            System.out.println("Tests passed\n");
        }
    }
}

class Pair<A, B> {
    public A first;
    public B second;

    public Pair(A first, B second) {
        this.first = first;
        this.second = second;
    }
}