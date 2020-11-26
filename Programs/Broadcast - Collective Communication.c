// collective communication

#include <stdio.h>
#include <mpi.h>
#include<unistd.h>

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
        X=10;
    }

    MPI_Bcast(&X, 1, MPI_INT, 0, MPI_COMM_WORLD); 
    /* 
    No need for a recv / send while broadcasting. Broadcast function should be called by every process present inside the communicator
    in which we want to establish the collective communication. If we would have called Bcast inside else part then it would not have worked
    because broadcasting means everyone should be included. It is a network communication to send same messages to everyone at the same time.
    The time complexity of normal send recv function is O( n ) however in broadcasting, when the root process or the sender process calls the
    bcast function then it only send messages to other parent processes only and not to their children processes. The data is sent to the
    child processes by their parent processes and this is continue till the leaf child and hence the time complexity is reduced to nLogN.
    see this link for visualization of broadcasting,
    https://www.codingame.com/playgrounds/349/introduction-to-mpi/broadcasting

    Using broadcast, we can avoid extra send/recv calls, reduce lines of code and is also of nLogN complexity.
    */
    printf("\nThe Value Of X In Process # %d = %d\n" , Rank , X) ;

    MPI_Finalize(); 
}


