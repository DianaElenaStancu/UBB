#include <iostream>
#include <fstream>
#include <mpi.h>

using namespace std;
ifstream fin("../in0.txt");
ofstream fout("../out.txt");

int k = 3, N = 1000;
vector<vector<int>> kernel(k, vector<int>(k));
vector<vector<int>> answer(N, vector<int>(N));

bool checkAnswer(){
    ifstream ans("../answer.txt");
    ifstream out("../out.txt");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int x, y;
            ans >> x; out >> y;
            if (x != y)
                return false;
        }
    }
    return true;
}


int main() {

    // Initialize the MPI environment
    MPI_Init(NULL, NULL);

    // Get the number of processes
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Get the rank of the process
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    if (world_rank == 0) { // parent
        // 0) read the kernel and send to the kids
        for (int i = 0; i < k; i++) {
            for (int j = 0; j < k; j++) {
                fin >> kernel[i][j];
            }
        }
    }

    MPI_Bcast(&kernel[0][0], k*k, MPI_INT, 0, MPI_COMM_WORLD);

    int cat = N/(world_size - 1); // se garanteaza ca se imparte exact
    int buffer[cat + 2][N];
    MPI_Status status;
    if (world_rank == 0) {
        auto tStart1 = std::chrono::high_resolution_clock::now();


        // 1) citeste din fisier cate N/(p-1) linii
        // 2) trimitem procesului i liniile citite
        // 3) i = i + 1

        //pt i = 1
        for (int j = 0; j < cat + 1; j++) {
            for (int l = 0; l < N; l++) {
                fin >> buffer[j + 1][l];
            }
        }

        for (int l = 0; l < N; l++) {
            buffer[0][l] = buffer[1][l];
        }

        MPI_Send(buffer, (cat + 2)*N, MPI_INT, 1, 0, MPI_COMM_WORLD);


        for (int i = 2; i < world_size; i++) {
            for (int j = 0; j < 2; j ++) {
                for (int l = 0; l < N; l++) {
                    buffer[j][l] = buffer[cat + j][l];
                }
            }

            for (int j = 0; j < cat; j++) {
                for (int l = 0; l < N; l++) {
                    fin >> buffer[j + 2][l];
                }
            }

            MPI_Send(buffer, (cat+2)*N, MPI_INT, i, 0, MPI_COMM_WORLD);
        }

        int rasp[cat][N];
        for (int i = 1; i < world_size; i++) {
            MPI_Recv(rasp, cat*N, MPI_INT, i, 0, MPI_COMM_WORLD, &status);

            for (int j = 0; j < cat; j++) {
                for (int l = 0; l < N; l++) {
                    fout << rasp[j][l] << " ";
                }
                fout << endl;
            }
        }

        if(!checkAnswer()) {
            cout << "FAIL!!!!";
        } else {
            cout << "ANS VERIFIED!";
        }

        auto tEnd = std::chrono::high_resolution_clock::now();
        double elapsedTimeMs = std::chrono::duration<double, std::milli>(tEnd - tStart1).count();
        cout << elapsedTimeMs << endl;
    } else {
        // primeste date de la procesul 0
        //
        MPI_Recv(buffer, (cat+2)*N, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);

        int rasp[cat][N];
        for (int i = 1; i < cat + 1; i++) {
            for (int j = 0; j < N; j++) {
                //convolutie

                int output = 0;
                for (int a = 0; a < k; a++) {
                    for (int b = 0; b < k; b++) {
                        int ii = i - 1 + a;
                        int jj = j - 1 + b;

                        if (jj < 0) jj = 0;
                        else if (jj >= N) jj = N - 1;
                        output += buffer[ii][jj] * kernel[a][b];
                    }
                }

                rasp[i-1][j] = output;
            }
        }

//        for (int i = 0; i < cat; i++) {
//            cout << "//" << world_rank << "//" << i << ": ";
//            for (int j = 0; j < N; j++) {
//                cout << rasp[i][j] << " ";
//            }
//            cout << endl;
//        }

        MPI_Send(rasp, cat*N, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }




    MPI_Finalize();

    return 0;
}
