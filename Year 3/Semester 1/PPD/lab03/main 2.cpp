#include <iostream>
#include <fstream>
#include <mpi.h>
#include <chrono>
using namespace std;
ifstream fin("../in0.txt");
ofstream fout("../out.txt");

const int k = 3, N = 1000, p = 8;
vector<vector<int>> kernel(k, vector<int>(k));
int matr[N][N], matrfin[N + p * 2][N], matraux[(N + p * 2)/p][N], rasp[N][N], raspaux[N][N];


bool checkAnswer() {
    ifstream ans("../answer.txt");
    ifstream out("../out.txt");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int x, y;
            ans >> x;
            out >> y;
            if (x != y)
                return false;
        }
    }
    return true;
}


int main() {
    auto tStart1 = std::chrono::high_resolution_clock::now();
    // Initialize the MPI environment
    MPI_Init(NULL, NULL);

    // Get the number of processes
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Get the rank of the process
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    // (1000 + 10)


    if (world_rank == 0) { // parent
        // 0) read the kernel and send to the kids
        for (int i = 0; i < k; i++) {
            for (int j = 0; j < k; j++) {
                fin >> kernel[i][j];
            }
        }
    }

    MPI_Bcast(&kernel[0][0], k * k, MPI_INT, 0, MPI_COMM_WORLD);

    if (world_rank == 0) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                fin >> matr[i][j];
            }
        }

        int cat = N / world_size, start, end;
        //creeaza matricea noua
        int i_matrfin = 0;
        start = 0;
        for (int i = 0; i < world_size; i++) {
            end = min(start + cat, N);
            //copiem liniile care trebuie prelucrate
            for (int j = start - 1; j <= end; j++) {
                for (int l = 0; l < N; l++) {
                    if (j == -1)
                        matrfin[i_matrfin][l] = matr[0][l];
                    else if (j == N)
                        matrfin[i_matrfin][l] = matr[N-1][l];
                    else
                        matrfin[i_matrfin][l] = matr[j][l];
                }
                i_matrfin++;
            }
            start = end;
        }
    }
    // (N + world_size * 2)*N/world_size
    //auto tStart2 = std::chrono::high_resolution_clock::now();
    MPI_Scatter(matrfin, (N + world_size * 2)*N/world_size, MPI_INT, matraux, (N + world_size * 2)*N/world_size, MPI_INT, 0,
                MPI_COMM_WORLD);


//    for (int i = 0; i < N/world_size + 2; i++) {
//        cout << "proces: " << world_rank << " ";
//
//        for (int j = 0; j < N; j++) {
//            cout << matraux[i][j] << ' ';
//        }
//        cout << endl;
//    }

    for (int i = 1; i < N/world_size + 1; i++) {
        for (int j = 0; j < N; j++) {
            //convolutie

            int output = 0;
            for (int a = 0; a < k; a++) {
                for (int b = 0; b < k; b++) {
                    int ii = i - 1 + a;
                    int jj = j - 1 + b;

                    if (ii < 0) ii = 0;
                    else if (ii >= N) ii = N - 1;

                    if (jj < 0) jj = 0;
                    else if (jj >= N) jj = N - 1;
                    output += matraux[ii][jj] * kernel[a][b];
                }
            }

            raspaux[i - 1][j] = output;
        }
    }

    MPI_Gather(raspaux, N * N / world_size, MPI_INT, rasp, N * N / world_size, MPI_INT, 0, MPI_COMM_WORLD);

    if (world_rank == 0) {
        auto tEnd = std::chrono::high_resolution_clock::now();

        double elapsedTimeMs = std::chrono::duration<double, std::milli>(tEnd - tStart1).count();
        cout << elapsedTimeMs << endl;


        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                fout << rasp[i][j] << ' ';
            }
            fout << endl;
        }

        fout.close();


        if (!checkAnswer()) {
            cout << "FAIL!!!!";
        } else {
            cout << "ANS VERIFIED!";
        }
    }

    MPI_Finalize();

    return 0;
}
