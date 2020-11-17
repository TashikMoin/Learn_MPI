#include <stdio.h>
#include <mpi.h>
#include<unistd.h>


int main(int argc, char **argv) 
{
    MPI_Init(&argc, &argv); 
    int Rank , X = 0 , Y = 0 ;
    int Total_Processes;
    MPI_Request Request;
    MPI_Comm_rank(MPI_COMM_WORLD, &Rank); 
    MPI_Comm_size(MPI_COMM_WORLD, &Total_Processes);

    if( Rank == 0 )
    { 
        //blocking
        printf("\nProcess # 0 is doing some work and have not started sending data \n") ;
        sleep(10) ;
        printf("\nProcess # 0 started sending data to process # 1\n") ;
        MPI_Send(&X, 1 , MPI_INT, 1 , 0 , MPI_COMM_WORLD);
        printf("\nProcess # 0 has sent the data to Process # 1 using MPI_Send and Process # 1 has received it\n") ;
    }
    else 
    {
        // blocking
        printf("\nProcess # 1 is ready to receive data from Process # 0 but data is not sent yet so process # 1 is blocked\n") ;
        MPI_Recv(&X, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("\nProcess # 1 has finally received the data \n") ;
    } 

    MPI_Finalize(); 
}

/* 
    The advantage of blocking communication is that there is no chance of a race condition. If we would have used asychronous variants of
    MPI_send and MPI_recv that is MPI_Isend and MPI_Irecv then there's a chance of race race condition. There is a separate program written
    for Race condition.
*/