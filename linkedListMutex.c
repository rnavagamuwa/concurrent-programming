#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <math.h>
#include <pthread.h>

struct node **root;
int threadCount =4;
int maxValue = 65535;
int n =1000;
int m =10000 ;
double mMember=0.99;
double mInsert=0.005;
double mDelete=0.005;
pthread_mutex_t lock;
int count = 0;

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



void *operations(void* rank){
    double timespent[m];
    clock_t begin;
    clock_t end;
    double timeSum = 0;
    int keepDoing = 1;
    int memberOperationCounter = 0;
    int insertOperationCounter = 0;
    int deleteOperationCounter = 0;
    int max_mMember = mMember / threadCount;
    int max_mInsert = mInsert / threadCount;
    int max_mDelete = mDelete / threadCount;
    printf("%d\n",max_mMember );
    printf("%d\n",max_mInsert );
    printf("%d\n",max_mDelete );

    while(memberOperationCounter<max_mMember || insertOperationCounter<max_mInsert || deleteOperationCounter<max_mDelete){
          if (memberOperationCounter<max_mMember)
          {
            memberOperationCounter++;
            pthread_mutex_lock(&lock);
            member(rand() % maxValue+1,root);
            pthread_mutex_unlock(&lock);
          }

          if (insertOperationCounter<max_mInsert)
          {
            insertOperationCounter++;
            pthread_mutex_lock(&lock);
            insert(rand() % maxValue+1,root);
            pthread_mutex_unlock(&lock);
          }

          if (deleteOperationCounter<max_mDelete)
          {
            deleteOperationCounter++;
            pthread_mutex_lock(&lock);
            delete(rand() % maxValue+1,root);
            pthread_mutex_unlock(&lock);
          }
    }
    return NULL;
}

int main()
{

    srand(time(NULL));
    root = malloc( sizeof(struct node) ); 
    generateList(n,root,maxValue);
    mMember = m * mMember;
    mInsert = m * mInsert;
    mDelete = m * mDelete;

    printf("===============================================================\n");
    printf("A linked list has been generated with %d elements.\n",n);
    printf("Number of total operations : %d\n", m);
    printf("Number of member operations : %d\n", (int)mMember);
    printf("Number of insert operations : %d\n", (int)mInsert);
    printf("Number of delete operations : %d\n", (int)mDelete);

  long thread;
  pthread_t* thread_handles;
   if (pthread_mutex_init(&lock, NULL) != 0)
    {
        printf("\n mutex init failed\n");
        return 1;
    }

  thread_handles = malloc(threadCount*sizeof(pthread_t));

  for (thread = 0; thread < threadCount; ++thread)
  {
    pthread_create(&thread_handles[thread],NULL,operations,(void*) thread);
  }

  for (thread = 0; thread < threadCount; ++thread)
  {
  pthread_join(thread_handles[thread],NULL);
  }

  free(thread_handles);
  pthread_mutex_destroy(&lock);
   printf("===============================================================\n");
   printf("%d\n",count );
   //  printf("Average time spent : %f seconds\n",timeSum/m );
   //  printf("Standard deviation : %f seconds\n",calculateSD(timespent));

    return 0;
}
