#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

/*
  A first example for running an MPI program on Open MPI. 
  To execute and run use the following commands:

   mpicc -o  firstExample firstExample.c 
   mpirun -np 4 --host localhost firstExample

*/

int main(int argc,char **argv)
{
  /* MPI job information. */
  int  mpiResult;  /* Used to check the results from MPI library calls */
  int  numtasks;   /* Total number of processes spawned for this job.  */
  int  rank;       /* The unique number associated with this process.  */

  /* Host Information */
  char hostname[MPI_MAX_PROCESSOR_NAME];
  int  len;

  /* Initialize the session */
  mpiResult = MPI_Init (&argc,&argv);
  if(mpiResult!= MPI_SUCCESS)
    {
      printf("MPI not started. Terminating the process.\n");
      MPI_Abort(MPI_COMM_WORLD,mpiResult);
    }

  /* Get information about this session and this process  */
  MPI_Comm_size(MPI_COMM_WORLD,&numtasks);  /* get the number of processes  */
  MPI_Comm_rank(MPI_COMM_WORLD,&rank);      /* get the rank of this process */
  MPI_Get_processor_name(hostname, &len);   /* Get the host name for this process */

  /* Print out the information about this process. */
  printf("Number of tasks: %d, my rank: %d, hostname: %s\n",
         numtasks,rank,hostname);

  /* All done. Time to wrap it up. */
  MPI_Finalize();
  return(0);
}
