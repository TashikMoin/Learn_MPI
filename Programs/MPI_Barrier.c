#include <stdio.h>
#include <mpi.h>
#include<unistd.h>
// run this code with 2 processes

int main(int argc, char **argv) 
{
    MPI_Init(&argc, &argv); 
    int Rank , X = 0 ;
    int Total_Processes ;
    int Flag ;
    MPI_Request Request ;
    MPI_Status Status ;
    MPI_Comm_rank(MPI_COMM_WORLD, &Rank); 
    MPI_Comm_size(MPI_COMM_WORLD, &Total_Processes);
    if( Rank == 0 )
    {
        sleep(10);
        printf("\nProcess # 0 has finished work\n");
    }

    printf("\n... Process # %d waiting for other processes to complete their work before the barrier (waiting point)\n",Rank) ;
    MPI_Barrier(MPI_COMM_WORLD); // A common meeting point for all processes --> Barrier.
    /* 
    All other processes will be waiting for other processes (Process 0 in our case) to complete their work to further proceed.
    MPI_Barrier(MPI_COMM_WORLD); takes a communicator/group of processes on which we are applying the barrier.
    */
    printf("\n... Process # %d doing some work After Barrier... \n", Rank) ;
    MPI_Finalize(); 
}
