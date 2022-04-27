// Implement a C program which demonstrates how to 
// "multitask", that is, to execute several unrelated 
// and distinct tasks simultaneously, using OpenMP for 
// parallel execution.

#include<iostream>
#include<omp.h>
using namespace std;
int main(){

    int noOfThreads=5;
    int threadId;
    int threadCount=4;

    #pragma omp parallel private(threadId) num_threads(threadCount)
    {
        threadId=omp_get_thread_num();
        cout<<"Hi, I am thread "<<threadId<<endl;

        cout<<"Before "<<noOfThreads<<endl;

        #pragma omp barrier

        if(threadId==0){
            noOfThreads=omp_get_num_threads();

            cout<<"Master : My team has "<<noOfThreads<<" threads"<<endl;
        }
        else{
            cout<<"hello"<<endl;
        }

        cout<<"After "<<noOfThreads<<endl;
    }

    return 0;
}