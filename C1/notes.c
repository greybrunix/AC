

/* Haskell notation
fact 0 = 1
fact (n+1) = (n+1) * (fact n)
*/
int
factorial(int n)
{
  int f = 1;
  while (n>0)
  { f = f*n;
    n = n-1;
  }
  return f;
}
/*
 * BNF grammar for an average C program
<program> ::= ID EQ <exp>
            | <program> ; <program>
            | if <cond> <program>
            | if <cond> <program>
            | while <cond> { <program> }
*/

/* Specifying a program */
/* Pre condition := What conditions must the program abide by
 * in order to funcion?
 * Post Condition := When terminating what conditions are verified
*/

void
swap(int*x,int*y)
{
    *x = *x ^ *y;
    *y = *x ^ *y;
    *x = *x ^ *y;
    /* SSA form
    int x0,x1,y0;
    int*x2; int*y1;
    x0 = *x; y0 = *y;
    x2 = x; y1 = y;

    x1=x0^y0;
    *y1=x1^y0;
    *x2=x1^*y1;
    */
}

/* It holds that the swap program executes for any input
 * -> Pre condition :: True;
 * When the program terminates we know that the contents of x
 * (that is the contents of what x is pointing to) will
 * contain the contents of what y is pointing to
 * -> Post condition :: *x = *y AND *y = *x;
*/

/* Note however that this specification is faulty;
 * it is saying that the contents of x and y are the same!
 *
 * Indeed let us consider instead a more ``complete'' adaptation
 * One where we specify we know the content of what x is pointing
 * to and the same for y, thus
 * -> Pre condition :: *x = x0 AND *y = y0;
 * Note how, now we can conclude a post condition that does
 * not imply equality of *x and *y;
 * -> Post condition :: *x = y0 AND *y = x0;
 *  What about the changed variables? What do we know about them?
 * -> Post condition :: (*x = y0 AND *y = x0)
 *                      AND
 *                      (x1 = x0^y0) AND (*y1= x1^y0) AND (*x2=x1^*y1)
 * Here we detail EXACTLY what happens to x and y in each state of the program
 *
 * In other words, this specification takes into consideration the
 * necessary side effects needed to perform the swap program.
*/

int
search(int*v, int a,
       int b, int x)
{ int f = -1, i = a;
  while (i <= b && f != -1)
  { if (v[i] == x)
      f = i;
    i++;
  }
  return f;
}

/* Note how this program only executes when all elements between
 * a and b are sorted; thus we can specify the pre condition as that;
 * -> Pre condition :: (ALL (a<=i<=b), v[i] = v(i))
 *                     AND (ALL (a<=i<=b), v(i) <=v(i+1))
 * We also know that, when execution ends, f will either be -1 or 1
 * and that the elements of the array are not altered
 * let's write that:
 * -> Post condition :: (ALL (a<=i<=b),v[i] = v(i))
 *                      AND
 *                      ((EXI (a<=i<=b),vi=x) => (f = p AND v[p] = x AND i = f)
 *                        OR
 *                      !(EXI (a<=i<=b),vi=x) => (f = -1)
*/

/* Let us consider the same problem, however, with a different
 * post condition:
 * -> (ALL (a<=i<=b), v[i] = v(i))
 *    AND
 *    (EXI (a<=i<=b),vi=x) => v[p] = x
 * What do we know about the program?
 *
 * Unlike the previous example where we know the program terminates when
 * x is found and we obtain the explicit index of the found value, even when it
 * doesn't exist, in which case being -1, in this example, the program
 * continues execution until i <= b, of which we are only certain that
 * if x is in v then v[p] = x
*/

/* EX1
 * 1.1)
 *    Pre-condition:: x = x0 >= 0 AND e = e0 > 0
 *    Post-condition:: | r*r - x0| < w0

 * Interpreting Directly:
 * We know this program runs when the value in x is greater or equal to zero
 * and the value in e is greater than 0.
 * We also know that when the program terminates, r will be such that
 * the absolute value of the subtraction between its square and x0 is
 * inferior to e0.
 * NOTE: We also know that x and e may suffer alterations but we are only
 * taking interest in the initial values.
 *
 *
 * 1.2)
 *    Pre-condition:: ALL (0<=i<N) A[i] = ai
 *    Post-condition:: ALL (0<=i<N) (A[i] = ai AND A[p] <=ai)
 *
 * Interpreting Directly:
 * The pre-condition and the first clause of the post condition allow us to
 * assert that this program will NOT change the contents of the array.
 * However, we also know that when the program terminates, all elements of the array
 * are Greater or equal to the content indexed in p.
 * As such these conditions specify a program that finds the minimum element of an
 * array.
*/

/* EX 2
 * 2.2)
 *    Specify a program that given two arrays A and B, checks if they have
 *    any element in common.
 * Note how we may halt execution as soon as we find one such element:
 * Pre-Condition: (ALL (0<=i<=Na) A[i] = ai) AND (ALL (0<=j<=Nb) B[j] = bj)
 * Post-Condition: ((ALL (0<=i<=Na) A[i] = ai) AND (ALL (0<=j<=Nb) B[j] = bj))
 *                 AND
 *                 ((EXI (0<=i<=Na) (EXI (0<=j<=Nb) ai = bj)) => A[p] = B[f])
*/
int
main()
{ return 0;
}
