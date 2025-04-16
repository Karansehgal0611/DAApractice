#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct job{
  char id;
  int dead;
  int profit;
};

int compare(const void *a,const void *b){
  struct job* temp1 = (struct job*)a;
  struct job* temp2 = (struct job*)b;
  return (temp1->profit - temp2->profit);
}

int min(int num1,int num2){
  return (num1>num2)?num2:num1;
}

void printjobscheduling(struct job arr[],int n){
  qsort(arr,n,sizeof(struct job),compare);
  int result[n];
  bool slot[n];
  for(int i = 0; i<n ;i++)
    slot[i]=false;
  for( int i = 0 ; i< n ;i++ ){
    for ( int j = min(n,arr[i].dead)-1;j>=0;j--){
      if(slot[j]==false){
        result[j]=i;
        slot[j]=true;
        break;
      }
    }
  }
  for(int i = 0 ;i <n ;i++){
    if(slot[i]){
      printf("%c ",arr[result[i]].id);
    }
  }
}

int main(){
  int n;
  printf("Enter the no of jobs  : ");
  scanf("%d",&n);
  struct job arr[n];
  for(int i =0;i<n;i++){
    printf("Job %d (id,dead,profit)",i+1);
    scanf(" %c %d %d",&arr[i].id,&arr[i].dead,&arr[i].profit);
  }
  printf("Maximum profit sequence of jobs :\n");
  printjobscheduling(arr,n);
}
