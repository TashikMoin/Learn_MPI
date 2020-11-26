#include <stdio.h>
#include <mpi.h>
#include<unistd.h>
// run this code with 2 processes

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
        printf("\nProcess # 0 is busy in doing its work\n") ;
        sleep(10) ;
        MPI_Isend( &X , 1 , MPI_INT , 1 , 0 , MPI_COMM_WORLD , &Request ); 
        printf("\n... Process # 0 has sent data and is executing the remaining code ... \n") ;
    }
    else 
    {
        printf("\nProcess # 1 is ready to receive data but process # 0 will take 10 seconds more to send it\n") ;
        printf("\nProcess # 1 would have waited for 10 seconds (blocked) if we would have used MPI_Send and MPI_Recv\n") ;
        printf("\nProcess # 1 will not wait this time because we have used aynchronous version of MPI_Send and MPI_Recv --> ISend/IRecv\n") ;
        MPI_Irecv( &X , 1 , MPI_INT , 0 , 0 , MPI_COMM_WORLD , &Request ); 
        printf("\nCode After MPI_Irecv\n") ;
    } 

    MPI_Finalize(); 
}

/* 
MPI_STATUS_IGNORE -->  MPI_STATUS_IGNORE informs MPI to not fill an MPI_Status, which saves some time.
MPI_Isend and MPI_Irecv works asynchronously which means while receiving, MPI_Irecv will not wait for other process to send it
data but it will go ahead and execute remaining code after MPI_Irecv. It will automatically get the value when the value is sent
to it. we can check the value of flag variable to confirm if the value is sent or not.



The reason that MPI_Irecv does not wait till the complete data transfer just like MPI_recv is because we used
MPI_Isend and MPI_Irecv and these functions are non-blocking(Asynchronous). If we would have used MPI_Send and 
MPI_Recv here, then MPI_recv would have waited till X is received by process # 1 and this wait is called "blocking".

*/
