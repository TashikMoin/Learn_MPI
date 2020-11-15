#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv) 
{
   // At this point n number of processes are created to execute the code.
   printf("Before MPI_INIT\n"); // this will be printed n * (total_processes_inside_communicator) times.
   MPI_Init(&argc, &argv); 
   printf("Hello world\n"); 
   MPI_Finalize(); //
}

/* 
"mpirun -np 10 ./MPI"   --> To specify total number of processes at the time of running the exec/output file.

The function MPI_INIT is used to initiate an MPI computation, respectively.MPI_INIT must be called before any 
other MPI function and must be called exactly once per process. No further MPI functions can be called 
after MPI_FINALIZE.

The MPI standard does not say what a program can do before an MPI_INIT or after an MPI_FINALIZE. In the MPICH implementation, 
you should do as little as possible. In particular, avoid anything that changes the external state of the program, such as 
opening files, reading standard input or writing to standard output.

The MPI_Finalize function cleans up all state related to MPI. Once it is called, no other MPI functions may be called, 
including MPI_Init and MPI_Init_thread. The application must ensure that all pending communications are completed or 
canceled before calling MPI_Finalize.
*/
   