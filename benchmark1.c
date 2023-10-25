#include "memalloc.h"
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>

/*Malloc bench mark*/
int main( int argc, char * argv[] )
{

  //For csv data
  FILE * fp = fopen("benchmark1.csv","w");

  struct timeval begin;
  struct timeval end;
  fprintf(fp,"Test1,\tTest2,\tTest3,\tTest4,\t\n");

  gettimeofday(&begin,NULL);
  
  //Test 1

  //Allocating and freeing a lot of pointers

  /*int status = memalloc_init(count,FIRST_FIT);
  if (status == -1)
  {
    return status;
  }*/

  size_t count = 10000;
  char* ptr[count];
  for (size_t i = 0; i < count; i++)
  {
    ptr[i] = malloc(1000);
  }

  for (size_t i = 0; i < count; i++)
  {
    free(ptr[i]);
  }
  
  gettimeofday(&end,NULL);
  double duration = ((end.tv_sec * 1000000) + end.tv_usec) - ((begin.tv_sec * 1000000) + begin.tv_usec);
  printf("duration is:%f\n",duration);
  fprintf(fp,"%f, ",duration);

  //Test two allocating all of the heap and freeing all even pointers

  gettimeofday(&begin,NULL);
  for (size_t i = 0; i < count; i++)
  {
    ptr[i] = malloc(1000);
  }

  for (size_t i = 0; i < count; i++)
  {
    if (i % 2 == 0)
    {
      free(ptr[i]);
      ptr[i] = NULL;
    }
  }
  gettimeofday(&end,NULL);
  duration = ((end.tv_sec * 1000000) + end.tv_usec) - ((begin.tv_sec * 1000000) + begin.tv_usec);
  printf("duration is:%f\n",duration);

  



  for (size_t i = 0; i < count; i++)
  {
    if (ptr[i])
    {
      free(ptr[i]);
    }
  }

  //Test 3 allocating all of the heap freeing half than adding it back in
  gettimeofday(&begin,NULL);

  //Allocate heap
  for (size_t i = 0; i < count; i++)
  {
    ptr[i] = malloc(1000);
  }

  //Free half
  for (size_t i = 0; i < count; i++)
  {
    if (i % 2 == 0)
    {
      free(ptr[i]);
      ptr[i] = NULL;
    }
  }

  for (size_t i = 0; i < count; i++)
  {
    if (i % 2 == 0)
    {
      ptr[i] = malloc(1000);
    }
  }

  gettimeofday(&end,NULL);
  duration = ((end.tv_sec * 1000000) + end.tv_usec) - ((begin.tv_sec * 1000000) + begin.tv_usec);
  printf("duration is:%f\n",duration);

  for (size_t i = 0; i < count; i++)
  {
    if (ptr[i])
    {
      free(ptr[i]);
    }
  }

  //Test 4 allocating heap freeing all even blocks and mulitples of three
  //Reallocating all even blocks and multimples of three

  gettimeofday(&begin,NULL);
  gettimeofday(&end,NULL);
  

  fclose(fp);
  return 0;
}
