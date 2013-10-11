
***************************
Introduction To Open MPI
***************************

=============
Open MPI
=============

.. index:: Open MPI

The Message Passing Interface (MPI) is a set of definitions for
managing multiple processes on a wide variety of computational
platforms. Open MPI is an implementation of this set of definitions.
The MPI definition is based on the idea of multiple processes running
in parallel, and the set of definitions provides a way to create
multiple processes, initiate multiple processes, and share information
between them.

At its most basic level Open MPI provides a framework in which the
computational platform can be treated as a array of independent,
distributed memory, distributed processor machines. This framework
allows for the creation of programs that can exploit this assumed
structure, and it allows for the creation and execution of multiple
processes that can be thought of as acting independently of one
another.  Any information shared between the processes must done so
explicitly making use of the Open MPI library.

\todo Provide a low level introduction to MPI

=================
Getting Started
=================

.. index:: tutorial


A quick example is given to provide an overview of how to run a set of
processes in the Open MPI execution environment. The program, shown in
listing :ref:`a first program <listing-firstProcess>`, is compiled and
ran. Each process in the job determines the total number of processes
and the order number for the process, and it then prints out the
details.

.. _listing-firstProcess:

.. literalinclude:: cpp/firstExample.c
    :language: c
    :linenos:

.. centered::
   Table: A First Example.
   A simple example of a program using the Open MPI ABI.

The commands to compile and execute the processes are given below,
:ref:`output from a first program <output-firstProcess>`. The code is
first compiled using the `mpicc` command and is then executed using
the `mpirun` command using a total of four processes.

.. _output-firstProcess:

.. code-block:: sh

   sh$ mpicc -o  firstExample firstExample.c
   sh$ mpirun -np 4 --host localhost firstExample
     Number of tasks: 4, my rank: 0, hostname: black.sc.clarkson.edu
     Number of tasks: 4, my rank: 1, hostname: black.sc.clarkson.edu
     Number of tasks: 4, my rank: 2, hostname: black.sc.clarkson.edu
     Number of tasks: 4, my rank: 3, hostname: black.sc.clarkson.edu

.. centered::
   Table: Output From A First Example.
   The output from the simple example of a program using the Open MPI
   ABI.



=========================
Compilation and Running
=========================

We provide a broad overview on how to compile and run a program to
work within the Open MPI execution environment. Open MPI provides both
the executable environment and the binary interface to the libraries
for sharing information across multiple processes in a wide variety of
hardware platforms. The details on how to compile and execute the
resulting processes can vary widely depending on the physical system
and how it is set up. 

The Open MPI execution environment can be accessed in one of the
following ways:

   * BProc versions 3 and 4 with LSF
   * Sun Grid Engine (SGE), and the open source Grid Engine (support first introduced in Open MPI v1.2)
   * PBS Pro, Torque, and Open PBS
   * LoadLeveler scheduler (full support since 1.1.1)
   * rsh / ssh
   * SLURM
   * XGrid
   * Yod (Cray XT-3 and XT-4)

We do not explore the details of all of these systems but provide an
overview of how to compile and execute a job using the standard Open
MPI libraries and wrappers. First, the details on compilation and
linking are explored. After that the details on executing a set of
processes is explored.

--------------
Compilation
--------------

.. index:: compilation
.. index:: mpicc
.. index:: linking
.. index:: compiler options
.. index:: --showme

To compile a C code that makes use of the Open MPI libraries you use
the ``mpicc`` command. This can be called from within a shell, or is
more commonly used within a make file. The command is used in the same
way as you might call ``gcc`` to compile a regular C file. 

.. code-block:: sh

   sh$ mpicc myApplication.c -o myApplication

The ``mpicc`` program is a wrapper around your system's C
compiler. Here the ``-o`` directive indicates what the name of the
resulting program should be.

If you do not wish to use the ``mpicc`` wrapper you can use your
system's normal compiler. To determine the required compile options,
the following command can be used to print out the compiler options
used on your system:

.. code-block:: sh

   sh$ mpicc --showme:compile

The following command can be used to then determine the linker options
used on your system:

.. code-block:: sh

   sh$ mpicc --showme:link

If you require more details or wish to see the specific commands that
the wrapper is using on your system the ``--showme`` option can be
used with ``mpicc`` to provide verbose output:

.. code-block:: sh

   sh$ mpicc myApplication.c -o myApplication --showme


-----------
Execution
-----------

.. index:: running
.. index:: execution
.. index:: mpirun
.. index:: mpiexec

