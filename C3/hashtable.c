#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 1

/* OPEN ADDRESSING  PRE PROC */
#define FREE 0
#define USED 1
#define DEL  2

/* CLOSED ADDRESSING STRUCTS */
struct bucket
{
    int info;char * key;
    struct bucket *next;
};
typedef struct bucket bucket;

/* OPEN ADDRESSIG STRUCTS */
struct o_bucket
{
    int status; /* FREE | USED | DEL */
    char key[6]; int info;
};
typedef struct o_bucket o_bucket;

int
hash(str)
    char *str;
{
    unsigned long hash;
    int c;
    hash = 5381;

    while ((c = *str++) != 0)
        hash = ((hash << 5) + hash) + c;

    return (int) hash%SIZE;
}

/* LINEAR PROBING API */
int
where(char*s,o_bucket*t)
{
    int count;
    int tmp;
    int has = hash(s);
    for (count=SIZE;
         count>0
         &&t[has].status == USED
         &&!strcmp(t[has].key,s);
         count--)
        has = (has+1)%SIZE;
    if (strcmp(t[has].key,s))
    {
        if (count == 0)
            has=-1;
        else
        {
            tmp = has;
            while (count > 0
                    && t[has].status !=FREE
                    && strcmp(t[has].key,s))
            {
                count--; has=(has+1)%SIZE;
            }
            if (strcmp(t[has].key,s)) has = tmp;
        }
    }
    return has;
}

void
init_empty_lin(o_bucket*t)
{
    int i;
    for (i=0; i<SIZE;t[i].info=0,t[i++].status=FREE);
    return;
}

double
charge(o_bucket*t)
{
    int i;
    double res = 0.0;
    for (i=0;i<SIZE;i++)
        if (t[i].status == FREE) res++;
    res = SIZE - res;
    return (double) res/SIZE;
}

void
garbage_collection(o_bucket*t)
{
/* creates a new hashtable with no dels and double the  */
  return;
}

void
add_lin(char*s,o_bucket*t)
{
    if (charge(t) >= 0.75) garbage_collection(t);
    int has = where(s,t);
    int flag_err = has == -1?1:0;
    if (!flag_err)
    {
        if (t[has].status == USED)
            t[has].info++;
        else
        {
            if (t[has].status == FREE)
            {
                t[has].status = USED;
                strcpy(t[has].key,s);
                t[has].info = 1;
            }
        }
    }
    return;
}

int
remove_LIN(char*s,o_bucket*t)
{
    int flag_err = 0;
    int has = where(s,t);

    if (has != -1 && !strcmp(t[has].key,s) && t[has].status == USED)
    {
        t[has].info--;
        if (t[has].info == 0)
            t[has].status = DEL;
    }
    else
        flag_err = 1;
    return flag_err;
}

int
lookup(char*s,o_bucket*t)
{
    int has = where(s,t);
    int res = has != -1 && t[has].status == USED && !strcmp(t[has].key,s)?
            t[has].info : 0;
    return res;
}


/* CLOSED ADDRESS API */
void
init_empty(bucket**t)
{
    int i;
    for (i=0; i < SIZE; t[i++] = NULL);

    return;
}

void
add_table(char*s,bucket**t)
{
    int has;
    bucket*item;
    has = hash(s);
    for (item = t[has];
         item != NULL && strcmp(s,item->key);
         item=item->next);
    if (item != NULL)
        item->info++;
    else
    {
        item = (bucket*) malloc(sizeof (bucket));
        item->key = (char *) malloc(20 * sizeof (char));
        item->key = strcpy(item->key,s); item->info=1;
        item->next = t[has];
        t[has] = item;
    }
    return;
}

int
lookup_chain(char*s,bucket**t)
{
    int has, ocur;
    bucket*item;
    has = hash(s);
    ocur = 0;
    for (item = t[has];
         item != NULL && strcmp(s,item->key);
         item=item->next);
    if (item != NULL)
        ocur = item->info;
    return ocur;
}
int
remove_ht(char*s,bucket**t)
{
    int res;
    int has;
    bucket*item;
    has = hash(s);
    if (lookup_chain(s,t))
    {
        for(item=t[has];
            item!=NULL&&strcmp(s,item->key);
            item=item->next);
        if (item->info==1)
        {
            item=NULL; t[has] = NULL;
        }
        else
            item->info--;
        res = 1;
    }
    else
        res = 0;
    return res;
}


int
main(void)
{
    bucket*t[20];
    init_empty(t);
    char s[4] = "Car\0";
    add_table(s,t);
    remove_ht(s,t);
    int i;
    i = lookup_chain(s,t);
    if (i)
        puts("FOUND");
    else
        puts("Not found");
    o_bucket t1[20];
    init_empty_lin(t1);
    add_lin("21",t1);
    remove_LIN("21",t1);
    add_lin(s,t1);
    int x = lookup(s,t1);
    printf("%d\n",x);
    if (x)
        puts("FOUND");
    else
        puts("NOT FOUND");
    return 0;
}
