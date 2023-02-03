/**
 * File: Data Structures; Trees, Heaps and Hashing tables
 * THIS CODE IS IN C89 STANDARD*
*/
/* Priority Queues */

/* A priority queue is a buffer in which the first element to be
 * removed is the smallest element stored (for the studied case)
 *   1. Sorted array from largest to smallest, making the removal
 *   efficient.
 *   2. Array sorted by order of storage in the buffer. Making the
 *   insertion efficient.
 * However, these solutions are not optimal, lacking in what the other
 * is better at, preferably we'd want a structure in which both these
 * operations are efficient.
 * Thus, let us consider a heap, in this case, min-heaps:
 *   1. Binary tree in which each element is smaller or equal to its
 *   successors.
 *   2. Left descendant is located in the index 2*i + 1
 *   3. Right descendant is located in the index 2*i + 2
 *   4. The ascendant is located at the level (i-1) / 2
 *   5. The first leaf is located at (N-2)/2
 * We can spare the trouble and start defining these macros in C:
*/
#define LEFT(i) (2*i +1)
#define RIGHT(i) (2*i +2)
#define ASCEN(i) ((i-1) / 2)
#define FLEAF(N) ((N-2) / 2)
#define MAX 1000
struct pqueue
{ int values[MAX];
  int size;
};
typedef struct pqueue pqueue;
/*
 * In order to successfully insert an element to the heap, we will need
 * to assure that the properties of the min-heap are preserved,
 * we can do so by successively swapping the studied element with
 * it's ascendant if the studied element is smaller than the ascendant.
 * We call this procedure bubbleup
*/
void
swap(int*px,int*py)
{ *px=*px^*py;
  *py=*px^*py;
  *px=*px^*py;
}
void
bubbleup(int*vector, int studied_index)
{ int ascen = ASCEN(studied_index);
  while (studied_index>0 && vector[studied_index] < vector[ascen])
  { swap(&vector[studied_index],&vector[ascen]);
    studied_index = ascen;
    ascen = ASCEN(studied_index);
  }
}
/* Note how the worst case (when the inserted element is the smallest element)
 * we have a time complexity in the order of Log2(N)
*/

/* In order to remove an element from the heap, we must swap it with the
 * last element of the array, note that this does not preserve the structure
 * of the heap, what we must do however is push the root down until
 * it's at its correct location.
 * We call this procedure bubbledown:
 */
void
bubbledown(int*vector, int N, int studied_index)
{ int desc = LEFT(studied_index);
  int flag_end = 0;
  while (!flag_end && desc < N )
  { desc = desc + 1 < N && vector[desc + 1] < vector[desc] ?
           desc + 1 : desc;
    if (vector[desc] > vector[studied_index])
    { flag_end = 1;
    }
    else
    { swap(&vector[studied_index],&vector[desc]);
      studied_index = desc;
      desc = LEFT(studied_index);
    }
  }
}

/* Both bubble up and bubble down have a logarithmic time complexity */
/* PriorityQueue manipulation */
void
initPQ(pqueue *queue)
{ queue->size = 0;
}

isempty(pqueue *queue)
{ return (queue->size==0);
}

/* Let us consider add and remove both return integers to denote operation
 * success or failure:
 * We have all the tools to define these procedures:
*/

add(pqueue *queue, int x)
{ int flag_err = (queue->size >= MAX);
  if (!flag_err)
  { queue->values[queue->size] = x;
    bubbleup(queue->values, queue->size);
    queue->size = queue->size + 1;
  }
  return flag_err;
}

remove(pqueue *queue, int *x)
{ int flag_err = isempty(queue);
  if (!flag_err)
  {
    *x = queue->values[0];
    queue->size = queue->size - 1;
    queue->values[0] = queue->values[queue->size];
    bubbledown(queue->values, queue->size, 0);
  }
  return flag_err;
}

/** Ex 12
 * Show the evolution of:
 * v={30,26,22,18,16,13,11,8,6,5,4,3} when passed as argument to heapify
*/

