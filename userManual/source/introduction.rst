
***************************
Introduction To Open MPI
***************************

=============
Open MPI
=============

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

.. todo::
   How to compile a code

-----------
Execution
-----------

.. todo::
   How to start and execute a code and creating new processes. 

mpirun

mpiexec

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





