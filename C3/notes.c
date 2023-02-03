/**
 * File: Data Structures; Trees, Heaps and Hashing tables
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
int
isempty(pqueue *queue)
{ return (queue->size==0);
}

/* Let us consider add and remove both return integers to denote operation
 * success or failure:
 * We have all the tools to define these procedures:
*/
int
add(pqueue *queue, int x)
{ int flag_err = (queue->size >= MAX);
  if (!flag_err)
  { queue->values[queue->size] = x;
    bubbleup(queue->values, queue->size);
    queue->size = queue->size + 1;
  }
  return flag_err;
}
int
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

/* Associative arrays */


int
main()
{ return 0;
}
