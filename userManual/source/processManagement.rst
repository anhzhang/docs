****************************************
Process Management
****************************************

=========
Basic
=========


When an MPI execution environment is initiated the requested number of
processes are created and are distributed in the manner specified by
the command used to start the processes. For example, if the
``mpirun`` command is used the options provided will determine
how many processes to start as well as the different machines to use.

At a minimum a process within the MPI execution environment is
expected to call two functions. Prior to any other call to the MPI
library the ``MPI_Init`` function *must* be called. When
the process will no longer make use of the MPI library the
``MPI_Finalize`` function should be called. 



.. _tabbasicProcessManagementCommands:


+--------------------+----------------------------------------------------+
|``MPI_Init``        | **Required** to initialize an process              |
+--------------------+----------------------------------------------------+
|``MPI_Comm_size``   | Determine the number of MPI processes              |
+--------------------+----------------------------------------------------+
|``MPI_Comm_rank``   | Determine the number associated with this process. |
+--------------------+----------------------------------------------------+
|``MPI_Abort``       | Stops all MPI processes.                           |
+--------------------+----------------------------------------------------+
|``MPI_Initialized`` | Determine if ``MPI_Init`` has been called.         |
+--------------------+----------------------------------------------------+
|``MPI_Finalize``    | Stops the MPI execution environment.               |
+--------------------+----------------------------------------------------+
|``MPI_Finalized``   | Determine if ``MPI_Finalize`` has been called.     |
+--------------------+----------------------------------------------------+

.. centered::
   Table: Basic Process Management Routines
   A list of the basic process management routines.




A number of other routines are available that can be used to get basic
information about the process calling the routines.  These basic
routines are given in Table 
:ref:`Basic Process Management Routines <tabbasicProcessManagementCommands>`
They are used to dynamically determine the number of MPI processes
that are associated with the job, determine a way to differentiate
between the different processes as an ordered list of processes, and
to gracefully end the processes.

-----------------------------------------------------------
Initializing and Terminating the MPI Execution Environment
-----------------------------------------------------------

The routines used to initialize and end an execution environment are
given here. The routines given are ``MPI_Init``, ``MPI_Abort``,
``MPI_Initialized``, and ``MPI_Finalize``. The syntax for these
routines are given in Table
:ref:`Basic Process Initialization Routines <tabinitializeProcessCommands>`
and are briefly discussed in order.

The first MPI library call must be the ``MPI_Init`` routine, and
this command can only be called once. The C/C++ versions of the
routine require two arguments that match the ``argc`` and
``argv`` arguments provided to the main program. The arguments
are not altered. 

The ``MPI_Initialized`` routine is available to test whether or
not the ``MPI_Init`` routine has been called.  The
``MPI_Initialized`` routine is the only routine in the Open MPI
library that can be called before the ``MPI_Init`` routine is
called. Question: Is the returned value and the flag the same?

.. _tabinitializeProcessCommands:

+--------------------+----------------------------------------------+
|``MPI_Init``        | int MPI_Init(int \*argc, char \*\*argv)      |
+--------------------+----------------------------------------------+
|``MPI_Initialized`` | int MPI_Initialized(int \*flag)              |
+--------------------+----------------------------------------------+
|``MPI_Abort``       | int MPI_Abort(MPI_Comm comm, int errorcode)  |
+--------------------+----------------------------------------------+
|``MPI_Finalize``    | int MPI_Finalize()                           |
+--------------------+----------------------------------------------+
|``MPI_Finalized``   | int MPI_Finalized(int \*flag)                |
+--------------------+----------------------------------------------+

.. centered::
    Table: Basic Process Initialization Routines
    Syntax for the initialization and termination routines.


A call to the ``MPI_Abort`` routine is a request to stop all of the
processes in the execution environment. The system will attempt to
stop all of the processes within the communicator group.  The error
code that is passed to this routine is passed to the main program and
should be handled appropriately.

.. todo:: TODO

   Needs Reference to Communicators

The last MPI routine to be called by a process is the
``MPI_Finalize`` routine. This library routine will clean up all
MPI states. The only routines that can be called after the
``MPI_Finalize`` is called are the ``MPI_Get_version``,
``MPI_Initialized``, and ``MPI_Finalized`` routines.

