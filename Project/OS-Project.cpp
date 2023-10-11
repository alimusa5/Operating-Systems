#include<iostream> 
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>
#include<sys/wait.h>
#include<string.h>

using namespace std;

int fd3[2];
int x = 0;
int c = 1;
int w = 1;
int daily_waiter_sales= 0;
int daily_sale[3] = {0};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void *serving(void *argv)
{

cout<<"Waiter # "<<w<<" is serving the order."<<endl;
w++;

pthread_exit(NULL);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void *cooking(void *argv)
{

cout<<"Cook # "<<c<<" is preparing the order."<<endl;
c++;

pthread_t waiter_id;

pthread_create( &waiter_id , NULL , serving , NULL ) ;
pthread_join( waiter_id , NULL); 

pthread_exit(NULL);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void showmenu()
{ 
int order[3]={0};
int button;
int i = 0;
do{
cout<<endl;
cout<<"______________________MENU___________________________"<<endl;
cout<<"Following are the dishes we serve in our restaurant : "<<endl;
cout<<"Dish number : Dish name : Price  : Preparation time   "<<endl;
cout<<"     1      : Burger    : RS.400 : 15 minute "<<endl;
cout<<"     2      : Pizza     : RS.800 : 20 minute "<<endl;
cout<<"     3      : Pasta     : RS.600 : 25 minute "<<endl;
cout<<"     4      : Steak     : RS.500 : 10 minute "<<endl;
cout<<endl;		
cout<<"To select the particular dish for order select the number of that dish. "<<endl;
cout<<"Please place your order here : "<<endl;
cin>>order[i];
 
if(order[i] == 0 || order[i] > 4)
{

do
{
cout<<"Please enter the correct option! : "<<endl;
cin>>order[i];
}
while(order[i] == 0 || order[i] > 4); 

}
i++;

cout<<"To add something in your order press '1' and to end and confirm your order press '0' : "<<endl;
cin>>button;
}
while(button);

cout<<"Thankyou for placing your order <3 ! "<<endl;
cout<<endl;

write( fd3[1] , &order , sizeof(order));

//cout<<order[0]<<"  "<<order[1]<<" "<<order[2]<<endl;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void * management( void *argv )
{

int buffer1[100];
char buffer2[100] = {""};
int buffer3[3] = { 0 };
char cus_name[100] = {""};
int cus_id;
int fd1[2];
int fd2[2];

pipe(fd1);
pipe(fd2);
pipe(fd3);

pid_t pid = fork();

if(pid < 0)
{
cout<<"Process not created!"<<endl;
}

else if(pid == 0)
{
close ( fd1[0] );
close ( fd2[0] );

cout<<endl;
cout<<"HI! I am the manager of this restaurant. "<<endl;
cout<<endl;
cout<<"----------------------------------------------"<<endl;
cout<<"Please tell me your name : "<<endl;
read( 0 , cus_name , sizeof(cus_name) );

cout<<"Now, please tell me your id : "<<endl;
cin>>cus_id;

write( fd1[1] , cus_name , sizeof(cus_name) );
write( fd2[1] , &cus_id  , sizeof(cus_id) );

}

else if(pid > 0)
{

close ( fd1[1] );
close ( fd2[1] );

wait(0);

read ( fd1[0] , buffer2 , sizeof(buffer2) ); 
read ( fd2[0] , &buffer1 , sizeof(buffer1));

cout<<endl;
cout<<"The name of the customer is : "<<buffer2<<"and the id of the customer is : "<<*buffer1<<endl;

showmenu();/////////////////////////////

read( fd3[0] , &buffer3 , sizeof(buffer3));

pthread_t cook_id[3];


if(buffer3[1] == 0)
{
for(int i = 0 ; i < 1 ; i++)
{

pthread_create( &cook_id[i] , NULL , cooking , NULL ) ;
pthread_join( cook_id[i] , NULL); 
if(w > 3)
{
w = 1;
}
}
}
else if(buffer3[2] == 0 )
{
for(int i = 0 ; i < 2 ; i++)
{

pthread_create( &cook_id[i] , NULL , cooking , NULL ) ;
pthread_join( cook_id[i] , NULL); 
if(w > 3)
{
w = 1;
}

}
}
else 
{

for(int i = 0 ; i < 3 ; i++)
{
pthread_create( &cook_id[i] , NULL , cooking , NULL ) ;
pthread_join( cook_id[i] , NULL); 
if(w > 3)
{
w = 1;
}
}

}


int o1 = buffer3[0];
int o2 = buffer3[1];
int o3 = buffer3[2];
int total = 0;

if( o1 == 1 && o2 == 0 && o3 == 0 )
{
total = 400;
}
else if( o1 == 2 && o2 == 0 && o3 == 0 )
{
total = 800;
}
else if( o1 == 3 && o2 == 0 && o3 == 0 )
{
total = 600;
}
else if( o1 == 4 && o2 == 0 && o3 == 0 )
{
total = 500;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
else if( o1 == 1 && o2 == 1 && o3 == 0 )
{
total = 800;
}
else if( o1 == 1 && o2 == 2 && o3 == 0 )
{
total = 1200;
}
else if( o1 == 1 && o2 == 3 && o3 == 0 )
{
total = 1000;
}
else if( o1 == 1 && o2 == 4 && o3 == 0 )
{
total = 900;
}
///////////////////////////////////////////
else if( o1 == 2 && o2 == 1 && o3 == 0 )
{
total = 1200;
}
else if( o1 == 2 && o2 == 2 && o3 == 0 )
{
total = 1600;
}
else if( o1 == 2 && o2 == 3 && o3 == 0 )
{
total = 1400;
}
else if( o1 == 2 && o2 == 4 && o3 == 0 )
{
total = 1300;
}
///////////////////////////////////////////
else if( o1 == 3 && o2 == 1 && o3 == 0 )
{
total = 1000;
}
else if( o1 == 3 && o2 == 2 && o3 == 0 )
{
total = 1400;
}
else if( o1 == 3 && o2 == 3 && o3 == 0 )
{
total = 1200;
}
else if( o1 == 3 && o2 == 4 && o3 == 0 )
{
total = 1100;
}
////////////////////////////////////////////
else if( o1 == 4 && o2 == 1 && o3 == 0 )
{
total = 900;
}
else if( o1 == 4 && o2 == 2 && o3 == 0 )
{
total = 1300;
}
else if( o1 == 4 && o2 == 3 && o3 == 0 )
{
total = 1100;
}
else if( o1 == 4 && o2 == 4 && o3 == 0 )
{
total = 1000;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
else if( o1 == 1 && o2 == 1 && o3 == 1 )
{
total = 1200;
}
else if( o1 == 1 && o2 == 1 && o3 == 2 )
{
total = 1600;
}
else if( o1 == 1 && o2 == 1 && o3 == 3 )
{
total = 1400;
}
else if( o1 == 1 && o2 == 1 && o3 == 4 )
{
total = 1300;
}
//////////////////////////////////////////////
else if( o1 == 1 && o2 == 2 && o3 == 1 )
{
total = 1600;
}
else if( o1 == 1 && o2 == 2 && o3 == 2 )
{
total = 2400;
}
else if( o1 == 1 && o2 == 2 && o3 == 3 )
{
total = 1800;
}
else if( o1 == 1 && o2 == 2 && o3 == 4 )
{
total = 1700;
}
//////////////////////////////////////////////
else if( o1 == 1 && o2 == 3 && o3 == 1 )
{
total = 1400;
}
else if( o1 == 1 && o2 == 3 && o3 == 2 )
{
total = 1800;
}
else if( o1 == 1 && o2 == 3 && o3 == 3 )
{
total = 1600;
}
else if( o1 == 1 && o2 == 3 && o3 == 4 )
{
total = 1500;
}
//////////////////////////////////////////////
else if( o1 == 1 && o2 == 4 && o3 == 1 )
{
total = 1300;
}
else if( o1 == 1 && o2 == 4 && o3 == 2 )
{
total = 1700;
}
else if( o1 == 1 && o2 == 4 && o3 == 3 )
{
total = 1500;
}
else if( o1 == 1 && o2 == 4 && o3 == 4 )
{
total = 1400;
}
////////////////////////////////////////////////////////////////////
else if( o1 == 2 && o2 == 1 && o3 == 1 )
{
total = 1600;
}
else if( o1 == 2 && o2 == 1 && o3 == 2 )
{
total = 2000;
}
else if( o1 == 2 && o2 == 1 && o3 == 3 )
{
total = 1800;
}
else if( o1 == 2 && o2 == 1 && o3 == 4 )
{
total = 1700;
}
//////////////////////////////////////////////
else if( o1 == 2 && o2 == 2 && o3 == 1 )
{
total = 2000;
}
else if( o1 == 2 && o2 == 2 && o3 == 2 )
{
total = 2400;
}
else if( o1 == 2 && o2 == 2 && o3 == 3 )
{
total = 2200;
}
else if( o1 == 2 && o2 == 2 && o3 == 4 )
{
total = 2100;
}
//////////////////////////////////////////////
else if( o1 == 2 && o2 == 3 && o3 == 1 )
{
total = 1800;
}
else if( o1 == 2 && o2 == 3 && o3 == 2 )
{
total = 2200;
}
else if( o1 == 2 && o2 == 3 && o3 == 3 )
{
total = 2000;
}
else if( o1 == 2 && o2 == 3 && o3 == 4 )
{
total = 1900;
}
//////////////////////////////////////////////
else if( o1 == 2 && o2 == 4 && o3 == 1 )
{
total = 1700;
}
else if( o1 == 2 && o2 == 4 && o3 == 2 )
{
total = 2100;
}
else if( o1 == 2 && o2 == 4 && o3 == 3 )
{
total = 1900;
}
else if( o1 == 2 && o2 == 4 && o3 == 4 )
{
total = 1800;
}
////////////////////////////////////////////////////////////////
else if( o1 == 3 && o2 == 1 && o3 == 1 )
{
total = 1400;
}
else if( o1 == 3 && o2 == 1 && o3 == 2 )
{
total = 1800;
}
else if( o1 == 3 && o2 == 1 && o3 == 3 )
{
total = 1600;
}
else if( o1 == 3 && o2 == 1 && o3 == 4 )
{
total = 1500;
}
//////////////////////////////////////////////
else if( o1 == 3 && o2 == 2 && o3 == 1 )
{
total = 1800;
}
else if( o1 == 3 && o2 == 2 && o3 == 2 )
{
total = 2200;
}
else if( o1 == 3 && o2 == 2 && o3 == 3 )
{
total = 2000;
}
else if( o1 == 3 && o2 == 2 && o3 == 4 )
{
total = 1900;
}
//////////////////////////////////////////////
else if( o1 == 3 && o2 == 3 && o3 == 1 )
{
total = 1600;
}
else if( o1 == 3 && o2 == 3 && o3 == 2 )
{
total = 2000;
}
else if( o1 == 3 && o2 == 3 && o3 == 3 )
{
total = 1800;
}
else if( o1 == 3 && o2 == 3 && o3 == 4 )
{
total = 1700;
}
//////////////////////////////////////////////
else if( o1 == 3 && o2 == 4 && o3 == 1 )
{
total = 1500;
}
else if( o1 == 3 && o2 == 4 && o3 == 2 )
{
total = 1900;
}
else if( o1 == 3 && o2 == 4 && o3 == 3 )
{
total = 1700;
}
else if( o1 == 3 && o2 == 4 && o3 == 4 )
{
total = 1600;
}
/////////////////////////////////////////////////////////////////
else if( o1 == 4 && o2 == 1 && o3 == 1 )
{
total = 1300;
}
else if( o1 == 4 && o2 == 1 && o3 == 2 )
{
total = 1700;
}
else if( o1 == 4 && o2 == 1 && o3 == 3 )
{
total = 1500;
}
else if( o1 == 4 && o2 == 1 && o3 == 4 )
{
total = 1400;
}
//////////////////////////////////////////////
else if( o1 == 4 && o2 == 2 && o3 == 1 )
{
total = 1700;
}
else if( o1 == 4 && o2 == 2 && o3 == 2 )
{
total = 2100;
}
else if( o1 == 4 && o2 == 2 && o3 == 3 )
{
total = 1900;
}
else if( o1 == 4 && o2 == 2 && o3 == 4 )
{
total = 1800;
}
//////////////////////////////////////////////
else if( o1 == 4 && o2 == 3 && o3 == 1 )
{
total = 1500;
}
else if( o1 == 4 && o2 == 3 && o3 == 2 )
{
total = 1900;
}
else if( o1 == 4 && o2 == 3 && o3 == 3 )
{
total = 1700;
}
else if( o1 == 4 && o2 == 3 && o3 == 4 )
{
total = 1600;
}
//////////////////////////////////////////////
else if( o1 == 4 && o2 == 4 && o3 == 1 )
{
total = 1400;
}
else if( o1 == 4 && o2 == 4 && o3 == 2 )
{
total = 1800;
}
else if( o1 == 4 && o2 == 4 && o3 == 3 )
{
total = 1600;
}
else if( o1 == 4 && o2 == 4 && o3 == 4 )
{
total = 1500;
}
/////////////////////////////////////////////////////////////////
cout<<endl;
cout<<"Your total bill is : "<<total<<endl;


daily_sale[x] = total;
x++;
/////////////////////////////////////////////////////////////////
if(o1 == 1 || o2 == 1 || o3 == 1 )
{
daily_waiter_sales += 400; 
}

if(o1 == 2 || o2 == 2 || o3 == 2 )
{
daily_waiter_sales += 800; 
}

if(o1 == 3 || o2 == 3 || o3 == 3 )
{
daily_waiter_sales += 600; 
}

if(o1 == 4 || o2 == 4 || o3 == 4 )
{
daily_waiter_sales += 500; 
}

//cout<<daily_sale[0]<<" "<<daily_sale[1]<<" "<<daily_sale[2]<<endl;
}
pthread_exit(NULL);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
int customer;
int manager =  1;
int waiter  =  3;
int cook    =  3;
pthread_t thread_id[2];
int daily_sales = 0;


cout<<"How many customers do you want to have ? : "<<endl;
cin>>customer;

cout<<"How many cooks do you want to have ? : "<<endl;
cin>>cook;

cout<<"How many waiters do you want to have ? : "<<endl;
cin>>waiter;


cout<<"         Welcome to the restaurant!         "<<endl;
cout<<"--------------------------------------------"<<endl;

for(int i = 0 ; i < customer  ; i++)
{

pthread_create( &thread_id[i] , NULL , management , NULL ) ;
pthread_join( thread_id[i] , NULL); 
c = 1;
}

for(int z = 1 ; z <= customer ; z++)
{
cout<<"Customer # "<<z<<" , you have recieved your order. "<<endl;
}
cout<<"Thankyou for ordering from this restaurant!"<<endl;

for(int y = 0 ; y < customer ; y++)
{
daily_sales += daily_sale[y]; 
}

cout<<"The daily sale is : "<<daily_sales<<endl; 
cout<<"The daily waiters sale is : "<<daily_waiter_sales<<endl;
pthread_exit(NULL);

exit(0);
}






