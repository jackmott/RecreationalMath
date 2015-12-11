#include<stdio.h>
#include<stdlib.h>
#include <gmp.h>
#include<math.h>
#include<string.h>


/* Queue */
typedef struct Queue
{
  int front;
  int rear;
  int size;
  int capacity;
  mpz_t **elements;
}Queue;

Queue * createQ(int);
void enQ(Queue *,mpz_t*);
void advanceQ(Queue *);
void printQ(Queue *);

void sumQ(mpz_t *,Queue *);
int isKeith(Queue *,mpz_t*,mpz_t*);


int main(int argc, char *argv[])
{
  mpz_t start;
  mpz_t end;
  char startString[256];
  char endString[256];
  char digitBuffer[2];
  int numDigits;
 
  if (argc < 2) exit (1);
  numDigits = atoi(argv[1]);

  printf("numDigits:%d\n",numDigits);
  for (int i = 0; i < numDigits; i++)
    {
      printf("Setting string at:%d\n",i);
      startString[i] = '0';
      endString[i] = '9';
    }
  startString[0] = '1';
  startString[numDigits] = '\0';
  endString[numDigits] = '\0';

  printf("startstring:%s\n",startString);
  printf("endString:%s\n",endString);
  
  mpz_init(start);
  mpz_init(end);
 
  mpz_set_str(start,startString,10);   
  mpz_set_str(end,endString,10);

 
 
  Queue *Q = createQ(numDigits);
  
 for (int i = 0; i < numDigits; i++)
   {	 
     mpz_t *digit;
     digit = (mpz_t *)malloc(sizeof(mpz_t));
     mpz_init(*digit);
     enQ(Q,digit);
     // printf("allocating one digit");
   }

 mpz_t sum;
 mpz_init(sum);
 digitBuffer[1] = '\0';

  while (mpz_cmp(start,end) <= 0)
    {
      //      Q->front = 0;
      Q->rear = 0;
      char *s;
    
      for (int i = 0; i < numDigits; i++)
	{
	  s = mpz_get_str(NULL,10,start);	 	  
	  digitBuffer[0] = s[i];	 
	  mpz_set_str(*Q->elements[i],digitBuffer,10);
	  //	  gmp_printf("setting digit:%Zd\n",Q->elements[Q->rear]);	 

	}

    
      // gmp_printf("checking %Zd\n",start);
      int result = isKeith(Q,&start,&sum);
      if (result == 0) {      
      } else {
	gmp_printf("%Zd\n",start);
      }
     
      mpz_add_ui(start,start,1);
    }
  return 0;

}

int isKeith(Queue *Q,mpz_t *n,mpz_t *sum)
{
  //  gmp_printf("num: %Zd\n",n);
 
 
  while (1==1) {
    //   printQ(Q);
    sumQ(sum,Q);    
    int r = mpz_cmp(*sum,*n);
    if (r > 0) return 0;
    if (r == 0) return 1;
    mpz_set(*Q->elements[Q->rear],*sum);
    advanceQ(Q);
    // gmp_printf("sum: %Zd\n",sum);
  } 

   
  return 0;
}

void printQ(Queue *Q)
{
  printf("[");
  for (int i = 0; i < Q->size;i++)
    {
      gmp_printf("%Zd,",Q->elements[i]);
    }
  printf("]\n");
}

void sumQ(mpz_t *s, Queue *Q)
{
  mpz_set_ui(*s,0);
  for (int i = 0;i < Q->size; i++)
    {
      // gmp_printf("loop %d:%Zd",i,*Q->elements[i]);
      mpz_add(*s,*s,*Q->elements[i]);
    }
 
}


Queue * createQ(int max)
{
  Queue *Q;
  Q = (Queue *)malloc(sizeof(Queue));
  Q->elements = (mpz_t **)malloc(sizeof(mpz_t *)*max);
  Q->size = 0;
  Q->capacity = max;
  Q->front = 0;
  Q->rear = -1;
  return Q;
}


 void advanceQ(Queue *Q)
 {
  
   Q->rear = (Q->rear +1) % Q->capacity;
  
    
  return;
 }

void enQ(Queue *Q, mpz_t* element)
{
  if (Q->size == Q->capacity)
    {
      printf("Q is Full");
    }
  else 
    {
      Q->size++;
      Q->rear = Q->rear + 1;
      if (Q->rear == Q->capacity)
	{
	  Q->rear = 0;
	}
      Q->elements[Q->rear] = element;
    }
  return;
}

