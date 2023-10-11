//i190684  B
//Syed Muhammad Ali Musa Raza Jaffri
//OS assignment 1

#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <cstring>
#include <string.h>
using namespace std;

int main()
{

int rows = 5;
	
cout<<"Please enter the number of rows you would want to have : "<<endl;
cin>>rows;
	
	
	pid_t pid_1 = fork();
	
	if(pid_1 == 0)
	{
		
		for ( int i = 1 ; i <= rows ; i++)
		{
			cout<<" ";
			
			pid_t pid_2 = fork();
			
			if (pid_2 == 0)
			{
				for (int  j = 1; j <= rows  ; j++)
				{
					cout<<" ";
				rows--;
					
					pid_t pid_3 = fork();
					
					if (pid_3 == 0)
					{
						
						 for ( int k = 1 ; k <= i ; k++)
						{
						cout<<"* ";
						}
							 
					exit(0);
					}
					
					else if (pid_3 > 0)
					{
						wait (NULL);
					}
					
						
			exit(0);
			}
			
			}
			
			else if (pid_2 > 0)
			{
				wait (NULL);
			}
		
		cout<<endl;
		}	
		
	exit(0);
		
	}
	
	else if (pid_1 > 0)
	{
		wait (NULL);
	}	

	

}
