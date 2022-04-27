// Write a parallel program that prints “Hello World” to 
// demonstrate task paritioning & IPC (Inter Process 
// Communication) using MPI (Message Passing Interface).

#include<iostream>
#include<mpi.h>
using namespace std;
int main(){
    
    int totalProcesses;
    int pid;

    MPI_Init(NULL,NULL);

    MPI_Comm_size(MPI_COMM_WORLD,&totalProcesses);
    MPI_Comm_rank(MPI_COMM_WORLD,&pid);

    if(pid==0){
        cout<<"The total no. of processes are "<<totalProcesses<<endl;
    }

    cout<<"Hello world from process "<<pid<<endl;

    MPI_Finalize();

    return 0;
}