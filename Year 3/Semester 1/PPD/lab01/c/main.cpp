#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>

#define N 10000
#define M 10
#define n 5
#define m 5
#define p 16

int matrix[N][M];
int kernel[n][m];
int finalMatrix[N][M];
int answerMatrix[N][M];

// vector<vector<int>> matrix;
// vector<vector<int>> kernel;
// vector<vector<int>> finalMatrix;
// vector<vector<int>> answerMatrix;

using namespace std;
using namespace std::chrono;

ifstream fin("../data3.txt");
ofstream fout("../output.txt");

void read() {

    // kernel = vector<std::vector<int>>(n, std::vector<int>(m));
    // matrix = vector<std::vector<int>>(N, std::vector<int>(M));
    // finalMatrix = vector<std::vector<int>>(N, std::vector<int>(M));

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            fin >> kernel[i][j];

    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++) {
            fin >> matrix[i][j];
        }
}

void readAnswer() {
    ifstream fin_ans("../answer3.txt");

    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++) {
            fin_ans >> answerMatrix[i][j];
        }
}

void write() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++)
            fout << finalMatrix[i][j] << " ";
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

    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            finalMatrix[i][j] = Convolution(i, j);
}

void parallelDistr(int start, int end) {
    if (N > M) // mai multe linii decat coloane
    {
        for (int i = start; i < end; i++)
            for (int j = 0; j < M; j++)
                finalMatrix[i][j] = Convolution(i, j);
    } else // mai multe coloane decat linii
    {
        for (int i = 0; i < N; i++)
            for (int j = start; j < end; j++)
                finalMatrix[i][j] = Convolution(i, j);
    }
}

void parallelConvolution() {
    vector<thread> t;

    int start, end = 0, chunk, rest;
    if (N > M) {
        chunk = N / p;
        rest = N % p;
    } else {
        chunk = M / p;
        rest = M % p;
    }

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
            if (finalMatrix[i][j] != answerMatrix[i][j])
                return 0;
        }
    }
    return 1;
}

void blockDistr(vector<pair<int, int>> blocks, int start, int end) {
    for (int b = start; b < end; b++) {
        for (int i = blocks[b].first; i < blocks[b].first + 5; i++) {
            for (int j = blocks[b].second; j < blocks[b].second + 5; j++) {
                finalMatrix[i][j] = Convolution(i, j);
            }
        }
    }
}

void blockConvolution() {
    vector<thread> t;
    vector<pair<int, int>> blocks;
    for (int i = 0; i < N; i += 5) {
        for (int j = 0; j < M; j += 5) {
            blocks.push_back({i, j});
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
        thread thr = thread(blockDistr, blocks, start, end);
        t.push_back(std::move(thr));
    }


    for (auto &th: t) {
        if (th.joinable())
            th.join();
    }
}

pair<int, int> getPosition(int index) {
    int row = index / M;
    int col = index % M;

    return {row, col};
}

void linearDistr(int start, int end) {
    for (int i = start; i < end; i++) {
        pair<int, int> position = getPosition(i);
        int ii = position.first;
        int jj = position.second;
        finalMatrix[ii][jj] = Convolution(ii, jj);
    }
}

void linearConvolution() {
    vector<thread> t;
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
        thread thr = thread(linearDistr, start, end);
        t.push_back(std::move(thr));
    }

    for (auto &th: t) {
        if (th.joinable())
            th.join();
    }
}

void jumpingDistr(int index, int jump) {
    for (int i = index; i < N * M; i += jump) {
        pair<int, int> position = getPosition(i);
        int ii = position.first;
        int jj = position.second;
        finalMatrix[ii][jj] = Convolution(ii, jj);
    }
}

void jumpingConvolution() {
    vector<thread> t;
    for (int i = 0; i < p; i++) {
        thread thr = thread(jumpingDistr, i, p);
        t.push_back(std::move(thr));
    }

    for (int i = 0; i < p; i++) {
        for (auto &th: t) {
            if (th.joinable())
                th.join();
        }
    }
}

int main() {
    read();

    auto startTime = high_resolution_clock::now();

    if (p == 1)
        secventialConvolution();
    else {
        //parallelConvolution();
        //blockConvolution();
        //linearConvolution();
        jumpingConvolution();
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
