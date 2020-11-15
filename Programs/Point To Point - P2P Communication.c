#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv) 
{
   int ;
   MPI_Init(&argc, &argv);
   
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


                                          P2P Communication
The most basic forms of P2P communication are called blocking communications. The process sending a message will be waiting 
until the process receiving has finished receiving all the information. This is the easiest form of communications but not 
necessarily the fastest.

MPI_Send(buffer_starting_address, total_no_of_blocks_of_given_type, mpi_type_name, rank_of_receiver_process, tag, Communicator);

MPI_Recv(buffer_starting_address, total_no_of_blocks_of_given_type, mpi_type_name, rank_of_source_process, tag, Communicator, status_structure);

*/