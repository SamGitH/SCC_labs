
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
 
#define TEST_NUMBER (1000000000ULL)
double rand_point(void) { return rand() / (double)RAND_MAX; }
#define ROOT (0)
 
int rand_inside(void) {
    double x = rand_point(), y = rand_point();
    
    return ( x * x + y * y ) <= 1.0;
}
 
int main(int argc, char ** argv) {
    int rank, ret;
    unsigned long long int i, hits = 0;
    srand(time(NULL));
    
    ret = MPI_Init(&argc, &argv);
    if ( ret != MPI_SUCCESS ) {
        fprintf(stderr, "Can't init MPI!\n");
        MPI_Abort(MPI_COMM_WORLD, ret);
    }
    
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if ( rank == 0 ) {
        int numWorkers;
        MPI_Status st;
        double hitsSum = 0.;
        
        MPI_Comm_size(MPI_COMM_WORLD, &numWorkers);
        if ( --numWorkers < 1 ) {
            fprintf(stderr, "No workers to do job!\n");
            MPI_Abort(MPI_COMM_WORLD, 1);
        }
        
        for ( i = 0; i < numWorkers; ++i ) {
            MPI_Recv(&hits, 1, MPI_UINT64_T, i + 1, 0, MPI_COMM_WORLD, &st);
            hitsSum += hits;
        }
        
        printf("Pi = %f\n", 4.0 * hitsSum / ((double)TEST_NUMBER * numWorkers));
    }
    else {
        for ( i = 0; i < TEST_NUMBER; ++i )
            hits += rand_inside();
        MPI_Send(&hits, 1, MPI_UINT64_T, ROOT, 0, MPI_COMM_WORLD);
    }
    
    MPI_Finalize();
    return 0;
}
