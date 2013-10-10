
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

.. todo::

   Give an example like a mini-tutorial.


=========================
Compilation and Running
=========================

.. todo::
   Discuss in more detail how to compile and execute a process. 


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

Another widely used flag is the ``--hostfile`` option. This flag
allows you to specify a list of hosts to be used, and the file format
allows you to specify the maximum number of processes per host. 

.. code-block:: sh

   # hostfile for my run
   # Note that anything after a "#" is treated as a comment.

   # Specify a file which will only have one process
   bubba.manges.edu

   # Specify a machine with many cores that will safely allow two
   # processes
   friendly.manges.edu=2

   # Specify a machine with limited cores that will safely allow two
   # processes but certainly not more than 3
   angry.manges.edu slots=2 max-slots=3



========================
High Level Introduction
========================

.. todo::
   Give a more detailed introduction. Include some information about the
   MPI functionality.

From Joshua Hursey: 


|  A high level introduction to some MPI functionally would be nice,
|  but I would not worry too much about the uglier corner cases of the
|  API.





