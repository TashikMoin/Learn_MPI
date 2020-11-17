#include <stdio.h>
#include <mpi.h>
#include<unistd.h>
// run this code with 2 processes

void Check_If_Request_Is_Completed( int X , int Flag )
{
    if(Flag != 0)
    {
        printf("\nReceived Value Of X = %d [Correct value because of the complete request]\n", X) ;
    }
    else
    {
        printf("\nRequest Is Not Completed Yet And X = %d\n", X) ;
    }
    
}

int main(int argc, char **argv) 
{
    MPI_Init(&argc, &argv); 
    int Rank , X = 0 ;
    int Total_Processes ;
    int Flag ;
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
        printf("\n... Process # 0 has sent data and is executing the remaining code ... \n") ;
    }
    else 
    {
        printf("\nProcess # 1 is ready to receive data but process # 0 will take 10 seconds more to send it\n") ;
        printf("\nProcess # 1 would have waited for 10 seconds (blocked) if we would have used MPI_Send and MPI_Recv\n") ;
        printf("\nProcess # 1 will not wait this time because we have used aynchronous version of MPI_Send and MPI_Recv --> ISend/IRecv\n") ;
        MPI_Irecv( &X , 1 , MPI_INT , 0 , 0 , MPI_COMM_WORLD , &Request ); 
        MPI_Test(&Request, &Flag, &Status);
        printf("\nCode After MPI_Irecv And MPI_Test [This Comes Immediately Because Testing Is Non-Blocking]\n") ;
        Check_If_Request_Is_Completed(X , Flag); 
        // let say at this point no more work to do but we need value of X at this point so we have to wait here and not at the start
        MPI_Wait(&Request, &Status) ; 
        /* 
        MPT_Test and MPI_TestAny tells us at what point we should use MPI_Wait to make our code more efficient.

        MPI_Wait is always used along with Test. we only start waiting when we actual need data from other processes.
        Be careful when using MPI_Test to always add a MPI_Wait in case the request has not been completing even 
        though your work is finished.
        */  
        Check_If_Request_Is_Completed(X , Flag);
        printf("\nX = %d",X);
    } 

    MPI_Finalize(); 
}

    /*
        Testing is non-blocking, so in any case the process continues execution after the call. The variable flag is there to 
        tell you if the request was completed during the test or not. If flag != 0 that means the request has been completed.
        MPI_Test function takes 3 parameters two of them are similar that of MPI_Wait but there is an additional parameter which
        is the flag variable that tells whether the request is compelted or not. if flag is != 0 means request is completed.

        when using MPI_Test/MPI_TestAny to always add a MPI_Wait/MPI_WaitAny in case the request has not been completing even 
        though your work is finished.

        MPI_Testany(Request/Array_Size, Array_of_requests[], Completed_Request_Index, flag, Status); is similar to MPI_WaitAny
        but is non-blocking and has a flag variable that tells whether the request is completed or not. if flag is not 0 then 
        it means the request is completed and if it is zero then it means request has to be completed.
        Note: Flag is not bool here it should be an integer.
    */