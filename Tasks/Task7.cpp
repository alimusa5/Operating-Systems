//i190684  B
//Syed Muhammad Ali Musa Raza Jaffri
//OS assignment 1

#include<iostream>
#include<unistd.h>
#include<string.h>
#include<sys/wait.h>
using namespace std;

int main()
{

int P = 1;
int C = 1;
int n;
cout<<"Enter the number of processes you want to call : "<<endl;
cin>>n;



for(int a = 0 ; a < n ; a++)
{

pid_t pid = fork();

if(pid > 0 )  // parent 
{

cout<<"Parent process : "<<"P"<<P<<endl;
cout<<"The process id is : "<<getpid()<<endl;
cout<<"The process id of its parent is : "<<getppid()<<endl;
P++;
}

else if ( pid == 0 ) //child
{

cout<<"Child process : "<<"C"<<C<<endl;
cout<<"The process id is : "<<getpid()<<endl;
C++;
}

}
return 0;
}

