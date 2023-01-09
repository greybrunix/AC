#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define LEFT(i) 2*i+1
#define RIGHT(i) 2*i+2
#define PARENT(i) (i-1)/2
#define FLEAF(n) (n/2)
#define MAX 100

struct queue
{
int val[MAX];
int size;
};
typedef struct queue queue;

int
min(int x, int y)
{
  int min;
  min = x > y ? y : x;
  return min;
}


void
swap(int*px,int*py)
{
  *px^=*py;*py^=*px;
  *px^=*py;
  return;
}

void
bubble_up(int i, int*h)
{
  while (i != 0 && h[PARENT(i)] > h[i])
  {
  swap(&h[PARENT(i)],&h[i]);
  i=PARENT(i);
}

return;
} /* The worst case is when i is the index of a leaf
     and is the smallest value (compared to it's parents)
     we have a time complexity of O(length of minheap)
     since minheap is a binary tree; O(log2N)
     */

void
bubble_down(int i, int*h, int n)
{
/* Left and Right need to be studied */
  int left, right, rep, flag_end;
  left = LEFT(i); right = RIGHT(i);
  flag_end = 0;
  while (!flag_end && left < n)
  {
    rep = right < n && h[right] < h[left]? right : left;
    if (right >= n || h[i] <= h[rep]) flag_end = 1;
    if (h[rep] < h[i])
    {
      swap(&(*(h+i)),&(*(h+rep)));
      i = rep;
      left = LEFT(rep);
      right = RIGHT(rep);
    }
  }

  return;
} /* The worst case is when i is the index of the root
     and is the largest value in the the min-heap,
     thus performing O(log2 N) swaps/comparisons
     */

void
empty(queue* q)
{
  q->size = 0;
  return;
} /* O(1) */

int
is_empty(queue* q)
{
  return q->size == 0;
} /* O(1) */

int
add_pq(int x, queue* q)
{
  int flag_err = 0;
  if (q->size >= MAX)
    flag_err = 1;
  else
  {
    q->size++;
    q->val[q->size-1] = x;
    bubble_up(q->size-1, q->val);
  }
  return flag_err;
} /* O(O(BU)) = O(log2N) */

int
rem_pq(queue* q,int*rem)
{
  int flag_err = 0;
  if (q->size == 0)
    flag_err = 1;
  else
  {
    *rem = q->val[0];
    q->val[0] = q->val[--(q->size)];
    bubble_down(0,q->val,q->size);
  }
  return flag_err;
} /* O(O(BD)) = O(log2N) */

/* Bottom up Heapify */
void
heapify_bu(int*v,int n)
{
  int i;
  for (i = FLEAF(n); i >= 0; i--)
    bubble_down(i,v,n);
  return;
} /* O(nlog2n) */
/* Top Down heapify */
void
heapify_td(int*v,int n)
{
  int i;
  for (i=1; i<n;i++)
    bubble_up(i,v);
  return;
} /* O(nlog2n) however > O(bottom-up)
     Why? Because for the same N, same worst case, it does studies more
 nodes, in fact all nodes are studied */


void
sort_heap(int*h, int n)
{
  int i;
  for (i=0; i<n;i++)
  {
    swap(&h[0],&h[n-i]);
    bubble_down(i,h,n-i);
  }
  return;
}

/* Last Problem */

/* Linked list solution O(N)
 * much greater for min-heap in fact O(Nlog2N)
 */

void
flush_arr(int*arr,int n)
{
int i;
for (i=0;i<n;i++)
printf("%d ",arr[i]);
putchar('\n');
return;
}

int
main(int argc,const char**argv)
{
queue* q;
q = (queue*) malloc(sizeof (queue));
empty(q);
add_pq(10,q);
add_pq(15,q);
add_pq(80,q);
add_pq(16,q);
add_pq(22,q);
add_pq(11,q);
add_pq(20,q);
add_pq(21,q);
add_pq(23,q);
add_pq(34,q);
add_pq(37,q);
add_pq(35,q);
add_pq(43,q);
add_pq(22,q);
add_pq(25,q);
add_pq(24,q);
add_pq(28,q);
flush_arr(q->val,q->size);
empty(q);
add_pq(1,q); add_pq(4,q);
add_pq(0,q); add_pq(-5,q);
add_pq(80,q); add_pq(50,q);
flush_arr(q->val,q->size);


printf("\n\n\n Testing heapify \n\n\n");
int v[6] = {1,4,0,-5,80,50};
int u[6] = {1,4,0,-5,80,50};
heapify_td(u,6);
printf("Array td:\t");
flush_arr(u,6);
heapify_bu(v,6);
printf("Array bu:\t");
flush_arr(v,6);
free(q);
return 0;
}
