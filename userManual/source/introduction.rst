
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

.. todo:: 
   Provide a low level introduction to MPI

=================
Getting Started
=================

.. index:: tutorial


A quick example is given to provide an overview of how to run a set of
processes in the Open MPI execution environment. The program, shown in
the listing (:ref:`a first program <listing-firstProcess>`), is
compiled and ran. Each process in the job determines the total number
of processes, the order number for the process, and it then prints out
the details.

.. _listing-firstProcess:

.. literalinclude:: cpp/firstExample.c
    :language: c
    :linenos:

.. centered::
   Listing: A First Example.
   A simple example of a program using the Open MPI ABI.

The commands to compile and execute the processes are given below
(:ref:`output from a first program <output-firstProcess>`). The code
is first compiled using the `mpicc` command and is then executed using
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
``/opt/openmpi`` directory then you need to either execute the
following lines if you are using a bash shell:

.. code-block:: sh

   sh$ export PATH=$PATH:/opt/openmpi/bin
   sh$ export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/opt/openmpi/lib

(Alternatively you could put these commands in your shell's profile.)

There are a wide variety ways to submit jobs for any system, and the
requirements can vary widely across different systems. You should
consult the manager for your system to get details and determine how
jobs are submitted for your particular system. The methods given below
are the generic approaches that are part of the standard Open MPI
libraries, but they may not be appropriate for your particular
system. 

The simplest way to execute a program under the Open MPI system is
to use either the ``mpirun`` or the ``mpiexec`` command. Both commands
are symbolic links to the Open MPI back-end that manages processes, and
we use ``mpirun`` here for our examples. 

You can specify the number of processes to initiate using the ``--np``
flag, and you then specify the name of the program to start. For
example, to execute a program called *myApplication* that has been
successfully compiled and linked using five processes you enter the
following command:

.. code-block:: sh

   sh$ mpirun --np 5 myApplication

This command will start five processes within the Open MPI run-time
execution system, and the five processes will load and execute copies
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
   thingTwo.clarkson.edu slots=2

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

   sh$ mpirun --np 2 --hostfile hosts.txt --host thingTwo.clarkson.edu,thingThree.clarkson.edu  myApplication

On the other hand, the following command will result in an error and
cannot be executed because the host ``thingFour`` is not in the host file:

.. code-block:: sh

   sh$ mpirun --np 2 --hostfile hosts.txt --host thingOne.clarkson.edu,thingFour.clarkson.edu  myApplication

The advantage to using both flags is that the ``--host`` flag can
specify which hosts to use. The ``--hostfile`` flag can be used to
provide a file name which contains details about the limits with
respect to the number of processes that can be used on each
machine. Taken together a general host file for a given system can be
used for a wide variety of job submissions.

Note that in the examples above fully qualified domain names are
used. This is not a requirement. If a name is found, that machine will
be used. Also, note that the host name is used to determine where the
process is run, but other details, such as the network interface, are
set through the various MCA parameters. See the chapter on
:ref:`tuning parameters<chapter-tuning>` for more details.

=============================
Defining Optional Behaviors
=============================

Some of the details of Open MPI are explored in this section. These
details focus on the Open MPI execution system. The examples given
here provide a relatively superficial overview of the kind of
behaviors that can be set or changed for an process. More details can
be found in the chapter on :ref:`tuning parameters.<chapter-tuning>`

A discussion on the environment variables defined by Open MPI is given
with a brief discussion of how environment variables are defined for a
process. Next a brief overview is given on the two different ways that
the parameters used to set specific behaviors can be set. 


.. to tell mpi where it is install used the --prefix flag.
.. shell$ mpirun --prefix /opt/openmpi-1.6.5 -np 4 a.out
..


-----------------------
Environment Variables
-----------------------

.. index:: environment variables
.. index:: OMPI_COMM_WORLD_SIZE
.. index:: OMPI_COMM_WORLD_RANK
.. index:: OMPI_COMM_WORLD_LOCAL_RANK
.. index:: OMPI_UNIVERSE_SIZE
.. index:: OMPI_COMM_WORLD_LOCAL_SIZE
.. index:: OMPI_COMM_WORLD_NODE_RANK

The local execution environment for a process includes copies of its
own environment variables. These environment variables depend on what
system is used to initiate the processes. For example, a system using
SLURM may be different from one using XGrid. The environment is
generally inherited from the user's shell, but some systems may not be
consistent with this ideal.

^^^^^^^^^^^^^^^^^^^^^^^^^^
Local Process Variables
^^^^^^^^^^^^^^^^^^^^^^^^^^

A few select environment variables created by Open MPI are given
below. These environment variables may be available to a process to
allow the program to determine fine grain needs with respect to the
whole set of processes in a given job.

   * OMPI_COMM_WORLD_SIZE - the number of processes in this process' MPI Comm_World
   * OMPI_COMM_WORLD_RANK - the MPI rank of this process
   * OMPI_COMM_WORLD_LOCAL_RANK - the relative rank of this process on this node within its job. For example, if four processes in a job share a node, they will each be given a local rank ranging from 0 to 3.
   * OMPI_UNIVERSE_SIZE - the number of process slots allocated to this job. Note that this may be different than the number of processes in the job.
   * OMPI_COMM_WORLD_LOCAL_SIZE - the number of ranks from this job that are running on this node.
   * OMPI_COMM_WORLD_NODE_RANK - the relative rank of this process on
     this node looking across ALL jobs.


It is possible to have environment variables set using the ``-x`` flag
on the ``mpirun`` command. The parser for this switch is somewhat
primitive, though, and it cannot correctly use quoted values. It is
recommended that environment variables be set in the process that
initiates the request to spawn MPI processes using the local
environment. 

^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Setting Open MPI Parameters
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The Open MPI execution environment can be tuned and changed for a wide
variety of settings. More details can be found in the :ref:`tuning
parameters chapter.<chapter-tuning>` These parameters, specifically
the parameters associated with the Modular Component Architecture
(MCA) modules, can be set in different ways. One way to set these
parameters is by setting local environment variables.

The MCA parameters have two parts. The first part is the *key*, and
the second part is the *value*. The key is used to identify the
parameter, and the value is used to set determine the behavior
associated with the modules that read the key. The format for the
environment variables is given by

.. code-block:: sh

   OMPI_MCA_<key>=<value>

For example, when a set of processes are initiated the processes can
either wait to establish connections between processes until one
begins to send messages. This is the default behavior since Open MPI
cannot predict in advance what topology the programmer will
assume. The processes will stay connected once the connections are
established.

Some applications require that all processes communicate with the
other processes. A programmer who makes use of a *fully connected*
topology may desire that those connections be created immediately once
the processes have been created. The MCA parameter associated with
this behavor is the ``mpi_preconnect_mpi`` parameter. If the
programmer wishes to assume this behavior then the following parameter
and value should be set in the environment that creates the processes:

.. code-block :: sh

   export OMPI_MCA_mpi_preconnect_mpi=1

Another way to set this parameter is using the ``-mca`` flag on the
``mpirun`` command. This flag takes two arguments, the key and the
value in order. For example, to set the ``mpi_preconnect_mpi``
parameter to ``True`` then a command may take the following form:

.. code-block :: sh

   mpirun -mca mpi_preconnect_mpi 1 -np 3 --host localhost myApplication


..  A high level introduction to some MPI functionally would be nice,
..  but I would not worry too much about the uglier corner cases of the
..  API.
..     -- Joshua Hursey



..  LocalWords:  MPI literalinclude mpicc mpirun LSF SGE LoadLeveler
..  LocalWords:  rsh SLURM XGrid Yod showme mpiexec hostfile todo
