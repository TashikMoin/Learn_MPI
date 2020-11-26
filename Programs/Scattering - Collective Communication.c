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

    if( Rank == 0 )
    {
        for(int i = 0 ; i < 3 ; ++i )
        {
            printf(" %d ", Squares[i]) ;
        }
        printf("\n\n\n") ;
    }
    else if( Rank == 1 )
    {
        for(int i = 0 ; i < 3 ; ++i )
        {
            printf(" %d ", Squares[i]) ;
        }
        printf("\n\n\n") ;
    }
    else if( Rank == 2)
    {
        for(int i = 0 ; i < 3 ; ++i )
        {
            printf(" %d ", Squares[i]) ;
        }
        printf("\n\n\n") ; 
    } 

    MPI_Finalize(); 
}

/*

MPI_Scatter(
    void* send_data,
    int send_count,
    MPI_Datatype send_datatype,
    void* recv_data,
    int recv_count,
    MPI_Datatype recv_datatype,
    int root,
    MPI_Comm communicator
    )

The first parameter, send_data, is an array of data that resides on the root process. The second and third 
parameters, send_count and send_datatype, dictate how many elements of Numbers specific MPI Datatype will be sent 
to each process. If send_count is one and send_datatype is MPI_INT, then process zero gets the first integer 
of the array, process one gets the second integer, and so on. If send_count is two, then process zero gets 
the first and second integers, process one gets the third and fourth, and so on. In practice, send_count is 
often equal to the number of elements in the array divided by the number of processes.

The receiving parameters of the function prototype are nearly identical in respect to the sending parameters. 
The recv_data parameter is Numbers buffer of data that can hold recv_count elements that have Numbers datatype of recv_datatype. 
The last parameters, root and communicator, indicate the root process that is scattering the array of data and the 
communicator in which the processes reside.

Note: MPI_Scatter & MPI_Gather are blocking functions and they their non-blocking version is also available that are,
MPI_IScatter & MPI_IGather.


*/

