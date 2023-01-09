
#define LEFT 1
#define BAL  0
#define RIGHT -1

struct node
{
  int key, info, inclinacao;
  struct node*left, *right;
};

typedef struct node node;

node*
rotate_left(node*a)
{
  node*c = a->right;
  node*d = c->left;
  a->right = d;
  c->left = a;
  return c;
}

node*
rotate_right(node*a)
{
  node*b = a->left;
  node*d = b->right;
  a->left = d;
  b->right = a;
  return b;
}

node*
fix_right(node*a)
{
  node*c;
  node*b=a->right; 
  if (b->inclinacao == RIGHT)
  {
    a->inclinacao=b->inclinacao=BAL;
    rotate_left(a);
  }
  else
  {
    c=b->left;
    switch (c->inclinacao)
    {
      case LEFT:
        a->inclinacao = RIGHT;
        b->inclinacao = BAL;
        break;
      case RIGHT:
        a->inclinacao = BAL;
        b->inclinacao = LEFT;
        break;
      default: // case BAL
        a->inclinacao=b->inclinacao=BAL;
    }
    c->inclinacao = BAL;
    a->right = rotate_right(b);
    a = rotate_left(a);
  }
  return a;
}
// b->inclinacao == RIGHT rotate_left(a)
// c->inclinacao == LEFT C-> BAL A -> RIGHT e B -> BAL
// c->inclinacao == RIGHT C-> BAL A->BAL e B -> LEFT

