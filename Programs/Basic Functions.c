#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv) 
{
   int Rank, Total_Processes;
   MPI_Init(&argc, &argv); 
   int arr[5] = { 1 , 2 , 3 , 4 , 5 } ;
   MPI_Comm_rank(MPI_COMM_WORLD, &Rank); 
   // MPI_Comm_size(MPI_COMM_WORLD, &Total_Processes); // Used to get total processes in a communicator.
   // An MPI function that returns current process's id/rank MPI_Comm_rank(communicator's_name, rank_variable_in_which_id_will_be_assigned)
   // printf("I am process # %d \n",Rank) ; 
   if( Rank == 0 )
   {
       MPI_Send(&arr, 5 , MPI_INT, 1 , 0 , MPI_COMM_WORLD);
   }
   else if( Rank == 1 )
   {
       int Square_Arr[5] = {0} ;
       MPI_Recv(&Square_Arr, 5, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
       int i = 0 ;
       printf("\nOriginal Array Received By Process # 1 \n");
       printf("\nAfter Squaring Original Array --> ") ;
       while( i < 5 )
       {
           Square_Arr[i] = Square_Arr[i] * Square_Arr[i] ;
           printf(" %d ",Square_Arr[i]) ;
           i++;
       }
       printf("\n");
   }
   else
   {
       MPI_ABORT(1); // used for terminating MPI execution environment.
   }
   
   MPI_Finalize(); 
}

   

/*

                                          MPI_COMM_WORLD
MPI_COMM_WORLD --> It is a Global communicator/container that contains all the processes that are executing the program.
// In MPI_COMM_WORLD every process of the program can communicate with any other process of the program.

The MPI_COMM_WORLD indicates that the operation is done on the global communicator that encapsulates every single process 
of the current run. We can also make our own custom communicators. For the moment, we will stick with calling MPI on the 
WORLD communicator for this program.

                                             Rank
A rank of a process is same as process id. A rank number is in range of [ 0 - (total processes in communicator - 1) ]. The
rank of first process is 0, second process has rank 1 and so on...


                                        P2P / Blocking Communication
The most basic forms of P2P communication are called blocking communications. The process sending a message will be waiting 
until the process receiving has finished receiving all the information. This is the easiest form of communications but not 
necessarily the fastest. P2P communication means that when a process sends or receive information, it has to wait for the 
transmission to end to get back to what it was doing. In some applications, this can be terribly limiting.

MPI_Send(buffer_starting_address, total_no_of_blocks_of_given_type, mpi_type_name, rank_of_receiver_process, tag, Communicator);

MPI_Recv(buffer_starting_address, total_no_of_blocks_of_given_type, mpi_type_name, rank_of_source_process, tag, Communicator, status_structure);

As you can see, there is an additional status parameter in recv function. Let's ignore this by putting the value MPI_STATUS_IGNORE.
It is nothing but a structure of some information that can be used in some case. This information that is encapsulated inside the
status block includes,
struct MPI_Status {
  int MPI_SOURCE;
  int MPI_TAG;
  int MPI_ERROR;
  int _cancelled;
  size_t _ucount;
};

*/