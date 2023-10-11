#include<iostream>
#include<unistd.h>
#include<string.h>
#include<sys/wait.h>

using namespace std;

int main()
{

int fd[2];
int  num = 0;
pid_t childpid;


char string[50] = "";
char readbuffer[50];

int result = pipe(fd);

if (result < 0)
{

cout << "Error while creating file" ;
exit(1);

}

childpid = fork();

for( ; ; )
{ 

if ( childpid < 0)
{

cout<<"Error in fork"<<endl ;
exit(1);
}


else if ( childpid > 0 )
{
close(fd[0]);




for(int i = 0 ; i < 50 ; i++)
{

cout<<"Enter text : ";
cin>>string[i];


if( string[i] == '.' || string[i] == '?' )
{
write ( fd[1] , string , sizeof ( string ) );
num++;
wait(NULL);
cout << "Sentence number "<<num<<" recieved by P2"<<endl;


break;

}

else if( string[i] == '#' )
{
char string[] = "Incomplete sentence recieved/n";
write ( fd[1] , string , sizeof ( string ) );
cout<<"P1 exiting"<<endl;
cout<<"P2 exiting"<<endl;
wait(NULL);

exit(0);

}

}

}


else if ( childpid == 0 )
{
close (fd[1]);

read ( fd[0] , readbuffer , sizeof ( readbuffer ) ) ;

cout<<"Sentence recieved : "<<readbuffer<<endl;
cout<<"Sentence number sent to P1 "<<endl;
exit(0);

}

}

return 0;
}
