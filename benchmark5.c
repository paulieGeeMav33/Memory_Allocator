#include "memalloc.h"
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>

/*Worst fit bench mark*/

int main( int argc, char * argv[] )
{
  FILE * fp = fopen("benchmark5.csv","w");
  struct timeval begin;
  struct timeval end;
  fprintf(fp,"Test1,Test2,Test3,Test4,\n");
  for(int i = 0; i<500; i++){

  gettimeofday(&begin,NULL);
  
  size_t count = 10000;
  int status = memalloc_init(count,WORST_FIT);
  if (status == -1)
  {
    return status;
  }
  
  char* ptr[count];
  for (size_t i = 0; i < count; i++)
  {
    ptr[i] = memalloc_alloc(1000);
  }

  for (size_t i = 0; i < count; i++)
  {
    memalloc_free(ptr[i]);
  }
  
  memalloc_destroy();
  gettimeofday(&end,NULL);
  double duration = ((end.tv_sec * 1000000) + end.tv_usec) - ((begin.tv_sec * 1000000) + begin.tv_usec);
  printf("duration is:%f\n",duration);
  fprintf(fp,"%f,",duration);

  //Test two allocating all of the heap and freeing all even pointers

  gettimeofday(&begin,NULL);
  status = memalloc_init(count,WORST_FIT);
  if (status == -1)
  {
    return status;
  }
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
  fprintf(fp,"%f,",duration);

  



  for (size_t i = 0; i < count; i++)
  {
    if (ptr[i])
    {
      free(ptr[i]);
    }
  }

  //Test 3 allocating all of the heap freeing half than adding it back in
  gettimeofday(&begin,NULL);

  for (size_t i = 0; i < count; i++)
    {
      ptr[i] = memalloc_alloc(1000);
    }

    //Free half
    for (size_t i = 0; i < count; i++)
    {
      if (i % 2 == 0)
      {
        memalloc_free(ptr[i]);
        ptr[i] = NULL;
      }
    }

    for (size_t i = 0; i < count; i++)
    {
      if (i % 2 == 0)
      {
        ptr[i] = memalloc_alloc(1000);
      }
    }

    gettimeofday(&end,NULL);
    duration = ((end.tv_sec * 1000000) + end.tv_usec) - ((begin.tv_sec * 1000000) + begin.tv_usec);
    printf("duration is:%f\n",duration);
    fprintf(fp,"%f,",duration);

    for (size_t i = 0; i < count; i++)
    {
      if (ptr[i])
      {
        memalloc_free(ptr[i]);
      }
    }

  //Test 4 allocating heap freeing all even blocks and mulitples of three
  //Reallocating all even blocks and multimples of three

  gettimeofday(&begin,NULL);

  for (size_t i = 0; i < count; i++)
  {
    ptr[i] = memalloc_alloc(1000);
  }

  for (size_t i = 0; i < count; i++)
  {
    if (i % 2 == 0 || i % 3 == 0)
    {
      memalloc_free(ptr[i]);
      ptr[i] = NULL;
    }
  }

  for (size_t i = 0; i < count; i++)
  {
    if (i % 2 == 0 || i % 3 == 0)
    {
      ptr[i] = memalloc_alloc(1000);
    }
  }



  gettimeofday(&end,NULL);
  duration = ((end.tv_sec * 1000000) + end.tv_usec) - ((begin.tv_sec * 1000000) + begin.tv_usec);
  printf("duration is:%f\n",duration);
  fprintf(fp,"%f,\n",duration);
  for (size_t i = 0; i < count; i++)
  {
    if (ptr[i])
    {
      memalloc_free(ptr[i]);
    }
  }

  memalloc_destroy();
  }
  

  fclose(fp);

  return 0;
}
