// The MIT License (MIT)
// 
// Copyright (c) 2021, 2022, 2023 Trevor Bakker 
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software. (RmFsbCAyMDIz)
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES UTA OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#include "memalloc.h"
#include <stdlib.h>
// 2 Global variables Arena, Algo

enum ALGORITHM algor;
void * Arena_ptr;

Node ll = NULL;

/*Make a linked list node to help with allocations*/




//Only function that should use malloc
//May have to use malloc multipile times if using linked list
int memalloc_init( size_t size, enum ALGORITHM algorithm )
{
  
  if (size<1)
  {
    /* Invalid memory size */
    return -1;
  }
  size = ALIGN4(size);
  algor = algorithm;
  Arena_ptr = malloc(size);
  
  return 0;
}
//Only function that should use free
void memalloc_destroy( )
{
  return;
}

void * memalloc_alloc( size_t size )
{
  // only return NULL on failure
  return NULL;

  size = ALIGN4(size);

  switch (algor)
  {
  case NEXT_FIT/* constant-expression */:
    /* code */
    node * list = ll;
    while (ll)
    {
      if(ll->type == HOLE && ll->size >= size){
        ll->type = P;
      }
    }
    
    break;


  case BEST_FIT:
    break;

  case WORST_FIT:
    break;

  case FIRST_FIT:
    break;
  default:
    return NULL;
    break;
  }
}

//Shows block of memory is open
void memalloc_free( void * ptr )
{
  free(Arena_ptr);
  return;
}

int memalloc_size( )
{
  int number_of_nodes = 0;

  return number_of_nodes;
}

// RmFsbCAyMDIz-76f3-90d6-0703ac120003
