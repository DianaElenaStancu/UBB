#include <mpi.h>
#include <stdio.h>
#include <random>
#include <iostream>
using namespace std;

void printVector(int v[], int n) {
    for (int i = 0; i < n; i++) {
        cout << v[i] << " ";
    }
    cout << endl;
}

int main(int argc, char** argv) {
    const int n = 12;
    int a[n], b[n], c[n];
    MPI_Status status;

    // Initialize the MPI environment
    MPI_Init(NULL, NULL);

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    int* auxa = new int[n/world_size];
    int* auxb = new int[n/world_size];
    int* auxc = new int[n/world_size];

    if (world_rank == 0) {
        for (int i = 0; i < n; i++) {
            a[i] = rand() % 10;
            b[i] = rand() % 10;
        }
    }

    MPI_Scatter(a, n/world_size, MPI_INT, auxa, n/world_size, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(b, n/world_size, MPI_INT, auxb, n/world_size, MPI_INT, 0, MPI_COMM_WORLD);

    for (int i = 0; i < n/world_size; i++) {
        auxc[i] = auxa[i] + auxb[i];
    }

    MPI_Gather(auxc, n/world_size, MPI_INT, c, n/world_size, MPI_INT, 0, MPI_COMM_WORLD);

    if (world_rank == 0) {
        printVector(a, n);
        printVector(b, n);
        printVector(c, n);
    }

    MPI_Finalize();
}

//int main(int argc, char** argv) {
//    const int n = 10;
//    int a[n], b[n], c[n];
//    int start, end;
//    MPI_Status status;
//
//    // Initialize the MPI environment
//    MPI_Init(NULL, NULL);
//
//    // Get the number of processes
//    int world_size;
//    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
//
//    // Get the rank of the process
//    int world_rank;
//    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
//
//    if (world_rank == 0) { // I am master
//        for (int i = 0; i < n; i++) {
//            a[i] = rand() % 10;
//            b[i] = rand() % 10;
//        }
//
//        int cat, rest;
//        cat = n/(world_size - 1);
//        rest = n%(world_size - 1);
//        start = 0;
//        for (int i = 1; i < world_size; i++) {
//            end = start + cat;
//            if (rest > 0) {
//                end++;
//                rest--;
//            }
//
//            //printf("Trimit id-ului %d: %d si %d\n", i, start, end);
//            // transmitem in mod explicit start si end fiecarui copil
//            MPI_Send(&start, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
//            MPI_Send(&end, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
//            MPI_Send(a + start, end - start, MPI_INT, i, 0, MPI_COMM_WORLD);
//            MPI_Send(b + start, end - start, MPI_INT, i, 0, MPI_COMM_WORLD);
//
//            start = end;
//        }
//
//        for (int i = 1; i < world_size; i++) {
//            MPI_Recv(&start, 1, MPI_INT, i, 0, MPI_COMM_WORLD, &status);
//            MPI_Recv(&end, 1, MPI_INT, i, 0, MPI_COMM_WORLD, &status);
//            MPI_Recv(c + start, end-start, MPI_INT, i, 0, MPI_COMM_WORLD, &status);
//        }
//
//        printVector(a, n);
//        printVector(b, n);
//        printVector(c, n);
//
//
//    } else { // I am worker
//        MPI_Recv(&start, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
//        MPI_Recv(&end, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
//        MPI_Recv(a + start, end-start, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
//        MPI_Recv(b + start, end-start, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
//
//        printf("Sunt id-ului %d: %d si %d\n", world_rank, start, end);
//
//        for (int i = start; i < end; i++) {
//            c[i] = a[i] + b[i];
//        }
//
//        MPI_Send(&start, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
//        MPI_Send(&end, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
//        MPI_Send(c + start, end - start, MPI_INT, 0, 0, MPI_COMM_WORLD);
//    }
//
//    // Finalize the MPI environment.
//    MPI_Finalize();
//}