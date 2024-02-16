#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
#include <vector>
#include <barrier>
#define p 1

using namespace std;
using namespace std::chrono;

ifstream fin("../data0.txt");
ofstream fout("../output.txt");


int N, M, n, m;
vector< vector<int> > matrix;
vector< vector<int> > kernel;
vector< vector<int> > finalMatrix;
vector< vector<int> > answerMatrix;
std::barrier b(p);

void read() {


     fin >> N >> M;
    matrix = vector<std::vector<int>>(N, std::vector<int>(M));

    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++) {
            fin >> matrix[i][j];
        }

     fin >> n >> m;
    kernel = vector<std::vector<int>>(n, std::vector<int>(m));

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            fin >> kernel[i][j];
}

void readAnswer() {
    ifstream fin_ans("../answer0.txt");
    answerMatrix = vector<std::vector<int>>(N, std::vector<int>(M));

    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++) {
            fin_ans >> answerMatrix[i][j];
        }
}

void write() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++)
            fout << matrix[i][j] << " ";
        fout << endl;
    }

    fout.close();
}

int Convolution(int x, int y) {
    int output = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int ii = x - (n - 1) / 2 + i;
            int jj = y - (m - 1) / 2 + j;

            if (ii < 0) ii = 0;
            else if (ii >= N) ii = N - 1;

            if (jj < 0) jj = 0;
            else if (jj >= M) jj = M - 1;
            output += matrix[ii][jj] * kernel[i][j];
        }
    }
    return output;
}

void secventialConvolution() {
    int buffer[3][M];

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (i >= 3) {
                matrix[i-3][j] = buffer[(i-3)%3][j];
            }

            buffer[i%3][j] = Convolution(i, j);
        }
    }

    for (int j = 0; j < M; j++) {
        matrix[N-3][j] = buffer[1][j];
        matrix[N-2][j] = buffer[2][j];
        matrix[N-1][j] = buffer[0][j];
    }
}

void parallelDistr(int start, int end) {
    vector< vector<int> > buffer(end - start + 1, vector<int>(M));
    int bufferLine;
    for (int i = start; i < end; i++) {
        bufferLine = i - start;
        for (int j = 0; j < M; j++) {
            buffer[bufferLine][j] = Convolution(i, j);
        }
    }

    b.arrive_and_wait();

    for (int i = start; i < end; i++) {
        bufferLine = i - start;
        for (int j = 0; j < M; j++) {
            matrix[i][j] = buffer[bufferLine][j];
        }
    }
}

void parallelConvolution() {
    vector<thread> t;
    int start, end = 0, chunk, rest;
    chunk = N / p;
    rest = N % p;


    for (size_t i = 0; i < p; i++) {
        start = end;
        end = start + chunk;
        if (rest > 0) {
            end++;
            rest--;
        }
        thread thr = thread(parallelDistr, start, end);
        t.push_back(std::move(thr));
        start = end;
    }

    for (auto &th: t) {
        if (th.joinable())
            th.join();
    }
}

bool checkAnswer() {
    readAnswer();

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (matrix[i][j] != answerMatrix[i][j])
                return 0;
        }
    }
    return 1;
}


int main() {
    read();

    auto startTime = high_resolution_clock::now();

    if (p == 1)
        secventialConvolution();
    else {
        parallelConvolution();
    }

    auto endTime = high_resolution_clock::now();

    double difference = duration<double, milli>(endTime - startTime).count();

    cout << difference;

    write();

    if (!checkAnswer())
        //    cout << "Tests passed!\n";
        //else
        cout << "Tests failed!\n";

    return 0;
}
