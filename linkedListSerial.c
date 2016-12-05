#include <stdlib.h>
#include <time.h>
#include <stdio.h>

struct node **root;

struct node {
  int value;
  struct node *next;
};

int insert(int value,struct node **head){
    struct node* curr = *head;
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
            *head=temp;
        }
        else{
            prev->next=temp;
        }
        return 1;
    }else{
        return 0; 
    }
  
}

int generateList(int n, struct node **head,int maxNumber){
  int result = 0;
  *head = malloc( sizeof(struct node) ); 
  (*head)->value = rand() % maxNumber+1;

  for (int i = 0; i < n; ++i)
  {
    result = insert(rand() % maxNumber+1,head);
    if (result == 0)
    {
      i--;
    }
  }
}

int member(int value, struct node **head){
  struct node* curr = *head;
  int result = 0;

  while(curr!=NULL){
      if (curr->value == value)
      {
        return 1;
      }
      curr = curr->next;
  }
   return 0;

}

int main()
{
        
    //Variables
    int range = 65535;
    int n = 1000;
    int m = 10000;
    int mMember = m * 0.99;
    int mInsert = m * 0.005;
    int mDelete = m * 0.005;

    srand(time(NULL));
    root = malloc( sizeof(struct node) ); 
    
    generateList(n,root,range);
    printf("%d\n",(*root)->next->value );
    printf("%d\n", member(90,root));
    printf("%d\n", member((*root)->next->value,root));
    
    return 0;
}