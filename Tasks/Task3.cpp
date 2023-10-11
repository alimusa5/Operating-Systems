#include<iostream>
#include<unistd.h>
#include<string.h>
#include<sys/wait.h>

using namespace std;

int main()
{

int fd[2];
int fd1[2];
pid_t childpid;


char string1[50] = "";
char string2[50] = "";
char readbuffer1[50];
char readbuffer2[50];

int oldfd1= pipe(fd);
int oldfd2=pipe(fd1);

int newfd =dup(oldfd1);
int newfd1=dup(oldfd2);

///////////////////////////////////////////////////////////////////////////////////////////
if (oldfd1 < 0)
{

cout << "Error while creating file" ;
exit(1);

}
childpid = fork();
int c = 0;
for( ; ; )
{ 
///////////////////////////////////////////////////////////////////////////////////////////
if ( childpid < 0)
{

cout<<"Error in fork"<<endl ;
exit(1);
}

///////////////////////////////////////////////////////////////////////////////////////////
else if ( childpid > 0 )
{
///////////////////////////////////////////////////////////////////////////////////////////
close(fd[0]);
close (fd1[1]);
cout<<"Enter string 1 : ";
cin.getline(string1 ,50 );
if( string1[0] == 'Q' || string1[0] == 'q' )
{
    return 0;

}
write ( fd[1] , string1 , sizeof ( string1 ) );
read ( fd1[0] , readbuffer2 , sizeof ( readbuffer2 ) ) ;

cout<<"String 2 recieved : "<<readbuffer2<<endl;

}


/////////////////////////////////////////////////////////////////////////////////////////////
else if ( childpid == 0 )
{
////////////////////////////////////////////////////////////////////////////////////////////
close (fd[1] );

/////////////////////////////////////////////////////////////////////////////////////////////
close(fd1[0]);
read ( fd[0] , readbuffer1 , sizeof ( readbuffer1 ) ) ;
cout<<"String 1 recieved : "<<readbuffer1<<endl;
cout<<"Enter string 2 : ";
cin.getline(string2 , 50 );

if( string2[0] == 'Q' || string2[0] == 'q' )
{
return 0;
break;

}

write ( fd1[1] , string2 , sizeof ( string2 ) );
wait(NULL);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

return 0;
}
