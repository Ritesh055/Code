// Write a program to find the sum of an array using MPI 
// in such a way that the parallel execution of sub-arrays 
// is done by parallel processes running to calculate their 
// partial sums & then finally, the master process (root process) 
// calculates the sum of these partial sums(adding the sum of its 
// own subarray) to return the total sum of the array.

#include<iostream>
#include<mpi.h>
using namespace std;
int main(){

    int totalProcesses;
    int pid;
    MPI_Status status;
    int temp[1000];

    int n;


    MPI_Init(NULL,NULL);

    MPI_Comm_size(MPI_COMM_WORLD,&totalProcesses);
    MPI_Comm_rank(MPI_COMM_WORLD,&pid);

    if(pid==0){
        cout<<"Enter no. of elts : ";
        cin>>n;

        int inc=n/totalProcesses;
        int last_inc=inc+n%totalProcesses;

        int*arr=new int[n];

        cout<<"Enter the array : ";
        for(int i=0;i<n;i++){
            cin>>arr[i];
        }

        for(int process=1;process<totalProcesses-1;process++){
            MPI_Send(&inc,1,MPI_INT,process,0,MPI_COMM_WORLD);
        }
        MPI_Send(&last_inc,1,MPI_INT,totalProcesses-1,0,MPI_COMM_WORLD);

        for(int process=1;process<totalProcesses-1;process++){
            MPI_Send(&arr[process*inc],inc,MPI_INT,process,1,MPI_COMM_WORLD);
        }
        MPI_Send(&arr[(totalProcesses-1)*inc],last_inc,MPI_INT,totalProcesses-1,1,MPI_COMM_WORLD);

        int sum=0;
        for(int i=0;i<inc;i++){
            sum+=arr[i];
        }
        int vals[totalProcesses-1];

        for(int process=1;process<totalProcesses;process++){
            MPI_Recv(&vals[process-1],1,MPI_INT,process,2,MPI_COMM_WORLD,&status);
        }
        
        for(int i=0;i<totalProcesses-1;i++){
            sum+=vals[i];
        }

        cout<<"The sum of the array is : "<<sum<<endl;

    }

    else{

        MPI_Recv(&n,1,MPI_INT,0,0,MPI_COMM_WORLD,&status);

        MPI_Recv(&temp,n,MPI_INT,0,1,MPI_COMM_WORLD,&status);

        int sum=0;
        for(int i=0;i<n;i++){
            sum+=temp[i];
        }

        MPI_Send(&sum,1,MPI_INT,0,2,MPI_COMM_WORLD);

    }



    MPI_Finalize();

    return 0;
}