The commands used to run an Open MPI program are ``mpirun`` and
``mpiexec``. These commands must be in your path, and your
``LD_LIBRARY_PATH`` must also include the Open MPI library. For
example, if your Open MPI installation is located in your
``/opt/openmpi`` directory then you need to execute the following lines
if you are using a bash shell:

.. code-block:: sh

   sh$ export PATH=$PATH:/opt/openmpi/bin
   sh$ export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/opt/openmpi/lib

There are a wide variety ways to submit jobs for any system, and the
requirements can vary widely across different systems. You should
consult the manager for your system to get details and determine how
jobs are submitted for your particular system. The methods given below
are the generic approaches that are part of the standard Open MPI
libraries, but they may not be appropriate for your particular
system. 

The most simple way to execute a program under the Open MPI system is
to use either the ``mpirun`` or the ``mpiexec`` command. Both commands
are symbloic links to the Open MPI backend that manages processes, and
we use ``mpirun`` here for our examples. 

You can specify the number of processes to initiate using the ``--np``
flag, and you then specify the name of the program to start. For
example, to execute a program called *myApplication* that has been
successfully compiled and linked using five processes you enter the
following command:

.. code-block:: sh

   sh$ mpirun --np 5 myApplication

This command will start five processes within the Open MPI run-time
execution system, and the five procceses will load and execute copies
of the program.

You can specify which computers that will run the processes using the
``--host`` flag. The argument for this flag is a comma separated list
of hosts. For example, to run three processes on hosts ``thingOne``,
``thingTwo``, and ``thingThree`` the following command can be used:

.. code-block:: sh

   sh$ mpirun --np 3 --host thingOne,thingTwo,thingThree myApplication

Another widely used flag is the ``--hostfile`` option. This flag
allows you to specify a list of hosts to be used, and the file format
allows you to specify the maximum number of processes per host. An
example is given below:

.. code-block:: sh

   # hosts.txt
   # hostfile for my run
   # Note that anything after a "#" is treated as a comment.

   # Specify a file which will only have one process
   thingOne.clarkson.edu

   # Specify a machine with many cores that will safely allow two
   # processes
   thingTwo.clarkson.edu=2

   # Specify a machine with limited cores that will safely allow two
   # processes but certainly not more than 3
   thingThree.clarkson.edu slots=2 max-slots=3

If the name of this file is *hosts.txt* then five processes can be
started on the hosts using the following command:

.. code-block:: sh

   sh$ mpirun --np 5 --hostfile hosts.txt myApplication


Note that the ``--host`` and the ``--hostfile`` flags can be used
together, but the  arguments to the ``--host`` command must be
contained in the given host file. The result of the ``--host`` options
is to limit the hosts to use that are found within the host file *and*
are in the list of options to the ``--host`` flag. For example, if a
file *hosts.txt* contains ``thingOne``, ``thingTwo``, and
``thingThree``, the following command will start the processes on
``thingTwo`` and ``thingThree``:

.. code-block:: sh

   sh$ mpirun --np 2 --hostfile hosts.txt --host thingTwo,thingThree  myApplication

On the other hand, the following command will result in an error and
cannot be executed because the host ``thingFour`` is not in the host file:

.. code-block:: sh

   sh$ mpirun --np 2 --hostfile hosts.txt --host thingOne,thingFour  myApplication


========================
High Level Introduction
========================

.. todo::
   Give a more detailed introduction. Include some information about the
   MPI functionality.

.. todo:: 
   Discuss how to distribute processes across nodes or across slots.

.. todo::
   Add discussion on the following environment variables:

   * OMPI_COMM_WORLD_SIZE - the number of processes in this process' MPI Comm_World
   * OMPI_COMM_WORLD_RANK - the MPI rank of this process
   * OMPI_COMM_WORLD_LOCAL_RANK - the relative rank of this process on this node within its job. For example, if four processes in a job share a node, they will each be given a local rank ranging from 0 to 3.
   * OMPI_UNIVERSE_SIZE - the number of process slots allocated to this job. Note that this may be different than the number of processes in the job.
   * OMPI_COMM_WORLD_LOCAL_SIZE - the number of ranks from this job that are running on this node.
   * OMPI_COMM_WORLD_NODE_RANK - the relative rank of this process on
     this node looking across ALL jobs.

.. todo:: 
   Discuss starting up MPI connections lazy vs. immediate

   * in the environment as OMPI_MCA_mpi_preconnect_mpi=1
   * on the cmd line as mpirun -mca mpi_preconnect_mpi 1

From Joshua Hursey: 


|  A high level introduction to some MPI functionally would be nice,
|  but I would not worry too much about the uglier corner cases of the
|  API.





