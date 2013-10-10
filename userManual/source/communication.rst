
***************************************
Sharing Information Between Processes
***************************************

The Open MPI libraries provide for a wide variety of approaches for
sharing information between processes. The details of how the
information is managed and passed between the physical machines is
hidden, and the programmer is allowed to focus on the information and
how to organize it from the point of view of an individual
process. The ideas shared here are divided into three broad sections.

First the most basic functions that allow the programmer to share data
are given. The focus in this first section is on synchronous
(blocking) communication and non-synchronous (non-blocking)
communication. At the most fundamental level synchronous
communications will wait until the request to share information is
complete from the point of view of the processes that send and receive
the information. Asynchronous communications, on the other hand, do
not wait, rather they submit the request to either send or receive the
information and the process is then allowed to go on and perform other
tasks.

In the second section some of the intermediate ideas and functions are
given. These build on the basic ideas of synchronous and asynchronous
communications but explore the details on ways to manage the buffers
used to shared information sent between processes. This section also
explores more ways to decide if requests have been completed.

Finally, in the third section some of the more advanced ideas and
functions are given. This section builds on the second section and
goes a little further into the organization of buffers. Additional
details are also explored in how to track the status of a request.

.. sidebar:: TODO 

   I am not familiar with the broadcast, scatter and gather
   routines. Where do they go?

======
Basic
======

In this section we introduce the basic ideas of sharing information
between processes. The focus is on passing messages, and messages can
be passed using synchronous (blocking) and asynchronous (non-blocking)
approaches. Each of these two ideas are given in separate subsections
starting with synchronous methods.

---------------------------
Synchronous communications
---------------------------

.. sidebar:: TODO 

   Discuss the idea of blocking sends and receives. Basic introduction to
   the idea.

.. sidebar:: TODO 

    Relies on the process chapter.

Ideas and library calls: 

  * ``MPI_Send``
  * ``MPI_Recv``



.. _listing-blockingCommunication:

.. literalinclude:: cpp/mpiBlockingCommunication.cpp
    :language: c++
    :linenos:


:ref:`Blocking Communication <listing-blockingCommunication>`

---------------------------
Aynchronous communications
---------------------------

.. sidebar:: TODO 

   Discuss the basic idea of asynchronous communications. Give basic
   examples. Next subsection goes into more details once richer data
   structures can be used.

Ideas and library calls: 

    * ``MPI_Isend``
    * ``MPI_Irecv``
    * ``MPI_Wait\*``
    * ``MPI_Test\*``




.. _listing-nonBlockingCommunication:

.. literalinclude:: cpp/mpiNonBlockingCommunication.cpp
    :language: c++
    :linenos:

:ref:`Nonblocking Communication <listing-nonBlockingCommunication>`

----------------------------
Data and Memory Management
----------------------------

.. sidebar:: TODO 

    Discuss memory organization. Discuss the ideas of buffers. Need to
    discuss the differences between synchronous and asynchronous
    communications.


    * Memory management and buffers
    * Data types


=============
Intermediate
=============

---------------------------
Synchronous communications
---------------------------

Ideas and library calls


    * ``MPI_Ssend``
    * ``MPI_Bsend``
    * ``MPI_Buffer_attach``
    * ``MPI_Buffer_detach``


----------------------------
Aynchronous communications
----------------------------

Ideas and library calls


    * ``MPI_Iprobe``
    * ``MPI_Probe``


---------------------------
Data and Memory Management
---------------------------


    * Memory management and buffers
    * Data types



=========
Advanced
=========

----------------------------
Synchronous communications
----------------------------

Ideas and library calls


    * ``MPI_Rsend``
    * ``MPI_Sendrecv``


---------------------------
Aynchronous communications
---------------------------

Ideas and library calls:


    * ``MPI_Issend``
    * ``MPI_Ibsend``


----------------------------
Data and Memory Management
----------------------------

Ideas and library calls:


    * Memory management and buffers
    * Data types


