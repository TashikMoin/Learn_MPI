#include <stdio.h>
#include <mpi.h>
#include<unistd.h>
// run this code with 2 processes

int main(int argc, char **argv) 
{
    MPI_Init(&argc, &argv); 
    int Rank , X = 0 ;
    int Total_Processes ;
    MPI_Request Request ;
    MPI_Status Status ;
    MPI_Comm_rank(MPI_COMM_WORLD, &Rank); 
    MPI_Comm_size(MPI_COMM_WORLD, &Total_Processes);

    if( Rank == 0 )
    { 
        printf("\nProcess # 0 is busy in doing its work\n") ;
        sleep(10) ;
        X = 10;
        MPI_Isend( &X , 1 , MPI_INT , 1 , 0 , MPI_COMM_WORLD , &Request ); 
        printf("\nBefore MPI_Wait\n");
        printf("\n... Process # 0 has sent data and is executing the remaining code ... \n") ;
    }
    else 
    {
        printf("\nProcess # 1 is ready to receive data but process # 0 will take 10 seconds more to send it\n") ;
        printf("\nProcess # 1 would have waited for 10 seconds (blocked) if we would have used MPI_Send and MPI_Recv\n") ;
        printf("\nProcess # 1 will not wait this time because we have used aynchronous version of MPI_Send and MPI_Recv --> ISend/IRecv\n") ;
        MPI_Irecv( &X , 1 , MPI_INT , 0 , 0 , MPI_COMM_WORLD , &Request ); 
        MPI_Wait(&Request, &Status);
        printf("\nCode After MPI_Irecv\n") ;
        printf("\nReceived Value Of X = %d\n", X) ; // if MPI_Wait wis not used then X will be 0
    } 

    MPI_Finalize(); 
}

    /*
    using MPI_Wait(&Request, &Status); after MPI_Irecv is same as using MPI_recv (blocking) variant.

    it is necessary to either wait or test when using MPI_Isend and MPI_Irecv functions otherwise we will not receive the values passed
    by other processes. If we do not wait or test, we wil get local value of the process's recieving value and not the actual passed data.
    MPI_Wait(&Request, &Status); takes the request and status objects as parameter and waits until 'that' request is finished. however,
    there is another waiting function,
    MPI_Waitany(Array_Size/Total_Requests, Array_Of_Requests[], Index_Of_Request_That_Is_Completed, Status);

    The difference is that, MPI_Wait wait for a single request to complete but ,
    let say if there are multiple sends and recieve function calls then MPI_WaitAny wait for the first request that is completed
    and does not wait for other requests and it returns the index of request that is completed.
    */