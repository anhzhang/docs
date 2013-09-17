#include <fstream>
#include <iostream>
#include <mpi.h>

// mpic++ -o  mpiManagementExample mpiManagementExample.cpp 
// mpirun -np 4 --host localhost mpiManagementExample

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

  // Variables to keep track of the status and the requests to send
  // info.
  MPI_Status  theStatus[2];
  MPI_Request theRequests[2];

  // Variables used to determine if the info has come through.
  int test1;
  int test2;

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

  // Initialize the buffer to be sent.
  for(lupe=0;lupe<NUMBER;++lupe)
    {
      val[lupe] = (double)lupe + rank;
    }


  // pass the info along to the next process
  std::cout << "Process " << rank << " sending message to " 
            << (rank+1)%numtasks << " process." << std::endl;
  MPI_Isend(val,NUMBER,MPI_DOUBLE,(rank+1)%numtasks,10,MPI_COMM_WORLD,&theRequests[0]);

  // Wait to hear the message.
  std::cout << "Process " << rank << " waiting to hear the message" << std::endl;
  MPI_Irecv(val,NUMBER,MPI_DOUBLE,MPI_ANY_SOURCE,MPI_ANY_TAG,MPI_COMM_WORLD,&theRequests[1]);

  // keep checking to see when everything is done.
  // This is not a good way to do it, and it is only for demonstration purposes.
  test1 = 0;
  test2 = 0;
  while(!test1 && !test2)
    {
      MPI_Test (&theRequests[0],&test1,&theStatus[0]);
      MPI_Test (&theRequests[1],&test2,&theStatus[1]);
    }

  // Alternatively, just wait for them all at once....
  MPI_Waitall(2, theRequests, theStatus);

  // print out the info that was passed
  std::cout << "Process " << rank << " heard: ";
  for(lupe=0;lupe<NUMBER;++lupe)
    std::cout << val[lupe] << ", ";
  std::cout << std::endl;

  // All done. Time to wrap it up.
  MPI_Finalize();
  return(0);
}
