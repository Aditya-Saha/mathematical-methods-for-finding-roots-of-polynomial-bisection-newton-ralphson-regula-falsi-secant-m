#include<stdio.h>
#include<stdlib.h>
typedef struct bisection
{
  int itr;
  double x0, x1, mid, fx0, fx1 ,fmid, error;
  struct bisection *next;
}bisect;
typedef struct raphson
{
  int itr;
  double x0, x1, fx0, fx1, error;
  struct raphson *next;
}raphson;

typedef struct falsi
{
  int itr;
  double x0, x1,x2, fx0, fx1, fx2, error;
  struct falsi *next;
}falsi;

typedef struct secant
{
  int itr;
  double x0, x1,x2, fx0, fx1, fx2, error;
  struct secant *next;
}secant;

int main(void)
{
  //DECLARATIONS OF VARIABLES
  double arr[10], tolerance;
  int i, order, power, counter, ch, bitr, sitr, fitr, ritr;
  double x, polySum;
  
  //STRUCTURE POINTERS DECLARATIONS
  bisect *headbi ;
  raphson *headraph;
  falsi *headfal;
  secant *headsec;

  //prototypes of function
  int function(double arr[],int order,double x,double *y);
  int derifunction(double arr[],int order,double x,double *y);
  int bisection(bisect **headbi, double tolerance ,double arr[],int order,int *bitr);
  int bisection_display(bisect* headbi);
  int raphson_method(raphson **head, double tolerance ,double arr[],int order,int *ritr);
  int raphson_display(raphson* headraph);
  int falsi_method(falsi **headfal, double tolerance ,double arr[],int order,int *fitr);
  int falsi_display(falsi* headfal);
  int secant_method(secant **head, double tolerance ,double arr[],int order,int *sitr);
  int secant_display(secant* head);
  

  char control;//declaration of char type variables 
 
  control='y';//storing y initilally


  while(1)
  {
   system("clear");

   printf("\t\tThe menu of operations are listed below ");//showing menu
   printf("\n1. Set Expression\n2. Set Tolerance\n3. Compute\n4.Exit");
   printf("\n\nEnter choice:");

   scanf("%d",&ch);//taking choice of user as input

   getchar();
   
   switch(ch)
   {
     case 01:printf("Enter the order of the polynomial \n");
     scanf("%d", &order);//TAKING ORDER OF POLYNOMIAL INPUT

     counter=order;
     for (i = 0; i <= order; i++)
     {
        printf("\nEnter coefficient of x^%d=",counter);
        scanf("%lf", &arr[i]);//coefficient input

        counter=counter-1;
     }
     break;

     case 02:printf("\nEnter the tolerance value for the given polynomial calculation:");
     scanf("%lf",&tolerance);//taking tolerance value
     break;

     case 03:headbi=NULL;//INITIALISING POINTER TO NULL
     //function call to calculate using bisection method
     bisection(&headbi ,tolerance,arr, order,&bitr);
     printf("\nTABLE 1:\n\t\tResult of bisection Method\n");
     //function call to display results
     bisection_display(headbi);

     headraph=NULL;//INITIALISING POINTER TO NULL
     raphson_method(&headraph ,tolerance,arr, order,&ritr);
     printf("\nTABLE 2:\n\t\tResult of Newton-Raphson Method\n");
     //function call to display results
     raphson_display(headraph);

     headfal=NULL;//INITIALISING POINTER TO NULL
     falsi_method(&headfal,tolerance,arr, order,&fitr);
     printf("\nTABLE 3:\n\t\tResult of Regula-Falsi Method\n"); 
     //function call to display results
     falsi_display(headfal);

     headsec=NULL;//INITIALISING POINTER TO NULL
     secant_method(&headsec,tolerance,arr, order,&sitr);
     printf("\nTABLE 4:\n\t\tResult of secant Method\n");
     //function call to display results
     secant_display(headsec);
     
     printf("\nTABLE 5:\n\t\tcomparisons\n");
     printf("Method\t\t\tNumber of iterations\n");
     printf("Bisection\t\t%d\nNewton-Ralphson\t\t%d\nRegula-Falsi\t\t%d\nSecantMethod\t\t%d\n",bitr,ritr,fitr,sitr);

     break;

     case 04:printf("Terminating the code......");
     return(1);
   }
    getchar();

    printf("\n\n press y to continue:");//asking user whether he wants to continue thwn to press y 

    control=getchar();   
    if(control!='y')//checking whether user pressed any other character other than y
    {
      break;//then break from the loop structure
    }

   }
  getchar();
  return(1);
}      
//-----------------------------------------------------------------------------------------------------------------------------
int function(double arr[],int order,double x,double *y)//to find value of function 
{
  int i;//DECLARATIONS OF VARIABLE

  *y = arr[0];
  i=1;
  while (i <= order)
  {
    *y =(((*y) * x) + arr[i]);//calculating value
    i=(i+1);
  }
  return(1);
}
int derifunction(double arr[],int order,double x,double *y)//to find value of derivative function 
{
  int i, j, counter;//DECLARATIONS OF VARIABLE
  double temp;//DECLARATIONS OF VARIABLE
  
  i=0;  
  *y=0;

  counter=order;
  while (i <=order)
  { 
    j=1;
    temp=1;
    while(j<counter)
    {
      temp=temp*x;
      j=(j+1);
    }
    *y =*y+(((arr[i]) *counter) * temp);//calculating value
    i=(i+1);
    counter=(counter-1);
  }  
  return(1);
}  
//-----------------------------------------------------------------------------------------------------------------------------
int bisection(bisect **head, double tolerance ,double arr[],int order,int *bitr)
{
  //DECLARATIONS OF VARIABLES AND STRUCTURE POINTER
  double x0, x1, mid, fmid, fx0, fx1 , error,fx;
  int i;
  bisect  *ptr, *temp;

  int absolute(double *x);//prototype of functions
  int function(double arr[],int order,double x,double *y);
  int derifunction(double arr[],int order,double x,double *y);
  
  *bitr = 0;
  i=-1;
  
  //loop to find the interval of root 
   do
  {
    i=(i+1);
    function(arr ,order,i,&fx0);
    function(arr ,order,(i+1),&fx1);
  }while((fx0*fx1)>0);

  if(fx0<0)
  {
    x0=i;
    x1=(i+1);
  }
  else
  {
    x0=(i+1);
    x1=i;
  }
 

  error = (x1 - x0);//calculating error
  absolute(&error);
  while(error > tolerance)
  {
     *bitr=(*bitr+1);//incrementing iteration
     mid =( (x0+x1)/2);//calculating mid

     //function call
     function(arr ,order, mid,&fmid);
     function(arr ,order,x0,&fx0);
     function(arr ,order,x1,&fx1);
   
     if(*head== NULL)
     {
       *head=(bisect*)malloc(sizeof(bisect));//creating node
       ptr=*head;
       ptr->next=NULL;
     }
     else
     {
       temp=(bisect*)malloc(sizeof(bisect));//creating node
       ptr->next=temp;
       ptr=temp;
       ptr->next=NULL;
     }
     //storing repective values in the structure
     ptr->itr=*bitr;
     ptr->x0=x0;
     ptr->x1=x1;
     ptr->mid=mid;
     ptr->fmid=fmid;
     ptr->fx0=fx0;
     ptr->fx1=fx1;
     ptr->error=error;

     if(fmid < 0)
     {
	x0 = mid;//updating x0
     }
     else
     {
        x1 = mid;//updating x1
     }
     
     error = (x1-x0); //calculating error
     absolute(&error);
  }

  return(1);
}
int bisection_display(bisect* head)//function to print result table
{
  bisect *temp;
  temp = head;
  printf("Itr  X1       X2      MID    F(x1)\t F(x2)\t  F(MID)  ERROR\n");
  printf("---------------------------------------------------------------\n");
  while(temp!= NULL)
  {
   printf("%d   %0.4lf   %0.4lf  %0.4lf  %0.4lf\t%0.4lf\t%0.4lf\t %0.4lf\n",temp->itr,temp->x0,temp->x1,temp->mid ,temp->fx0,temp->fx1,temp->fmid,temp->error);
    temp = temp->next;
  }
  return (1);
}
//---------------------------------------------------------------------------------------------------------------------------------
int raphson_method(raphson **head, double tolerance ,double arr[],int order,int *ritr)
{
  //DECLARATIONS OF VARIABLES AND STRUCTURE POINTER
  int i;
  double x0, x1, fx0, fd, fx1, h, e;
  raphson * ptr, *temp;

  //prototype of functions
  int absolute(double *x);
  int function(double arr[],int order,double x,double *y);
  int derifunction(double arr[],int order,double x,double *y);

  *ritr=0;
  i=-1;
  
  //loop to find the interval of root 
  do
  {
    i=i+1;
    function(arr ,order,i,&fx0);
    function(arr ,order,(i+1),&fx1);
  }while((fx0*fx1)>0);

  x0=i;
  derifunction(arr , order, x0, &fd);//function call to find fd
  
  h=(fx0/fd);
  x1=(x0-h);//calculating x1

  e=(x1-x0);//calculating error
  absolute(&e);

  while(e>tolerance)
  
  {
    *ritr=(*ritr+1);//incrementing iteration
    function(arr ,order,x1,&fx1);//function call to find fx1
   
    if(*head== NULL)
    {
       *head=(raphson*)malloc(sizeof(raphson));//creating node
       ptr=*head;
       ptr->next=NULL;
    }
    else
    {
      temp=(raphson*)malloc(sizeof(raphson));//creating node
      ptr->next=temp;
      ptr=temp;
      ptr->next=NULL;
    }
    //storing repective values in the structure
    ptr->itr=*ritr;
    ptr->x0=x0;
    ptr->x1=x1;
    ptr->fx0=fx0;
    ptr->fx1=fx1;
    ptr->error=h;

    x0=x1;//updating x0

    fx0=fx1;//updating fx0

    derifunction(arr , order, x0, &fd);

    h=(fx0/fd);

    x1=(x0-h);//calculating x1

    e=(x1-x0);
    absolute(&e);   
  } 
 
  return(1);
}
int raphson_display(raphson* head)
{
  raphson *temp;
  temp = head;
  printf("Itr  X0       X1       F(x0)      F(x1)       ERROR\n");
  printf("------------------------------------------------------\n");
  while(temp!= NULL)
  {
   printf("%d   %0.4lf   %0.4lf   %0.4lf    %0.4lf      %0.4lf\n",temp->itr,temp->x0,temp->x1,temp->fx0,temp->fx1,temp->error);
    temp = temp->next;
  }
  return (1);
}
//-----------------------------------------------------------------------------------
int absolute(double *x)//function to find absolute value
{
  if(*x<0)
  {
    *x=-1**x;
  }
  else 
  {
    *x=*x;
  }
  return(1);
}
//-----------------------------------------------------------------------------------------------------------------------------
int falsi_method(falsi **head, double tolerance ,double arr[],int order,int *fitr)
{
  //DECLARATIONS OF VARIABLES AND STRUCTURE POINTER
  double x0, x1, x2, fx0, fx1, fx2, error, afx2;
  int i;  
  falsi *ptr ,*temp;

  
  //prototype of functions
  int absolute(double *x);
  int function(double arr[],int order,double x,double *y);
  int derifunction(double arr[],int order,double x,double *y);
  
  *fitr=0;
  i=-1;
  //loop to find the interval of root 
   do
  {
    i=i+1;
    function(arr ,order,i,&fx0);
    function(arr ,order,(i+1),&fx1);
  }while((fx1*fx0)>0);

  if(fx0<0)
  {
    x0=i;
    x1=(i+1);
  }
  else
  {
    x0=(i+1);
    x1=i;
  }
  //function call
  function(arr ,order,x0,&fx0);
  function(arr ,order,x1,&fx1);
  
  error=(x0-x1);//calculating error
  
   do
  {
  
     *fitr=(*fitr+1);//incrementing iteration
  
     x2=x0-((fx0*(x1-x0))/(fx1-fx0));//calculating x2

     function(arr ,order,x2,&fx2);//function call

     afx2=fx2;
     absolute(&afx2);
     
     if(*head==NULL)
     {
       *head=(falsi*)malloc(sizeof(falsi));//creating node
       ptr=*head;
       ptr->next=NULL;
     }
     else
     {
       temp=(falsi*)malloc(sizeof(falsi));//creating node
       ptr->next=temp;
       ptr=temp;
       ptr->next=NULL;
     }
     //storing repective values in the structure
     ptr->itr=*fitr;
     ptr->x0=x0;
     ptr->x1=x1;
     ptr->x2=x2;
     ptr->fx0=fx0;
     ptr->fx1=fx1;
     ptr->fx2=fx2;
     ptr->error=error;
  
     if(fx2<0)
     {  
       x0=x2;//updating variables
       fx0=fx2;
     }
     else
     {
       x1=x2;//updating variables
       fx1=fx2;
     }
       
     error=(x0-x1);
     //absolute(&error);
  }
   while(afx2>tolerance);

  return(1);
}
int falsi_display(falsi* head)
{
  //DECLARATIONS OF VARIABLES AND STRUCTURE POINTER
  falsi *temp;
  temp = head;
  printf("Itr  X0     X1      X2     F(x0)    F(x1)     F(X2)\tERROR\n");
  printf("-------------------------------------------------------------\n");
  while(temp!= NULL)
  {
    printf("%d  %0.4lf  %0.4lf  %0.4lf  %0.4lf  %0.4lf  %0.4lf  %0.4lf\n",temp->itr,temp->x0,temp->x1,temp->x2,temp->fx0,temp->fx1,temp->fx2,temp->error);
    temp = temp->next;
  }
  return (1);
}
//----------------------------------------------------------------------------------------------------------------------------
int secant_method(secant **head, double tolerance ,double arr[],int order,int *sitr)
{
  //DECLARATIONS OF VARIABLES AND STRUCTURE POINTER
  double x0, x1,x2, fx0, fx1, fx2, error;
  secant *ptr ,*temp;
  int i;

  //prototype of functions
  int absolute(double *x);
  int function(double arr[],int order,double x,double *y);

  *sitr=0;
  i=-1;
  
   do
  {
    i=(i+1);
    function(arr ,order,i,&fx0);
    function(arr ,order,(i+1),&fx1);
  }while((fx1*fx0)>0);

  x0=i;
  x1=(i+1);  
  
  //function(arr ,order,x0,&fx0);
  //function(arr ,order,x1,&fx1);
  
  error=(x0-x1);
  absolute(&error);
 
  while(error>tolerance)
  {
  
     *sitr=(*sitr+1);//incrementing iteration

     x2=x0-((fx0*(x1-x0))/(fx1-fx0));//calculating x2

     function(arr ,order,x2,&fx2);

     if(*head==NULL)
     {
       *head=(secant*)malloc(sizeof(secant));//creating node
       ptr=*head;
       ptr->next=NULL;
     }
     else
     {
       temp=(secant*)malloc(sizeof(secant));//creating node
       ptr->next=temp;
       ptr=temp;
       ptr->next=NULL;
     }
     //storing repective values in the structure
     ptr->itr=*sitr;
     ptr->x0=x0;
     ptr->x1=x1;
     ptr->x2=x2;
     ptr->fx0=fx0;
     ptr->fx1=fx1;
     ptr->fx2=fx2;
     ptr->error=error;  

     //updating variables
     x0=x1;
     x1=x2;
     fx0=fx1;
     fx1=fx2;
   
     error=(x0-x1);//calculating error
     absolute(&error);
  }
  return(1);
}

int secant_display(secant* head)
{
  //DECLARATIONS OF VARIABLES AND STRUCTURE POINTER
  secant *temp;
  temp = head;
  printf("Itr  X0     X1      X2     F(x0)    F(x1)     F(X2)\tERROR\n");
  printf("-------------------------------------------------------------\n");
  while(temp!= NULL)
  {
    printf("%d  %0.4lf  %0.4lf  %0.4lf  %0.4lf  %0.4lf  %0.4lf  %0.4lf\n",temp->itr,temp->x0,temp->x1,temp->x2,temp->fx0,temp->fx1,temp->fx2,temp->error);
    temp = temp->next;
  }
  return (1);
}
//---------------------------------------------------------------------------------------------------------------------------
