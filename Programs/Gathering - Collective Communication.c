// collective communication
// Run this code with 3 processes.
#include <stdio.h>
#include <mpi.h>
#include<unistd.h>

int main(int argc, char **argv) 
{
    MPI_Init(&argc, &argv); 
    int Rank , Numbers[9] = { 0 } ;
    int Squares[9] = {0} ;
    int Total_Processes ;
    MPI_Request Request ;
    MPI_Status Status ;
    MPI_Comm_rank(MPI_COMM_WORLD, &Rank);  
    MPI_Comm_size(MPI_COMM_WORLD, &Total_Processes);
    if ( Rank == 0 )
    {
        for( int i = 0 ; i < 9 ; ++i )
        {
            Numbers[i] = i + 1 ; // initializing the array.
        }
    }
    MPI_Scatter( &Numbers, 3, MPI_INT, &Squares, 3, MPI_INT, 0, MPI_COMM_WORLD) ; // dividing 3 , 3 ,3 for each process
    /* 
    Every process will receive values in the first 3 indices of the square array. The scatter function
    will divide the original(Numbers) array within total processes but when those processes will be receiving
    those values, they will start receiving values from the 0th index of the receiving buffer
    */
    for(int i = 0 ; i < 3 ; ++i )
    {
        Squares[i] = Squares[i] * Squares[i] ;
    }
    /* 
    This loop will be executed by all the processes including the 0th/master/root process and each process has scattered values
    inside the recieving buffer from 0th index  - - >   total_division / average / per process division. This loop will square
    the complete original array that was scattered and divided among other processes and will store the squared result inside the
    square array.
    */

    MPI_Gather( &Squares, 3, MPI_INT, &Numbers, 3, MPI_INT, 0, MPI_COMM_WORLD) ;

    if( Rank == 0 ) 
    // since the values were gathered inside 0th/root/master process so the final output should be printed by process with rank 0
    {
        for( int i = 0 ; i < 9 ; ++i )
        {
            if( i % 3 == 0 )
            {
                printf("\n") ;
            }
            printf(" %d ", Numbers[i] ) ;
        }
        printf("\n\n");
    }

    MPI_Finalize(); 
}

/*

MPI_Gather is the inverse of MPI_Scatter. Instead of spreading elements from one process to many processes, 
MPI_Gather takes elements from many processes and gathers them to one single process. 

MPI_Gather(
    void* send_data,
    int send_count,
    MPI_Datatype send_datatype,
    void* recv_data,
    int recv_count,
    MPI_Datatype recv_datatype,
    int root,
    MPI_Comm communicator
    )


The MPI_Gather takes input similar to MPI_Scatter. The sender becomes the receiver and receiver becomes sender. In MPI_Gather,
all other processes sents value to the root process whose id is sent inside the Gather function. The root process then start
gathering values from 0th index of its buffer and receive values till n where n is the total_division*total_processes. In our
example, the gather function gathers all the values like this,

0 - > 2 0th process
3 - > 5 1st process
6 - > 8 2nd process
and so on...

Note: MPI_Scatter & MPI_Gather are blocking functions and they their non-blocking version is also available that are,
MPI_IScatter & MPI_IGather.

*/

