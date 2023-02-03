/**
 * File: Specification, verification and Hoare Logic
 */

/* Haskell notation
fact 0 = 1
fact (n+1) = (n+1) * (fact n)
*/
int
factorial(int n)
{ int f = 1;
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
{  *x = *x ^ *y;
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

/*
 * Hoare triple for While cycles
 *
 * P => I  {I AND c} S {I}  (I AND NOT c)=>Q
 *         {P} while c S {Q}

 * 1. P=>I, Before executing the cycle, I is true
 * 2. {I AND c} S {I}, Assuming the invariant to be valid before the iteration,
 *     it must remain valid
 * 3. (I AND NOT c)=>Q, Q is true when c is false
*/

/*
 * Let us consider the factorial function once more;
  f = 1;
  while (n>0)
  { f = f*n;
    n = n-1;
  }
  * a posteriori we can specify this program with:
  * Pre:: n = n0 AND n0 >= 0
  * Pos:: (n0 != 0 AND n1 = (n0-1) AND f1 = factorial(n1)*n0 AND f = f1)
  *       OR (n0 = 0 AND f = f0);
  * However, how can we assert that such a program is correct?
  * As seen before, the invariant is the tool for specifying a program with a
  * while cycle that can be proven to terminate.
  * Inv:: ALL (0<i<=n) (f(i) = f(i-1)*n(i-1) AND n(i) = n(i-1) - 1)
*/

/*
 * Pre: x = x0 AND y = y0 >= 0
 * Pos: m = x0 * y0
{ int m = 0, d = y;
  while (d > 0)
  { m=m+x;
    d=d-1;
  }
}
 * Inv: (x=x0 AND y=y0) AND d >= 0 AND x0 * d + m = x0 * y0
 *
 * 1.(Pre) => Inv[m\0,d\y]
 * 2.(Inv AND d > 0) => (Inv[m\m+x,d\d-1])
 * 3.(Inv AND NOT(d>0)) => (m = x0 * y0)
 *
 * 1. Is Inv[m\0,d\y] true? considering y0 >= 0 and x = x0?
 *    Yes! Let us analyse;
 *    (x = x0 AND y = y0) AND y >= 0 AND x0 * y + 0 = x0 * y0
 * ===(x = x0 AND y = y0) AND y0 >= 0 AND x0 * y0 = x0 * y0
 * 2. Is Inv[m\m+x,d\d-1]) True? knowing that d > 0?
 *    Yes! Let us analyse;
 *    (x = x0 AND y = y0) AND d >= 0 AND x0 * d + m = x0 * y0 AND d > 0
 *  =>(x = x0 AND y = y0) AND d > 0 AND x0 * d + m = x0 * y0
 *  =>(x = x0 AND y = y0) AND d >= 1 AND x0 * (d-1) + m + ? = x0 * y0
 *  =>(x = x0 AND y = y0) AND d-1>=0 AND x0 * (d-1) + (m+x0) = x0*y0
 * 3. Is (m = x0 * y0)? True when d = 0?
 *    (x = x0 AND y = y0) AND d >= 0 AND x0*d+m=x0+y0 AND d <= 0
 *  =>(x = x0 AND y = y0) AND d = 0 AND x0* d+m=x0+y0
 *  =>(x = x0 AND y = y0) AND d = 0 AND m = x0 + y0
*/

/* Total Correction
 *
 * Variant
 *    [P] S [Q]
 * 1. P is valid then S terminates
 * 2. From all states where P is valid, then S terminates, reaching states
 * where Q is valid.
 *
 * How can we assert the termination of a cycle however?
*/

/* VARIANT
 * The variant is an integer expression that
 * 1. decreases in each iteration
 * 2. is always greater than a pre-defined value (typically 0)
*/

/* Exercise
 *
 * Pre:: ALL (0<=i<N) A[i] = a(i)
 * Pos:: s = SUM (i=0;N-1) a(i)
 *
 * 1.
s = 0; p = 0;
while (p<N)
{ s = s + A[p];
  p = p + 1;
}
 * Invariant
 * Pre => Inv[s\0,p\0]
 * (Inv AND (p<N)) => V >= 0
 * (Inv AND (p<N) AND V = v0) => (Inv AND Var < v(0))[s\s+A[p],p\p+1]
 * (Inv AND (p>=N)) => Pos
 *
 *  Inv = ALL (0<=i<N) A[i] = a(i) AND s = SUM (0;p-1) a(p-1)
 *  Var: N-p (>0)
 *
 *   ALL (0<=i<N) A[i] = a(i) => (0 = SUM(0;-1) a(-1) AND Pre)
 * =>ALL (0<=i<N) A[i] = a(i) => (0 = 0 AND Pre)
 * =>True
 *
 *   (s = SUM (0;p) a(p) AND Pre AND (p<N)) => N-p > 0
 * =>   (p0 and Pre AND 0<N-p) => N-p > 0
 * => TRUE
 *   s = SUM (0;p) a(p) AND Pre AND (p<N) AND Var = v(0)
 * => Pre AND s+A[p] = SUM (0;p+1) a(p+1) AND (N-(p+1)) < N-p
 * => TRUE AND SUM (0;p) a(p)+A[p] = SUM (0;p+1) a(p+1) AND
                                              (N-(p+1)) < N-p
 * => TRUE AND SUM (0;p+1) a(p+1) = SUM (0;p+1) a(p+1)
                                           AND (N-(p+1)) < N-p
 * => TRUE AND TRUE AND (N-(p+1)) < N-p
 * => TRUE AND TRUE AND (N-p-1) < N-1
 * => TRUE AND TRUE AND TRUE
 * => TRUE
 *  (Inv AND (p>=N)) => Pos
 * =>Pre AND s = SUM (0;p) a(p) AND p>=N AND N = p
 *  Note how if p is greater or equal than N it will be greater than N-1
 * =>Pre AND s = SUM (0;p) a(p) AND p > N-1 AND N = p
 *   => s = SUM (0,N-1) a(i)
 * =>TRUE
 *
*/

int
main()
{ return 0;
}
