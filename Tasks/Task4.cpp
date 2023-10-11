#include <pthread.h>
#include <stdio.h>
#include<stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include<sys/wait.h>
#include<string.h>
#include<unistd.h>

pthread_t t1,t2,t3,t4,t5;
char word[]={" "};

void *palindromic()
{
        int flag = 0;
        int n=sizeof(word);
        
    for (int i = 0; i <= n / 2 && n != 0; i++) {
        if (word[i] != word[n - i - 1]) {
            flag = 1;
            break;
        }
    }
 
 
    if (flag == 1)
    {  
        cout<<"Not Palindrome"<<endl;
    }
    
    else
    {
        cout<<"Palindrome"<<endl;
    }
}

void *reverse()
{

    cout<<"Reverse  string"<<endl;
    
    int len=sizeof(word);
    for(int i=len+1;i>=0;i--)
    {
        cout<<" %c"<<endl ,word[i];
    }
    pthread_exit(NULL);

}
void *ASCCii()
{
  
    cout<<"ASSCII OF a string"<<endl;
  
    for(int i=0;word[i]!='\0';i++)
    {
        cout<<"%d",word[i];
    }
    pthread_exit(NULL);   
}
void *input()
{

    
    coutz<<"Enter a string"<<endl;
    cout<<" %s", word;
    cout<<" %s",word;
    pthread_exit(NULL);

}
int main()
{

pthread_create(&t1,NULL,input,NULL);
pthread_join(t1,NULL);

pthread_create(&t2,NULL,ASCCii,NULL);
pthread_join(t2,NULL);


pthread_create(&t3,NULL,reverse,NULL);
pthread_join(t3,NULL);
pthread_create(&t4,NULL,palindromic,NULL);
pthread_join(t4,NULL);
    

}
