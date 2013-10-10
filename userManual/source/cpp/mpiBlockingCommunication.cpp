#include <fstream>
#include <iostream>
#include <mpi.h>

// mpic++ -o  mpiBlockingCommunication  mpiBlockingCommunication.cpp 
// mpirun -np 4 --host localhost mpiBlockingCommunication

// The size of the array to be sent to the next process.
#define NUMBER 10

int main(int argc,char **argv)
{
  // MPI job information.
  int  mpiResult;     // Used to check the results from MPI library calls
  int  numtasks;      // Total number of processes spawned for this job.
  int  rank;          // The unique number associated with this process.

  // Information about the host this process is running on.
  char hostname[MPI_MAX_PROCESSOR_NAME]; 
  int len;

  // Information to be shared between processes.
  double val[NUMBER];
  int lupe;
  MPI_Status theStatus;

  // Initialize the session
  mpiResult = MPI_Init (&argc,&argv);
  if(mpiResult!= MPI_SUCCESS)
    {
      std::cout << "MPI not started. Terminating the process." << std::endl;
      MPI_Abort(MPI_COMM_WORLD,mpiResult);
    }


  // Get information about this session and this process 
  MPI_Comm_size(MPI_COMM_WORLD,&numtasks);  // get the number of processes
  MPI_Comm_rank(MPI_COMM_WORLD,&rank);      // get the rank of this process
  MPI_Get_processor_name(hostname, &len);   // Get the host name for
                                            // this process


  // Decide to start the communication or wait to hear something.
  if(rank == 0)
    {
      // This is the first process. Send my information to the second process.

      // First initialize the buffer
      for(lupe=0;lupe<NUMBER;++lupe)
        {
          val[lupe] = (double)lupe;
        }

      // Now pass the information along to the next process.
      std::cout << "Sending message from the zero process" << std::endl;
      MPI_Send(val,NUMBER,MPI_DOUBLE,1,10,MPI_COMM_WORLD);

      // Now wait to get the information from the last process in the ring.
      std::cout << "Zero process waiting to hear the message from " << numtasks-1 << std::endl;
      MPI_Recv(val,NUMBER,MPI_DOUBLE,MPI_ANY_SOURCE,MPI_ANY_TAG,MPI_COMM_WORLD,&theStatus);
      std::cout << "Zero process heard from  " << theStatus.MPI_SOURCE << " with tag " 
                << theStatus.MPI_TAG << std::endl;
    }

  else
    {
      // I am not the first process. Wait until I get the information
      // before passing along what I have.
      std::cout << "Process " << rank << " waiting to hear the message" << std::endl;
      MPI_Recv(val,NUMBER,MPI_DOUBLE,MPI_ANY_SOURCE,MPI_ANY_TAG,MPI_COMM_WORLD,&theStatus);
      std::cout << "Process " << rank << " heard from  " << theStatus.MPI_SOURCE << " with tag " 
                << theStatus.MPI_TAG << std::endl;

      // update the information that was sent to me.
      for(lupe=0;lupe<NUMBER;++lupe)
        val[lupe] += 1.0;

      // Finally pass it along to the next process in the ring.
      std::cout << "Process " << rank << " sending message to " 
                << (rank+1)%numtasks << " process." << std::endl;
      MPI_Send(val,NUMBER,MPI_DOUBLE,(rank+1)%numtasks,10,MPI_COMM_WORLD);
    }

  // print out the information that I have.
  std::cout << "Process " << rank << " heard: ";
  for(lupe=0;lupe<NUMBER;++lupe)
    std::cout << val[lupe] << ", ";
  std::cout << std::endl;

  // All done. Time to wrap it up.
  MPI_Finalize();
  return(0);
}
