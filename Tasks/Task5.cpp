#include<iostream>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<stdio.h>
#include<signal.h>
#include<fcntl.h>
#include<time.h>
using namespace std;
int a1[1000][1000];
int a2[1000][1000];
int r[1000][1000];
pthread_t threadid;
struct arrayindex {
int s_in;
int e_in;
};
struct arrayindex obj1;
void* fun1(void* arg)
{
    obj1.s_in=0;
    obj1.e_in=250;
    cout<<obj1.s_in<<endl;
    cout<<obj1.e_in<<endl;
for(int i=obj1.s_in;i<obj1.e_in;i++)
{
    for(int j=obj1.s_in;j<obj1.e_in;j++)
    {
        for(int col=obj1.s_in;j<obj1.e_in;col++)
    {

        r[i][j] += a1[i][col] * a2[col][j];
    }

    }
}

cout << endl << "Output Matrix: " << endl;
   for(int i=obj1.s_in;i<obj1.e_in;i++)
{
    for(int j=obj1.s_in;j<obj1.e_in;j++)
    {
   
    
        cout << " " << r[i][j];
        
    }
    cout<<endl;

}
pthread_exit(NULL);
}
int main(int argc,char *argv[])
{
     srand((unsigned) time(0));
for(int i=0;i<1000;i++)
{
    for(int j=0;j<1000;j++)
    {
        a1[i][j]=1+rand()%3;
    }
}
for(int i=0;i<1000;i++)
{
    for(int j=0;j<1000;j++)
    {
        a2[i][j]=1+rand()%4;
    }
}


pthread_create(&threadid,NULL,fun1,&obj1);
pthread_join(threadid,NULL);

}h
