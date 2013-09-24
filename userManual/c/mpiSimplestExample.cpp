#include <fstream>
#include <iostream>
#include <mpi.h>

// mpic++ -o  mpiSimplestExample mpiSimplestExample.cpp 
// mpirun -np 4 --host localhost mpiSimplestExample

int main(int argc,char **argv)
{
  // MPI job information.
  int  mpiResult;     // Used to check the results from MPI library calls

  // Initialize the session
  mpiResult = MPI_Init (&argc,&argv);
  if(mpiResult!= MPI_SUCCESS)
    {
      std::cout << "MPI not started. Terminating the process." << std::endl;
      MPI_Abort(MPI_COMM_WORLD,mpiResult);
    }

  // All done. Time to wrap it up.
  MPI_Finalize();
  return(0);
}
