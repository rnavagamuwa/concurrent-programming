#include <stdlib.h>
#include <time.h>
#include <stdio.h>

struct node {
  int x;
  struct node *next;
};

int main()
{
        
    //Variables
    int range = 65535;
    int n = 1000;
    int m = 10000;
    int mMember = m * 0.99;
    int mInsert = m * 0.005;
    int mDelete = m * 0.005;

    int value = 0;
    int minValue =0;
    srand(time(NULL));
    struct node *root;       
    struct node *conductor;  
    root = malloc( sizeof(struct node) );  
    root->next = 0;  
    value = rand() % range;
    minValue = value;
    root->x = value;
    conductor = root; 

    
    for (int i = 0; i < n; ++i)
    {
      value = 0;
      if ( conductor != 0 ) {
        while ( conductor->next != 0)
        {
            conductor = conductor->next;
        }

         conductor->next = malloc( sizeof(struct node) );  
         conductor = conductor->next; 

      if ( conductor == 0 )
        {
          printf( "Out of memory" );
          return 0;
        }

        while(value<=minValue){
          value = rand() % range;
        }
        minValue = value;
        conductor->next = 0;         
        conductor->x = value;
        printf("%d\n", conductor->x);
    }
    }



   
    return 0;
}