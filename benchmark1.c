#include "memalloc.h"
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>

/*Malloc bench mark*/
int main( int argc, char * argv[] )
{


  struct timeval begin;
  struct timeval end;

  gettimeofday(&begin,NULL);
  
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
  
  return 0;
}
