#include "memalloc.h"
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>

int main( int argc, char * argv[] )
{


  struct timeval begin;
  struct timeval end;

  gettimeofday(&begin,NULL);
  char* ptr = malloc(1000);
  size_t count = 2000;
  for (size_t i = 0; i < count; i++)
  {
    free(ptr);
    ptr = malloc(1000);
  }
  gettimeofday(&end,NULL);
  double duration = ((end.tv_sec * 1000000) + end.tv_usec) - ((begin.tv_sec * 1000000) + begin.tv_usec);
  printf("duration is:%f\n",duration);
  
  return 0;
}
