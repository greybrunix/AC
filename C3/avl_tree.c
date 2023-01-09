#include <stdlib.h>
#include <stdio.h>

#define LEFT  1
#define BLCD  0
#define RGHT -1

struct node
{
  int key, inf;
  int bal;
  struct node*left, *rght;
};
typedef struct node node;

/* rotations */
node*
rotate_right(node*src)
{
  auto node*dst = src->left;
  src->left = dst->rght;
  dst->rght = src;
  return dst;
}
node*
rotate_left(node*src)
{
  auto node*dst = src->rght;
  src->rght = dst->left;
  dst->left = src;
  return dst;
}

node*
fix_right(node*src)
{
  node*b,*c;
  b=src->rght;
  if (b->bal == RGHT)
  {
    src->bal=b->bal=BLCD;
    src=rotate_left(src);
  }
  else
  {
    c=b->left;
    switch (c->bal)
    {
      case LEFT:
        src->bal=BLCD;
        b->bal=RGHT;
        break;
      case RGHT:
        src->bal=LEFT;
        b->bal=BLCD;
        break;
      default:
        src->bal=b->bal=BLCD;
    }
    c->bal=BLCD;
    src->rght=rotate_right(b);
    src=rotate_left(src);
  }
  return src;
}
node*
fix_left(node*src)
{
  node*b,*c;
  b=src->left;
  if (b->bal==LEFT)
  {
    src->bal=b->bal=BLCD;
    src=rotate_right(src);
  }
  else
  {
    c=b->rght;
    switch (c->bal)
    {
      case LEFT:
        src->bal=LEFT;
        b->bal=BLCD;
        break;
      case RGHT:
        src->bal=BLCD;
        b->bal=RGHT; 
        break;
      default:
        src->bal=b->bal=BLCD;
    }
    c->bal=BLCD;
    src->left=rotate_left(b);
    src=rotate_right(src);
  }
  return src;
}

node*
update_tree_rec(node*a,
                int key,
                int val,
                int*g,
                int*u)
{
  if (a==NULL)
  {
    a=(node*) malloc(sizeof (node));
    a->key=key;a->inf=val;a->bal=BLCD;
    a->left=a->rght=NULL;
    *g=1;*u=0;
  }
  else
    if (a->key==key)
    {
      a->inf=val;
      *g=0;*u=1;
    }
  else
    if (a->key > key)
    {
      a->left=update_tree_rec(a->left,key,val,g,u);
      if (*g)
        switch (a->bal)
        {
          case LEFT:
            a=fix_left(a);
            *g=0;
            break;
          case RGHT:
            a->bal=BLCD;
            *g=0;
            break;
          default:
            a->bal=LEFT;
        } 
    }
  else
  {
    a->rght=update_tree_rec(a->rght,key,val,g,u);
    if (*g)
      switch (a->bal)
      {
        case LEFT:
          a->bal=BLCD;
          *g=0;
          break;
        case RGHT:
          a=fix_right(a);
          *g=0;
          break;
        default:
          a->bal=RGHT;
      }
  }
  return a;
}

int
update_tree(node**src,
            int key,
            int val)
{
  int g, u;
  *src = update_tree_rec(*src, key, val, &g, &u);
  return u;
}

int
main(void)
{
  return 0;
}
