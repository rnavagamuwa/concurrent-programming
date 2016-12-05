#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <math.h>

struct node **root;

struct node {
  int value;
  struct node *next;
};

int insert(int value,struct node **root){
    struct node* curr = *root;
    struct node* prev = NULL;
    struct node* temp;

    while(curr!=NULL && curr-> value < value){
        prev=curr;
        curr=curr->next;
    }

    if(curr==NULL || curr->value > value){
        temp = malloc(sizeof(struct node));
        temp->value = value;
        temp->next = curr;

        if(prev==NULL){
            *root=temp;
        }
        else{
            prev->next=temp;
        }
        return 1;
    }else{
        return 0; 
    }
  
}

int generateList(int n, struct node **root,int maxNumber){
  int result = 0;
  *root = malloc( sizeof(struct node) ); 
  (*root)->value = rand() % maxNumber+1;

  for (int i = 0; i < n; ++i)
  {
    result = insert(rand() % maxNumber+1,root);
    if (result == 0)
    {
      i--;
    }
  }
}

int member(int value, struct node **root){
  struct node* curr = *root;

  while(curr!=NULL){
      if (curr->value == value)
      {
        return 1;
      }
      curr = curr->next;
  }
   return 0; //item not found

}

int delete(int value, struct node **root){
  struct node* curr = *root;
  struct node* prev = NULL;

  while(curr!=NULL){
    if (curr->value == value)
    {
      if (prev!=NULL && curr->next!=NULL )
      {
        prev->next = curr->next;
      }else if(curr->next!=NULL){
        *root = curr->next;
      }else{
        *root = NULL;
      }
      return 1;
    }
    prev = curr;
    curr = curr->next;
  }
  return 0;
}

double calculateSD(double data[])
{
    double sum = 0.0, mean, standardDeviation = 0.0;

    int i;

    for(i=0; i<10; ++i)
    {
        sum += data[i];
    }

    mean = sum/10;

    for(i=0; i<10; ++i)
        standardDeviation += pow(data[i] - mean, 2);

    return sqrt(standardDeviation/10);
}



int main()
{
        


    //Variables
    int maxValue = 65535;
    // int n;
    // int m ;
    // double mMember;
    // double mInsert;
    // double mDelete;


    // printf("Enter number of samples: ");
    // printf("Enter n: ");
    // scanf("%d",&n);
    // printf("Enter m: ");
    // scanf("%d",&m);
    // printf("Enter member_fraction: ");
    // scanf("%lf",&mMember);
    // printf("Enter insert_fraction: ");
    // scanf("%lf",&mInsert);
    // printf("Enter delete_fraction: ");
    // scanf("%lf",&mDelete);
    int n =1000;
    int m =10000 ;
    double mMember=0.99;
    double mInsert=0.005;
    double mDelete=0.005;

    mMember = m * mMember;
    mInsert = m * mInsert;
    mDelete = m * mDelete;

    srand(time(NULL));
    root = malloc( sizeof(struct node) ); 
    generateList(n,root,maxValue);

    printf("===============================================================\n");
    printf("A linked list has been generated with %d elements.\n",n);
    printf("Number of total operations : %d\n", m);
    printf("Number of member operations : %d\n", (int)mMember);
    printf("Number of insert operations : %d\n", (int)mInsert);
    printf("Number of delete operations : %d\n", (int)mDelete);

    double timespent[m];
    clock_t begin;
    clock_t end;
    double timeSum = 0;

    for (int i = 0; i < (int)mMember; ++i)
    {
      begin = clock();
      member(rand() % maxValue+1,root);
      end = clock();
      timespent[i] = (double)(end - begin) / CLOCKS_PER_SEC;
      timeSum += timespent[i];
    }

    for (int i = 0; i < (int)mInsert; ++i)
    {
      begin = clock();
      insert(rand() % maxValue+1,root);
      end = clock();
      timespent[i+(int)mMember] = (double)(end - begin) / CLOCKS_PER_SEC;
      timeSum += timespent[i+(int)mMember];
    }

    for (int i = 0; i < (int)mDelete; ++i)
    {
      begin = clock();
      delete(rand() % maxValue+1,root);
      end = clock();
      timespent[i+(int)mMember+(int)mInsert] = (double)(end - begin) / CLOCKS_PER_SEC;
      timeSum += timespent[i+(int)mMember+(int)mInsert];
    }
    printf("===============================================================\n");
    printf("Average time spent : %f seconds\n",timeSum/m );
    printf("Standard deviation : %f seconds\n",calculateSD(timespent));


    return 0;
}
