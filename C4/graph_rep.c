#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#define NV 6

struct edge
{
int dest; int cost;
struct edge *next;
};
typedef struct edge * ADJL;
typedef ADJL LGRAPH[NV];
typedef int MGRAPH[NV][NV];

void
fromMat(in, out)
    MGRAPH in;
    LGRAPH out;
{
    int i,j;
    ADJL tmp;
    for (i=0; i<NV; i++)
    {
        out[i]=NULL;
        for (j=NV-1;j>=0;j--)
            if (in[i][j] != 0)
            {
                tmp = (ADJL) malloc(sizeof (struct edge));
                tmp->dest = j;
                tmp->cost = in[i][j];
                tmp->next = out[i];
                out[i] = tmp;
            }
    }
    return;
}

void
invert(in,out)
    LGRAPH in;
    LGRAPH out;
{
    int i;
    ADJL tmp;
    ADJL tmp1;
    for (i=0;i<NV;i++)
        out[i] = NULL;
    for (i=0;i<NV;i++)
    {
        tmp1 = in[i];
        while (tmp1 != NULL)
        {
            tmp = (ADJL) malloc(sizeof (struct edge));
            tmp->cost = tmp1->cost;
            tmp->dest = i;
            tmp->next = out[tmp1->dest];
            out[tmp1->dest] = tmp;
            tmp1 = tmp1->next;
        }
    }
    return;
}

int
inDegree(in)
	LGRAPH in;
{
    int i;
	int count;
	int res = 0;
	LGRAPH tmp;
    ADJL tmp1;
    invert(in,tmp);
	for (i=0; i<NV;i++)
	{
		tmp1 = tmp[i];
        count = 0;
		while(tmp1 != NULL)
		{
			count++;tmp1 = tmp1->next;
		}
		res = count > res? count : res;
	}

	return res; 
}

int
colourOK(g,colour)
        LGRAPH g;
        int *colour;
{
        /* Let us consider that no nodes have any edges
         * in which case the array must be ALL the same value
         * this is a specific case
         * possible solution, iterate the array:
         * for each entrance verify that nodes that are connected
         * have different values
         * (this might be optimized by keeping track of already
         * tracked values) however it's an edge case of being a
         * non directed graph
         * Either way this results in O(V*E)
         */
        ADJL tmp;
        int i;
        int flag_err = 0;
        for (i=0; i<NV && flag_err != 1; i++)
        {
                tmp = g[i];
                while (tmp!=NULL && flag_err != 1)
                {
                        if (*(colour + i) == *(colour + tmp->dest))
                                flag_err = 1;
                        tmp = tmp->next;
                }
        }
        return !flag_err;
}

int
main(argc, argv)
    int argc;
    char ** argv;
{

MGRAPH g1
    ={{ 0,  1,  1,  0,  0,  0},
      { 0,  0,  0,  1,  0,  0},
      { 0,  0,  0,  0,  0,  1},
      { 1,  0,  0,  0,  1,  0},
      { 1,  0,  0,  0,  0,  0},
      { 1,  0,  0,  1,  1,  0}
      };
LGRAPH g2;
LGRAPH g3,g4;
fromMat(g1,g2);
invert(g2,g3);
invert(g3,g4);
int arr[6] = {0,1,1,2,3,4};
int x = colourOK(g2, arr);
printf("%d\n",x);
return 0;
}
