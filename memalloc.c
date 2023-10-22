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
Node last_alloc = NULL;

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

  //Linked list allocation
  ll = malloc(sizeof(node));
  ll->size = size;
  ll->Arena_ptr = Arena_ptr;
  ll->type = HOLE;
  ll->next = NULL;
  
  return 0;
}


//Only function that should use free
void memalloc_destroy( )
{
  free(Arena_ptr);
  Node save = NULL;
  while(ll){
    save = ll->next;
    free(ll);
    ll = save;

    
  }
  return;
}

void * memalloc_alloc( size_t size )
{
  // only return NULL on failure
  //return NULL;

  size = ALIGN4(size);

  Node list = ll;

  switch (algor)
  {
  case NEXT_FIT:
    ;
    //Checks if we have reached end of list
    int check = 0;

    //If last alloc is null do not change ll 
    if (last_alloc)
    {
      ll = last_alloc;
    }
    
    while (ll && check != 1)
    {
      

      if(ll->type == HOLE && ll->size >= size){
        ll->type = PROCESS;
        if (ll->size > size)
        {
          Node new_node = malloc(sizeof(node));

          //allocating new node and linked list
          ll->next = new_node;
          new_node->prev = ll;
          new_node->size = ll->size - size;
          ll->size = size;

          //
          new_node->type = HOLE;
          new_node->Arena_ptr = ll->Arena_ptr + size;
          last_alloc = ll;
        }
        void* ans = ll->Arena_ptr;
        ll = list;
        return ans;
      }

      else if (ll->next == NULL)
      {
        check = 1;
        //ll = list;
      }
      
      
      

      ll = ll->next;
    }


    
    return NULL;
    break;


  case BEST_FIT:
    return NULL;
    break;

  case WORST_FIT:
    return NULL;
    break;

  case FIRST_FIT:
    /*while (ll)
    {
      if (ll->size >= size && ll->type == HOLE)
      {
        //Geneeral changes
        ll->type = PROCESS;
        list->prev = ll;
        ll->next = list;
        list->Arena_ptr = Arena_ptr;
        list->type = HOLE;

        list->size = ll->size - size;
        ll->size = size;

    }*/


    while (ll)
    {
      if(ll->type == HOLE && ll->size >= size){
        ll->type = PROCESS;
        if (ll->size > size)
        {
          Node new_node = malloc(sizeof(node));

          //allocating new node and linked list
          ll->next = new_node;
          new_node->prev = ll;
          new_node->size = ll->size - size;
          ll->size = size;

          //
          new_node->type = HOLE;
          new_node->Arena_ptr = ll->Arena_ptr + size;
        }
        void* ans = ll->Arena_ptr;
        ll = list;
        return ans;
      }
      ll = ll->next;
    }
    
    return NULL;
    break;
  default:
    return NULL;
    break;
  }
}

//Shows block of memory is open
void memalloc_free( void * ptr )
{
  while (ll)
  {
    if(ptr == ll->Arena_ptr){
      //ll->type = HOLE;
      break;
    }
    ll = ll->next;
  }
  
  return;
}

int memalloc_size( )
{
  int number_of_nodes = 0;
  Node save = ll;
  while (ll)
  {
    number_of_nodes++;
    ll = ll->next;
  }

  ll = save;
  

  return number_of_nodes;
}

// RmFsbCAyMDIz-76f3-90d6-0703ac120003
