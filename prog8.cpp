// Implement a C program which demonstrates the 
// default, static and dynamic methods of "scheduling" 
// loop iterations in OpenMP to avoid work imbalance.

#include<iostream>
#include<vector>
#include<omp.h>
using namespace std;
int main(){

    int noOfThreads;
    int threadId;

    int n;
    cout<<"Enter the no. of elts : ";
    cin>>n;

    vector<int> v(n);

    cout<<"Enter the array : ";
    for(int i=0;i<n;i++){
        cin>>v[i];
    }

    int threadCount;
    cout<<"Enter the no. of threads : ";
    cin>>threadCount;

    #pragma omp parallel private(threadId) num_threads(threadCount)
    {
        threadId=omp_get_thread_num();

        // Default Scheduling
        #pragma omp for
        for(int i=0;i<n;i++){
            cout<<"Thread "<<threadId<<" executing iteration "<<i<<endl;
        }

        #pragma omp barrier

        if(threadId==0){
            cout<<"*************************"<<endl;
        }
        
        // Static Scheduling
        #pragma omp for schedule(static,4)
        for(int i=0;i<n;i++){
            cout<<"Thread "<<threadId<<" executing iteration "<<i<<endl;
        }

        if(threadId==0){
            cout<<"*************************"<<endl;
        }
        
        // Dynamic Scheduling
        #pragma omp for schedule(dynamic,4)
        for(int i=0;i<n;i++){
            cout<<"Thread "<<threadId<<" executing iteration "<<i<<endl;
        }
    }

    return 0;
}