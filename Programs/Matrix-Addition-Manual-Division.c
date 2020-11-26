// Run Executable with 3 processes ( better to use N Processes for NXN square Matrix ) --> mpirun -np 3 ./MPI

#include <stdio.h>
#include <mpi.h>

const int M = 3; 
const int N = 3; 

  
void print(int Matrix[M][N]) 
{ 
    int i, j; 
    printf("\n");
    for( i = 0 ; i < M ; ++i )
    {
        for( j = 0 ; j < N ; ++j )
        {
            printf("  %d " , Matrix[i][j] );
        }
        printf("\n") ; 
    }
} 

int main(int argc, char **argv) 
{
    MPI_Init(&argc, &argv); 
    int Rank , x = 0 , y = 0 ;
    int Total_Processes , FROM = 0 , TO = 0 ;
    int *ptrA = NULL , *ptrB = NULL , *ptrC = NULL, *baseA = NULL, *baseB = NULL, *baseC = NULL ;
    MPI_Comm_rank(MPI_COMM_WORLD, &Rank); 
    MPI_Comm_size(MPI_COMM_WORLD, &Total_Processes);
    int Average = (M*N) / Total_Processes ;
    int MatrixA[3][3] = { 0 , 1 , 2 , 3 , 4 , 5 , 6 , 7 , 8 } ; // creating matrices for sum
    int MatrixB[3][3] = { 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 } ;
    int MatrixC[3][3] ; // resultant matrix
    baseA = *MatrixA ;
    baseB = *MatrixB ;
    baseC = *MatrixC ; 
    ptrA = *MatrixA ;
    ptrB = *MatrixB ;
    ptrC = *MatrixC ;
    if( Rank == 0 ) // if master process, then divide the work among other processes and do your work also.
    { 
        int i = 1 , Temp ; 
        FROM = 0 ;
        TO = Average-1 ; 
        while( FROM <= TO )
        {
            ptrA = ( ( baseA + ( (FROM/N) * N + (FROM%N) )  ) ) ;
            ptrB = ( ( baseB + ( (FROM/N) * N + (FROM%N) )  ) ) ;
            ptrC = ( ( baseC + ( (FROM/N) * N + (FROM%N) )  ) ) ;
            *ptrC = *ptrA + *ptrB ;
            FROM++ ;
            /* 
            ( baseA + ( (FROM/N) * N + (FROM%N) ) is a row major formula to access a N dimentional array linearly as
            a 1D array. here (FROM/N) and (FROM%N) are same as i,j in Matrix[i][j] where N is the total columns.
            FROM --> Current value box index for a N dimentional --> 1D form.
            N --> Total Columns
            Original Row Major Formula --> Base_Address + ( i * total_col + j ) * data_type_size
            Base_Address + [ (index/tot_columns) * total_col + (index%tot_columns) ] * data_type_size
            */
        }
        Temp = FROM ;
        TO = TO + Average ;
        while( i < Total_Processes ) // master thread dividing the work
        {
            MPI_Send(&FROM, 1 , MPI_INT, i , 0 , MPI_COMM_WORLD);
            MPI_Send(&TO, 1 , MPI_INT, i , 0 , MPI_COMM_WORLD);
            FROM = FROM + Average ; 
            TO = TO + Average ;
            ++i ;
        }
        FROM = Temp ; // so that we can start receiving from the process 1 --- N
        i = 1 ;
        while( i < Total_Processes )
        { 
            // ( baseA + ( (FROM/N) * N + (FROM%N) )  ) represent current collection of average blocks starting address
            MPI_Recv(( ( baseC + ( (FROM/N) * N + (FROM%N) )  ) ) 
            , 3, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE); // i = source process
            FROM = FROM + Average ; 
            ++i;
        }

    }
    else // if not master process
    {
        MPI_Recv(&FROM, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(&TO, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        int Temp = FROM ;
        while( FROM <= TO )
        {
            ptrA = ( ( baseA + ( (FROM/N) * N + (FROM%N) )  ) ) ;
            ptrB = ( ( baseB + ( (FROM/N) * N + (FROM%N) )  ) ) ;
            ptrC = ( ( baseC + ( (FROM/N) * N + (FROM%N) )  ) ) ;
            *ptrC = *ptrA + *ptrB ;
            FROM++ ; 
        }
        MPI_Send(( baseC + ( (Temp/N) * N + (Temp%N) )  ), Average , MPI_INT, 0 , 0 , MPI_COMM_WORLD); 
        // sending output values back to the master process after performing arithmetic operations.
    }
    MPI_Barrier(MPI_COMM_WORLD) ;
    if( Rank == 0 )
    {
        printf("\nResultant Matrix \n\n ") ; 
        print(MatrixC) ;
        printf("\n\n");
    }
    MPI_Finalize(); 
}
