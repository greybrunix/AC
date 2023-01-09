#include <stdio.h>

#define NV 10

struct edge
{
  int dest;
  int cost;
  struct edge *next;
};
typedef struct edge edge;

int
DF(edge**graph,
        int origin,
        int *vstd,
        int *prnt,
        int *dist)
{
  auto int nvis, current,prev, s[NV], top=0;
  auto int flag = 0;
  auto edge* item;
  for (nvis=0; nvis<NV; nvis++)
  {
    vstd[nvis] = 0;
    prnt[nvis] = -1;
    dist[nvis] = -1;
  }
  s[top++] = origin;
  nvis=0;
  while (top)
  {
    current = s[top-1];
    if (!vstd[current])
    {
      vstd[current] = 1;
      prnt[current] = !nvis ? -1 : s[top-2];
      dist[current] = !nvis ?  0 : 1+dist[s[top-2]];
      nvis++;
    }
    item = graph[current];
    if (item == NULL)
      top--;
    else if (vstd[item->dest])
    {
      flag = 0;
      while (item!=NULL && !flag)
      {
        if (!vstd[item->dest])
        {
          s[top++] = item->dest; 
          flag = 1;
        } else item = item->next;
      }
      if (item==NULL)
        top--;
    }
    else s[top++] = item->dest;
  }
  return nvis;
}

int
BF(edge**graph,
   int origin,
   int *vstd,
   int *prnt,
   int *dist)
{
  auto int nvis, current, queue[NV], front, end;
  auto edge*item;
  for (nvis=0; nvis<NV; nvis++)
  {
    vstd[nvis] = 0;
    prnt[nvis] = -1;
    dist[nvis] = -1;
  }
  front = end = 0;
  queue[end++] = origin;
  vstd[origin] = 1;
  prnt[origin]=-1;
  dist[origin]=0;
  nvis=1;
  while (front != end)
  {
    current = queue[front++];
    for (item=graph[current];
         item!=NULL;
         item=item->next)
      if (!vstd[item->dest])
      {
        nvis++;
        vstd[item->dest]=1;
        prnt[item->dest]=current;
        dist[item->dest]=1+dist[current];
        queue[end++]=item->dest;
      }
  }
  return nvis;
}

int
longest(edge**graph,
        int origin,
        int *path)
{
  auto int i;
  auto int res;
  auto int max;
  res = max = 0;
  auto int vstd[NV], prnt[NV], dist[NV];
  BF(graph,origin,vstd,prnt,dist);
  for (i=0;i<NV;i++) if (dist[i] > dist[max]) max = i;
  res = dist[max]; 
  while (max != -1)
  {
    path[dist[max]] = max;
    max = prnt[max];
  }
  return res;
}

int
components(edge**graph,
           int*components)
{
  auto int next = 0;
  auto int i,j;
  auto int vstd[NV], prnt[NV], dist[NV];
  
  for (i=0; i<NV; i++) *(components+i) = 0;
  for (i=0; next < NV; i++)
  {
    BF(graph, next, vstd,prnt,dist);
    for (j=0, next=NV;j<NV;j++)
    {
      if (vstd[j]) *(components+j) = i+1;
      else if (!components[j] && j < next) next = j;
    }
  }
  return i;
}
/*  2005/2006 */
int
is_cyclic(edge**graph,
          int*top)
{
  // indegree 0 (produces edges but received no edges)
  for ()
    
}


int
main(int argc,
     char**argv )
{
  auto int longest_res;
  auto int path[NV];
  auto edge*graph[NV];
  auto edge n00 = {.dest=3,.cost=2,.next=NULL};
  auto edge n0 = {.dest=1, .cost=5 , .next=&n00};
  auto edge n1 = {.dest=4, .cost=8 , .next=NULL};
  auto edge n20 = {.dest=9,.cost=2,.next=NULL};
  auto edge n2 = {.dest=5, .cost=2 , .next=&n20};
  auto edge n3 = {.dest=6, .cost=2 , .next=NULL};
  auto edge n5 = {.dest=8, .cost=8 , .next=NULL};
  auto edge n6 = {.dest=7, .cost=1 , .next=NULL};
  auto edge n7 = {.dest=3, .cost=2 , .next=NULL};
  auto edge n80 = {.dest=9, .cost=4, .next=NULL};
  auto edge n8 = {.dest=4, .cost=3 , .next=&n80};
  graph[0] = &n0;
  graph[1] = &n1;
  graph[2] = &n2;
  graph[3] = &n3;
  graph[4] = NULL;
  graph[5] = &n5;
  graph[6] = &n6;
  graph[7] = &n7;
  graph[8] = &n8;
  graph[9] = NULL;
  longest_res = longest(graph, 0, path);
  printf("%d\n", longest_res);
  return 0;
}
