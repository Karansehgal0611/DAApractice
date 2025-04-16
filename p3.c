#include<stdio.h>
#include<limits.h>
typedef struct
{
    int start;
    int end;
    int sum;
} maxarr;

maxarr MaxcrossSum(int arr[],int low,int mid,int high)
{
    maxarr result;
    int leftsum=INT_MIN;
    int sum=0;
    int leftidx=mid;

    for(int i=mid;i>=low;i--)
    {
        sum+=arr[i];
        if(sum>leftsum)
        {
            leftsum=sum;
            leftidx=i;
        }
    }

    int rightsum=INT_MIN;
     sum=0;
    int rightidx=mid+1;

    for(int i=mid+1;i<=high;i++)
    {
        sum+=arr[i];
        if(sum>rightsum)
        {
            rightsum=sum;
            rightidx=i;
        }
    }
    result.start=leftidx;
    result.end=rightidx;
    result.sum=leftsum+rightsum;

    return result;
}
 maxarr maxSubsum(int arr[],int low,int high)
 {
     maxarr result;
     if(low==high)
     {
         result.start=low;
         result.end=high;
         result.sum=arr[low];
         return result;
     }

     if(high>low)
     {
         int mid=low+(high-low)/2;
         maxarr left=maxSubsum(arr,low,mid);
         maxarr right=maxSubsum(arr,mid+1,high);
         maxarr cross=MaxcrossSum(arr,low,mid,high);

         if(left.sum>=right.sum && left.sum>=cross.sum)
         {
             return left;
         }
          else if(right.sum>=left.sum && right.sum>=cross.sum)
         {
             return right;
         }
         else
         {
             return cross;
         }
     }
 }
 int main()
 {
     int n;
     scanf("%d",&n);
     int arr[n];
     for(int i=0;i<n;i++)
     {
         scanf("%d",&arr[i]);
     }
     maxarr g=maxSubsum(arr,0,n-1);
     printf("Maximum subarray sum: %d\n", g.sum);
    printf("Starting position: %d\n", g.start);
    printf("Ending position: %d\n", g.end);
    return 0;
 }
