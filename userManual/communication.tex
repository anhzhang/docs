\chapter{Sharing Information Between Processes}


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

\todo I am not familiar with the broadcast, scatter and gather
routines. Where do they go?


\section{Basic}

In this section we introduce the basic ideas of sharing information
between processes. The focus is on passing messages, and messages can
be passed using synchronous (blocking) and asynchronous (non-blocking)
approaches. Each of these two ideas are given in separate subsections
starting with synchronous methods.

\subsection{Synchronous communications}

\todo Discuss the idea of blocking sends and receives. Basic introduction to
the idea.

\todo Relies on the process chapter.

Ideas and library calls: \\
\begin{itemize}
\item \texttt{MPI\_Send}
\item \texttt{MPI\_Recv}
\end{itemize}

\lstset{language=C++, numbers=left, numberstyle=\tiny, stepnumber=1,
  numbersep=5pt, commentstyle=\scriptsize}
\begin{lstlisting}[caption={Example of blocking communication.},
                   basicstyle=\scriptsize,
                   label=listing:blockingCommunication]
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
  MPI_Status theStatus;

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


  // Decide to start the communication or wait to hear something.
  if(rank == 0)
    {
      // This is the first process. Send my information to the second process.

      // First initialize the buffer
      for(lupe=0;lupe<NUMBER;++lupe)
        {
          val[lupe] = (double)lupe;
        }

      // Now pass the information along to the next process.
      std::cout << "Sending message from the zero process" << std::endl;
      MPI_Send(val,NUMBER,MPI_DOUBLE,1,10,MPI_COMM_WORLD);

      // Now wait to get the information from the last process in the ring.
      std::cout << "Zero process waiting to hear the message from " << numtasks-1 << std::endl;
      MPI_Recv(val,NUMBER,MPI_DOUBLE,MPI_ANY_SOURCE,MPI_ANY_TAG,MPI_COMM_WORLD,&theStatus);
      std::cout << "Zero process heard from  " << theStatus.MPI_SOURCE << " with tag " 
                << theStatus.MPI_TAG << std::endl;
    }

  else
    {
      // I am not the first process. Wait until I get the information
      // before passing along what I have.
      std::cout << "Process " << rank << " waiting to hear the message" << std::endl;
      MPI_Recv(val,NUMBER,MPI_DOUBLE,MPI_ANY_SOURCE,MPI_ANY_TAG,MPI_COMM_WORLD,&theStatus);
      std::cout << "Process " << rank << " heard from  " << theStatus.MPI_SOURCE << " with tag " 
                << theStatus.MPI_TAG << std::endl;

      // update the information that was sent to me.
      for(lupe=0;lupe<NUMBER;++lupe)
        val[lupe] += 1.0;

      // Finally pass it along to the next process in the ring.
      std::cout << "Process " << rank << " sending message to " 
                << (rank+1)%numtasks << " process." << std::endl;
      MPI_Send(val,NUMBER,MPI_DOUBLE,(rank+1)%numtasks,10,MPI_COMM_WORLD);
    }

  // print out the information that I have.
  std::cout << "Process " << rank << " heard: ";
  for(lupe=0;lupe<NUMBER;++lupe)
    std::cout << val[lupe] << ", ";
  std::cout << std::endl;

  // All done. Time to wrap it up.
  MPI_Finalize();
  return(0);
}
\end{lstlisting}

\subsection{Aynchronous communications}

\todo Discuss the basic idea of asynchronous communications. Give basic
examples. Next subsection goes into more details once richer data
structures can be used.

Ideas and library calls: \\
\begin{itemize}
\item \texttt{MPI\_Isend}
\item \texttt{MPI\_Irecv}
\item \texttt{MPI\_Wait*}
\item \texttt{MPI\_Test*}
\end{itemize}

\lstset{language=C++, numbers=left, numberstyle=\tiny, stepnumber=1,
  numbersep=5pt, commentstyle=\scriptsize}
\begin{lstlisting}[caption={Example of nonblocking communication.},
                   basicstyle=\scriptsize,
                   label=listing:nonblockingCommunication]
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
\end{lstlisting}

\subsection{Data and Memory Management}

\todo Discuss memory organization. Discuss the ideas of buffers. Need to
discuss the differences between synchronous and asynchronous
communications.

\begin{itemize}
\item Memory management and buffers
\item Data types
\end{itemize}

\section{Intermediate}

\subsection{Synchronous communications}

\todo Ideas and library calls: \\
\begin{itemize}
\item \texttt{MPI\_Ssend}
\item \texttt{MPI\_Bsend}
\item \texttt{MPI\_Buffer\_attach}
\item \texttt{MPI\_Buffer\_detach}
\end{itemize}

\subsection{Aynchronous communications}

\todo Ideas and library calls: \\
\begin{itemize}
\item \texttt{MPI\_Iprobe}
\item \texttt{MPI\_Probe}
\end{itemize}

\subsection{Data and Memory Management}

\begin{itemize}
\item Memory management and buffers
\item Data types
\end{itemize}


\section{Advanced}


\subsection{Synchronous communications}

\todo Ideas and library calls: \\
\begin{itemize}
\item \texttt{MPI\_Rsend}
\item \texttt{MPI\_Sendrecv}
\end{itemize}

\subsection{Aynchronous communications}

\todo Ideas and library calls: \\
\begin{itemize}
\item \texttt{MPI\_Issend}
\item \texttt{MPI\_Ibsend}
\end{itemize}

\subsection{Data and Memory Management}

\todo Ideas and library calls: \\
\begin{itemize}
\item Memory management and buffers
\item Data types
\end{itemize}


%%% Local Variables: 
%%% mode: latex
%%% TeX-master: "OpenMPIUserManual"
%%% End: 