Prior to calling the ``MPI_Finalize`` routine all pending
communications should be completed. There is no guarantee that any
communication request that is pending when the ``MPI_Finalize``
routine is executed will be completed. This command will impact all
processes in an execution environment, and it is left to the
programmer to determine that any pending requests have been completed
prior to calling the ``MPI_Finalize`` routine.

Finally, the ``MPI_Finalized`` routine allows for a process to
check to see if the ``MPI_Finalize`` routine has been called by
a process in the execution environment. This routine can be called
before ``MPI_Init`` or after the ``MPI_Finalize`` command
has been called. It returns an expression that evaluates to ``true``
if the ``MPI_Finalize`` routine has been executed and
completed. 


-------------------
Basic Information
-------------------

.. _tabProcessInformationCommands:


+-------------------+-----------------------------------------------+
|``MPI_Comm_size``  |  int MPI_Comm_size(MPI_Comm comm, int \*size) |
+-------------------+-----------------------------------------------+
|``MPI_Comm_rank``  |  int MPI_Comm_rank(MPI_Comm comm, int \*rank) |
+-------------------+-----------------------------------------------+

.. centered::
    Table: Basic Information Routines
    A list of the routines that provide basic information about the process.



There are two commands, ``MPI_Comm_size`` and
``MPI_Comm_rank``, that return information about processes
within an execution group. The first command,
``MPI_Comm_size``, returns the number of processes associated
with the communicator. If the communicator provided allows
communication between different groups then the number of processes
returned is with respect to the local group. 

The second command, ``MPI_Comm_rank``, returns information
about the specific process that calls the routine. It returns the rank
number assigned to the process. The ranks are numbered from 0 to
N-1, where N is the total number of processes associated with the
group. Combined with the ``MPI_Comm_size`` routine a process
can determine its position within the group, and decisions can be made
with respect to how different processes will determine their specific
tasks as well as how the communication patterns will proceed.

---------
Examples
---------

Two examples are given here. The first example, Listing
:ref:`Simple Process <listing-simplestProcess>` , 
is a minimal MPI program. The two
required routines are called. First the ``MPI_Init`` routine is
called, and at the end of the program the ``MPI_Finalize``
routine is called.


.. _listing-simplestProcess:

.. code-block:: cpp
     :linenos:

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


The second program, Listing
:ref:`Simple Process <listing-basicProcess>` 
provides a demonstration on the information that a process can
determine about the process itself as well as the wider execution
group. This program is similar to the minimal program given in Listing
:ref:`Simple Process <listing-simplestProcess>` . 
The primary difference is that the process makes use of the
``MPI_Comm_size`` and ``MPI_Comm_rank`` routines to determine how many
processes were initiated in the execution group and the relative order
of the process with respect to the other processes.


.. _listing-basicProcess:

.. code-block:: cpp
     :linenos:

     #include <fstream>
     #include <iostream>
     #include <mpi.h>

     // mpic++ -o  mpiManagementExample mpiManagementExample.cpp 
     // mpirun -np 4 --host localhost mpiManagementExample

     int main(int argc,char **argv)
     {
       // MPI job information.
       int  mpiResult;     // Used to check the results from MPI library calls
       int  numtasks;      // Total number of processes spawned for this job.
       int  rank;          // The unique number associated with this process.

       // Host Information 
       char hostname[MPI_MAX_PROCESSOR_NAME];
       int  len;

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

       // Print out the information about this process.
       std::cout << "Number of tasks= " <<  numtasks
                 << " My rank= " << rank
                 << " Running on " << hostname
                 << std::endl;

       // All done. Time to wrap it up.
       MPI_Finalize();
       return(0);
     }



=============
Intermediate
=============

Intermediate ideas and commands associated include the following: 

   * ``MPI_Get_processor_name``
   * ``MPI_Get_version``
   * ``MPI_Initialized``


.. todo:: TODO
 
   Talk about groups and communicators.

.. todo:: TODO
 
   Error handling and status.

=========
Advanced
=========

.. todo:: TODO

    Intermediate ideas and commands associated include the following: 

   * ``MPI_Wtime``
   * ``MPI_Wtick``
   * Go into details about communicators?



.. todo:: TODO

    Talk about groups and communicators.

.. todo:: TODO

   Error handling and status.

