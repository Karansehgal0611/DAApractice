#include<stdio.h>
#include<stdlib.h>
//leaf nodes
struct minheapnode{
  char data;
  int freq;
  struct minheapnode *left,*right;
};
//collection of leaf nodes
struct minheap{
  int size;
  int cap;
  struct minheapnode** array;
};
//creation of new leaf node to the min heap
struct minheapnode* newnode(char data,int freq){
  struct minheapnode* temp= (struct minheapnode *)malloc(sizeof(struct minheapnode));
  temp->left=NULL;
  temp->right=NULL;
  temp->data=data;
  temp->freq=freq;
  return temp;
}
//creating a minheap of a certain capacity
struct minheap* createminheap(int cap){
  struct minheap* temp=(struct minheap*)malloc(sizeof(struct minheap));
  temp->size=0;
  temp->cap=cap;
  temp->array=(struct minheapnode*)malloc(cap*sizeof(struct minheapnode*));
}
//swaping two minheap nodes
void swapminheap(struct minheapnode** a,struct minheapnode** b){
  struct minheapnode *temp=*a;
  *a=*b;
  *b=temp;
}
//heapify function
void heapify(struct minheap* curheap,  int ind){
  int left=(2*ind)+1;
  int right=(2*ind)+2;
  int min=ind;
  if(left<curheap->size && curheap->array[left]->freq<curheap->array[min]->freq)
    min=left;
  if(right<curheap->size && curheap->array[right]->freq<curheap->array[min]->freq)
    min=right;
  if(min!=ind){
    swapminheap(&curheap->array[min],&curheap->array[ind]);
    heapify(curheap,min);
  }
}
//checks if the heap is of size 1
int isone(struct minheap* curheap){
  return(curheap->size==1);
}
//returns minimum value node from heap
struct minheapnode* extractmin(struct minheap* curheap){
  struct minheapnode* temp=curheap->array[0];
  curheap->array[0]=curheap->array[curheap->size-1];
  curheap->size--;
  heapify(curheap,0);
  return temp;
}
//insertion of newnode in minheap
void insertminheap(struct minheap* curheap,struct minheapnode* curnode){
  curheap->size++;
  int i=curheap->size-1;
  while(i && curnode->freq<curheap->array[(i-1)/2]->freq){
    curheap->array[i]=curheap->array[(i-1)/2];
    i=(i-1)/2;
  }
  curheap->array[i]= curnode;
}
//building minheap
void buildminheap(struct minheap* curheap){
  int n=curheap->size-1;
  int i;
  for(i=(n-1)/2;i>=0;--i){
    heapify(curheap,i);
  }
}
//function to print an array
void printarr(int arr[],int n){
  int i;
  for(i=0;i<n;i++){
    printf("%d",arr[i]);
  }
  printf("\n");
}
//check if leaf node
int isleaf(struct minheapnode* root){
  return !(root->left) && !(root->right);
}
//create and build minheap
struct minheap* createandbuildminheap(char data[],int freq[],int size){
  struct minheap* curheap=createminheap(size);
  for(int i=0;i<size;i++){
    curheap->array[i]=newnode(data[i],freq[i]);
  }
  curheap->size=size;
  buildminheap(curheap);
  return curheap;
}
//building huffmatree
struct minheapnode* buildhuffmantree(char data[],int freq[],int size){
  struct minheapnode *left,*right,*top;
  struct minheap* curheap=createandbuildminheap(data,freq,size);
  while(!isone(curheap)){
    left=extractmin(curheap);
    right=extractmin(curheap);
    top=newnode('$',left->freq+right->freq);
    top->left=left;
    top->right=right;
    insertminheap(curheap,top);
  }
  return extractmin(curheap);
}
//printing codes
void printcodes(struct minheapnode* root,int arr[],int top){
  if(root->left){
    arr[top]=0;
    printcodes(root->left,arr,top+1);
  }
  if(root->right){
    arr[top]=1;
    printcodes(root->right,arr,top+1);
  }
  if(isleaf(root)){
    printf("%c: ",root->data);
    printarr(arr,top);
  }
}
//huffman codes
void huffmancodes(char data[],int freq[],int size){
  struct minheapnode* root= buildhuffmantree(data,freq,size);
  int arr[100],top=0;
  printcodes(root,arr,top);
}

int visited(char str[],char a,int j){
  int i=0;
  while(str[i]!='\0' && i<j){
    if(a==str[i])
      return 1;
    i++;
  }
  return 0;
}

int frequency(char str[],char a){
  int i=0;int freq=0;
  while(str[i]!='\0'){
    if(a==str[i])
      freq++;
    i++;
  }
  return freq;
}

void bubbleSort(char ch[], int freq[], int n) {
  for (int i = 0; i < n - 1; i++) {
    for (int j = 0; j < n - i - 1; j++) {
      if (freq[j] > freq[j + 1]) {
        // Swap frequencies
        int tempFreq = freq[j];
        freq[j] = freq[j + 1];
        freq[j + 1] = tempFreq;

        // Swap characters
        char tempChar = ch[j];
        ch[j] = ch[j + 1];
        ch[j + 1] = tempChar;
      }
    }
  }
}
int main(){
  char arr[100];
  char ch[100];
  int freq[100]={0};
  printf("Please enter the required string : \n");
  fgets(arr,sizeof(arr),stdin);
  int i=0;int j=0;
  while(arr[i]!='\0'){
    if(!visited(arr,arr[i],i)){
      ch[j]=arr[i];
      freq[j]=frequency(arr,arr[i]);
      j++;
    }
    i++;
  }
  char ch_new[j-1];
  int freq_new[j-1];
  for(i=0;i<j-1;i++){
    ch_new[i]=ch[i];
    freq_new[i]=freq[i];
  }
  bubbleSort(ch_new,freq_new,j-1);
  int size = sizeof(ch_new);
  huffmancodes(ch_new,freq_new,size);
  return 0;
}
