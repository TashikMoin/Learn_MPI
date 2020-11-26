// collective communication

#include <stdio.h>
#include <mpi.h>
#include<unistd.h>

int main(int argc, char **argv) 
{
    MPI_Init(&argc, &argv); 
    int Rank , A[100000] = {0} ;

    int Global_Sum_Result = 0 , Local_Sum_Result = 0 ;
    int Total_Processes ;
    MPI_Request Request ;
    MPI_Status Status ;
    MPI_Comm_rank(MPI_COMM_WORLD, &Rank); 
    MPI_Comm_size(MPI_COMM_WORLD, &Total_Processes);

    if( Rank == 0 )
    { 
        for( int i = 0 ; i < 100000 ; ++i )
        {
            A[i] = i + 1;
        }

    }

    MPI_Bcast(&A, 100000, MPI_INT, 0, MPI_COMM_WORLD);  
    for( int i = 0 ; i < 100000 ; ++i )
    {
        Local_Sum_Result = i + 1 ; // local sum of every process
    }

    MPI_Reduce(&Local_Sum_Result, &Global_Sum_Result, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    // sum of all local sums without any race condition.
    if( Rank ==0 )
    {
        printf("The Sum = %d\n", Global_Sum_Result) ;
    }

    MPI_Finalize(); 
}

/*
int MPI_Reduce(Buffer, Result_buffer, Total_Values_Count, Datatype, Reduction_operation, Sender/Master/Root , Communicator);
*/

