#include "memalloc.h"
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>


int main( int argc, char * argv[] )
{
  struct timeval begin;
  struct timeval end;

  gettimeofday(&begin,NULL);
  int success = memalloc_init(1000,FIRST_FIT);
  if (success == -1)
  {
    return success;
  }
  
  char* ptr = memalloc_alloc(1000);
  size_t count = 2000;
  for (size_t i = 0; i < count; i++)
  {
    free(ptr);
    ptr = memalloc_alloc(1000);
  }
  gettimeofday(&end,NULL);
  double duration = ((end.tv_sec * 1000000) + end.tv_usec) - ((begin.tv_sec * 1000000) + begin.tv_usec);
  printf("duration is:%f\n",duration);
  
  return 0;
}
