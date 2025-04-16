#include<stdio.h>
 float x[20];
 float tp;
 void knapsack(int n, float wt[], float val[],float cap)
 {
      int i,j;
      float u = cap;
      for(i=0;i<n;i++)
      {
          x[i]=0.0;
      }
      for(i=0;i<n;i++)
      {
          if(wt[i]>u)
            break;
          else
          {
              x[i]=1.0;
              tp=tp+val[i];
              u=u-wt[i];
          }
      }
      if(i<n)
        x[i]=u/wt[i];

      tp=tp+(x[i]*val[i]);

 }
int main()
{
    float weight[20],profit[20],capacity;
    char name[20][20];
    float ratio[20],temp;
    char temp1[20];
    int i,j,n;

    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        scanf("%s",name[i]);
        scanf("%f",&weight[i]);
        scanf("%f",&profit[i]);
    }
    scanf ("%f\n", &capacity);

    for(i=0;i<n;i++)
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
 knapsack(n,weight,profit,capacity);

 for(int i=0;i<n;i++)
 {
     printf("%s",name[i]);
     printf("%f",x[i]);
     printf("%f",profit[i]*x[i]);
 }
 printf("\n %f", tp);

}
