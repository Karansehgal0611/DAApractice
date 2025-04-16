# include<stdio.h>
# include<string.h>
float x[20];tp= 0;
void knapsack(int n, float weight[], float profit[], float capacity)
{

 int i, j, u;
 u=capacity;

 for (i=0;i<n;i++)
     x[i]=0.0;

 for (i=0;i<n;i++)
 {
 if(weight[i]>u)
      break;
 else
     {
     x[i]=1.0;
     tp= tp+profit[i];
     u=u-weight[i];
     }
 }

 if(i<n)
       x[i]=u/weight[i];

 tp= tp + (x[i]*profit[i]);
}
void main()
{
 float weight[20], profit[20], capacity;
 int n, i ,j;
 float ratio[20], temp;
 char temp1[20];
 char name[20][20];

 printf("Enter the no. of objects:- ");
 scanf("%d\n",&n);


 for (i=0; i<n; i++)
 {
     printf (" Enter the name ,weight and profits of each object:- ");
     scanf("%s",name[i]);
     scanf("%f",&weight[i]);
     scanf("%f",&profit[i]);
 }

 printf ("enter the capacity of knapsack:- ");
 scanf ("%f\n", &capacity);

 for (i=0; i<n; i++)
 {
 ratio[i]=profit[i]/weight[i];
 }

 for(i=0; i<n; i++)
 {
    for(j=i+1;j< n; j++)
    {
      if(ratio[i]<ratio[j])
      {
      temp= ratio[j];
      ratio[j]= ratio[i];
      ratio[i]= temp;

     temp= weight[j];
     weight[j]= weight[i];
     weight[i]= temp;

     temp= profit[j];
     profit[j]= profit[i];
     profit[i]= temp;

     strcpy(temp1,name[j]);
     strcpy(name[j],name[i]);
     strcpy(name[i],temp1);
     }
   }
 }

 knapsack(n, weight, profit, capacity);
 getch();
 for(int i=0;i<n;i++)
 {
     printf("%s",name[i]);
     printf("%f",x[i]);
     printf("%f",profit[i]*x[i]);
 }
 printf("\n %f", tp);
}
