#include<stdio.h>
#include <stdlib.h>
#include <string.h>

void naivesm(char *txt, char *pat)
{
    int m =strlen(pat);
    int n=strlen(txt);
    for(int i=0;i<n-m+1;i++)
    {
        int j;
        {
            for(j=0;j<m;j++)
            {
                if(txt[i+j]!=pat[j])
                    break;
            }
            if(j==m)
            {
                printf("pattern found at shift %d\n",i-1);
            }
        }
    }
}
int main()
{
    char txt[100],pat[100];

    printf("Enter the text:");
    fgets(txt,sizeof(txt),stdin);
    txt[strcspn(txt,"\n")]='\0';

    printf("Enter the pattern:");
    fgets(pat,sizeof(pat),stdin);
    pat[strcspn(pat,"\n")]='\0';

    naivesm(txt,pat);
}