void
heapify(int*vector, int N)
{ int i;
  for (i=1; i<N;i++)
  { bubbleup(vector,i);
  }
}
/*
 * => v={26,30,22,18,16,13,11,8,6,5,4,3}
 * => v={22,30,26,18,16,13,11,8,6,5,4,3}
 * => v={22,18,26,30,16,13,11,8,6,5,4,3}
 * => v={18,22,26,30,16,13,11,8,6,5,4,3}
 * => v={18,16,26,30,22,13,11,8,6,5,4,3}
 * => v={16,18,26,30,22,13,11,8,6,5,4,3}
 * => v={16,18,13,30,22,26,11,8,6,5,4,3}
 * => v={13,18,16,30,22,26,11,8,6,5,4,3}
 * => v={13,18,11,30,22,26,16,8,6,5,4,3}
 * => v={11,18,13,30,22,26,16,8,6,5,4,3}
 * => v={11,18,13,8,22,26,16,30,6,5,4,3}
 * => v={11,8,13,18,22,26,16,30,6,5,4,3}
 * => v={8,11,13,18,22,26,16,30,6,5,4,3}
 * => v={8,11,13,6,22,26,16,30,18,5,4,3}
 * => v={8,6,13,11,22,26,16,30,18,5,4,3}
 * => v={6,8,13,11,22,26,16,30,18,5,4,3}
 * => v={6,8,13,11,5,26,16,30,18,22,4,3}
 * => v={6,5,13,11,8,26,16,30,18,22,4,3}
 * => v={5,6,13,11,8,26,16,30,18,22,4,3}
 * => v={5,6,13,11,4,26,16,30,18,22,8,3}
 * => v={5,4,13,11,6,26,16,30,18,22,8,3}
 * => v={4,5,13,11,6,26,16,30,18,22,8,3}
 * => v={4,5,13,11,6,3,16,30,18,22,8,26}
 * => v={4,5,3,11,6,13,16,30,18,22,8,26}
 * => v={3,5,4,11,6,13,16,30,18,22,8,26}
 */
/* Associative arrays */

/* In this case it shall be a pair of key and info
 * Since this represents a mathematical finite function, no key can be repeated;
 * We will want to add new pairs;
 * change the info associated to each key
 * lookup the information associated with a key
 * remove a key
*/

/** Hash Table */
#include <stdlib.h>

hash(unsigned int x, int size) {
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = (x >> 16) ^ x;
    return (int) (x % size);
}

/*** Closed Addressing ***/

struct bucket
{ int key; int info;
  struct bucket*next;
};
/* Note the hashtable itself will be a pointer to a pointer to a bucket */
void
inittab(struct bucket** h, int size)
{ int i;
  for (i=0; i<size; h[i++]=NULL);
}

lookup(struct bucket**h, int size, int key, int *info)
{ int p = hash(key, size);
  int found = 0;
  struct bucket*item;
  for (item = h[p];
       item!=NULL && item->key!=key;
       item=item->next)
    ;
  if (item!=NULL)
  { *info = item->info;
    found = 1;
  }
  return found;
}

update(struct bucket**h, int size, int key, int info)
{ int p = hash(key,size);
  int new = 1;
  struct bucket*item;
  for (item = h[p];
       item!=NULL && item->key!=key;
       item=item->next)
    ;
  if (item!=NULL)
  { item->info = info;
    new = 0;
  }
  else
  { item = (struct bucket*) malloc (sizeof (struct bucket));
    item->info = info;
    item->key = key;
    item->next = h[p];
    h[p] = item;
  }
  return new;
}


remKey(struct bucket**h, int size, int key)
{ int p = hash(key,size);
  int removed=0;
  struct bucket**item, *tmp;

  for (item = h+p;
       *item!=NULL && (*item)->key!=key;
       item=&((*item)->next))
    ;
  if (*item!=NULL)
  { tmp = *item;
    *item = (*item)->next;
    free(tmp);
    removed = 1;
  }
  return removed;
}

/* Open Addressing */
#define STATUS_FREE 0
#define STATUS_USED 1
struct bucket_O
{ int status;
  int key; int info;
};

void
initOpen(struct bucket_O*h, int size)
{ int i;
  for (i=0; i <size; h[i++].status = STATUS_FREE);
}



main()
{ return 0;
}
