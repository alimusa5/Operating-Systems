#include<iostream>
#include<unistd.h>
#include<string.h>
#include<sys/wait.h>

using namespace std;

int main()
{


int fd1=open("input.txt",O_ORDONLY);

if( fd1 < 1 )
{
cout<<"Error opening the file. "<<endl;
}

int newfd1 = dup(fd1);

char string1[50] = "";
char string2[50] = "";


int fd2=open("input.txt",O_WRONLY);
if( fd2 < 1 )
{
cout<<"Error opening the file. "<<endl;
}

int newfd2 = dup(fd2);


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
close(fd1[0]);


cout<<"Enter string 1 : ";
cin.getline(string1 , 50 );


if( string1 == "ali" )
{

exit(0);

}

else
{
write ( fd[1] , string1 , sizeof ( string1 ) );

wait(NULL);

}

close ( newfd );
read ( newfd , readbuffer2 , sizeof ( readbuffer2 ) ) ;

cout<<"String 2 recieved : "<<readbuffer2<<endl;

}


/////////////////////////////////////////////////////////////////////////////////////////////
else if ( childpid == 0 )
{
////////////////////////////////////////////////////////////////////////////////////////////
close ( fd[1] );


read ( newfd , readbuffer1 , sizeof ( readbuffer1 ) ) ;

cout<<"String 1 recieved : "<<readbuffer1<<endl;


/////////////////////////////////////////////////////////////////////////////////////////////
close(newfd);

cout<<"Enter string 2 : ";
cin.getline(string1 , 50 );

if( string2 == "ali" )
{

exit(0);

}

else
{


write ( newfd , string2 , sizeof ( string2 ) );

wait(NULL);

}

}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}




return 0;
}
