#include "memalloc.h"
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>

/*Best fit bench mark*/
int main( int argc, char * argv[] )
{
  struct timeval begin;
  struct timeval end;

  gettimeofday(&begin,NULL);
  
  size_t count = 10000;
  int status = memalloc_init(count,BEST_FIT);
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
  return 0;
}
