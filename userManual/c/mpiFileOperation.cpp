#include <fstream>
#include <iostream>
#include <string.h>
#include <mpi.h>

// mpic++ -o  mpiManagementExample mpiManagementExample.cpp 
// mpirun -np 4 --host localhost mpiManagementExample

// Set the name of the data file and the number of items to write.
#define FILE_NAME "fileExample-01.dat"
#define NUMBER 10

int main(int argc,char **argv)
{
  // MPI job information.
  int  mpiResult;     // Used to check the results from MPI library calls
  int  numtasks;      // Total number of processes spawned for this job.
  int  rank;          // The unique number associated with this process.

  // Information to be written to the file.
  struct output 
  {
    double x;
    int    i;
  };

  // buffers used to write the information.
  output basicInfo;
  char   buffer[1024];

  // File related stuffs
  MPI_File mpiFileHandle;


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

  // open the file
  std::cout << "opening " << FILE_NAME << std::endl;
  MPI_Status status;
  char err_buffer[MPI_MAX_ERROR_STRING];
  int resultlen;
  int ierr = MPI_File_open(MPI_COMM_WORLD,FILE_NAME, 
                           MPI_MODE_WRONLY | MPI_MODE_CREATE | MPI_MODE_EXCL, 
                           MPI_INFO_NULL, 
                           &mpiFileHandle);

  // Print out the status of the request.
  std::cout << "Open: " << ierr << "," << MPI_SUCCESS << std::endl;
  std::cout << "Status: " << status.MPI_ERROR << "," 
            << status.MPI_SOURCE << "," 
            << status.MPI_TAG << std::endl;
  MPI_Error_string(ierr,err_buffer,&resultlen);
  std::cout << "Error: " << err_buffer << std::endl;


  if(ierr != MPI_SUCCESS)
    {
      // There was an error in trying to create the file. Stop
      // everything and shut down.
      std::cout << "Could not open the file. Terminating the process." << std::endl;
      MPI_Abort(MPI_COMM_WORLD,mpiResult);
    }

  // Write out the basic information to the file.
  // First move the file pointer to the correct location.
  MPI_File_seek(mpiFileHandle,rank*sizeof(basicInfo),MPI_SEEK_SET);

  // Set the data and  copy it to the buffer
  basicInfo.i = 2*rank;
  basicInfo.x = 1.0+(float)basicInfo.i;
  memset(buffer,0,1024);
  memcpy(buffer,&basicInfo,sizeof(basicInfo));

  // Let everybody know what will be written to the file.
  std::cout << "rank: " << rank << " moving pointer to "
            << rank*sizeof(basicInfo) 
            << " writing " <<  basicInfo.i 
            << " and " << basicInfo.x << std::endl;

  // write the date at the current pointer
  MPI_File_write(mpiFileHandle,buffer,sizeof(basicInfo)/sizeof(char),
                 MPI_CHAR, &status );

  // close the file 
  MPI_File_close(&mpiFileHandle);

  // All done. Time to wrap it up.
  MPI_Finalize();
  return(0);
}
