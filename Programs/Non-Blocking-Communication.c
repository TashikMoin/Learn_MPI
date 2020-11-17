// Compile with --> mpicc -o MPI MPI.c
// Run Executable with 3 processes ( better to use N Processes for NXN square Matrix ) --> mpirun -np 3 ./MPI

#include <stdio.h>
#include <mpi.h>
#include<unistd.h>


int main(int argc, char **argv) 
{
    MPI_Init(&argc, &argv); 
    int Rank , X = 0 , Y = 0 ;
    int Total_Processes;
    MPI_Request Request;
    // MPI_Status  Status; 
    // --> No need because we have not using MPI_Send and MPI_Recv. We can also avoid it in MPI_Send and MPI_Recv by MPI_STATUS_IGNORE.
    MPI_Comm_rank(MPI_COMM_WORLD, &Rank); 
    MPI_Comm_size(MPI_COMM_WORLD, &Total_Processes);

    if( Rank == 0 )
    { 
        MPI_Isend( &X , 1 , MPI_INT , 1 , 0 , MPI_COMM_WORLD , &Request ); 
        printf("\n... Process # 0 has sent data and is executing the remaining code ... \n") ;
    }
    else 
    {
        printf("\nProcess # 1 waiting for the data\n") ;
        sleep(10) ;
        MPI_Irecv( &X , 1 , MPI_INT , 0 , 0 , MPI_COMM_WORLD , &Request ); 
        printf("\n... Data received by Process # 1 ...\n") ;
        printf("\nX value in process # 1 = %d\n", X ) ;
    } 

    MPI_Finalize(); 
}

/* 
MPI_STATUS_IGNORE -->  MPI_STATUS_IGNORE informs MPI to not fill an MPI_Status, which saves some time.
MPI_Isend and MPI_Irecv works asynchronously which means that they do not wait for complete sending/recieving they will move ahead and
will execute other code written after these function calls.

The output of above code is,

Process # 1 waiting for the data
... Process 0 has sent data and is executing the remaining code ...
... Data received by Process # 1 ...
X value in process # 1 = 0


The reason that MPI_Isend does not wait till the complete data transfer just like MPI_send is because we used
MPI_Isend and MPI_Irecv and these functions are non-blocking(Asynchronous). If we would have used MPI_Send and 
MPI_Recv here, the send will wait until X is received by process # 1 and this wait is called "blocking".

*/