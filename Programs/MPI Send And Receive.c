#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv) 
{
   int ;
   MPI_Init(&argc, &argv);
   
   MPI_Finalize();
}