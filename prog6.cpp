// Implement a program for Process Synchronization using mutex locks:
// Program create two threads: one to increment the value of a shared 
// variable and second to decrement the value of shared variable. Both 
// the threads make use of locks so that only one of the threads is 
// executing in its critical section

#include<iostream>
#include<pthread.h>
#include<unistd.h>
using namespace std;

int shared=0;
pthread_mutex_t lck;

void* increment(void*tid){

    cout<<"Thread 1 attempting to acquire lock"<<endl;
    pthread_mutex_lock(&lck);
    cout<<"Thread 1 acquires the lock"<<endl;

    int a=shared;
    cout<<"Value of shared variable read by thread 1 : "<<a<<endl;

    a+=8;

    sleep(2);
    shared=a;

    cout<<"Value of shared variable updated by thread 1 : "<<shared;

    pthread_mutex_unlock(&lck);

    cout<<"Lock released by thread 1"<<endl;

    pthread_exit(NULL);
}
void* decrement(void*tid){

    cout<<"Thread 2 attempting to acquire lock"<<endl;
    pthread_mutex_lock(&lck);
    cout<<"Thread 2 acquires the lock"<<endl;

    int a=shared;
    cout<<"Value of shared variable read by thread 2 : "<<a<<endl;

    a-=13;

    sleep(2);
    shared=a;

    cout<<"Value of shared variable updated by thread 2 : "<<shared;

    pthread_mutex_unlock(&lck);

    cout<<"Lock released by thread 2"<<endl;

    pthread_exit(NULL);

}
int main(){

    pthread_mutex_init(&lck, NULL);

    pthread_t thread1;
    pthread_t thread2;
    int tid1=1;
    int tid2=2;

    pthread_create(&thread1,NULL,increment,(void*)tid1);
    pthread_create(&thread2,NULL,decrement,(void*)tid2);


    pthread_join(thread1,NULL);
    pthread_join(thread2,NULL);

    pthread_exit(NULL);

    pthread_mutex_destroy(&lck);

    cout<<"The final value of shared variable = "<<shared<<endl;

    return 0;
}