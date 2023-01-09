#include <stdlib.h>

// first ex
int
fa(int x, int y)
{
    // pre: True
    int m = y;
    if (x > y) m = x;
    
    /* In other words, this function has two values, x and y
     * and the result must be the greatest of the two
     * a.k.a. fa is equivalent to the max functin */
    
    // pos: (m == x || m  == y) && (m >= x && m >= y)
    return m;
}

int
fb(int x, int y)
{
    // pre: x >= 0 && y >= 0
    
    int r, i = 1;

    for (i; i <= x && i <= y; i++)
        if (x % i==0 && y % i==0)
            r = i;

    /* given two positive integers as input
     * this function returns a value r such
     * that both x and y are divisible
     * Thus it returns a common divisor
     */

    // pos: x % r == 0 && y % r == 0
    return r;
}

int
fd(int a[], int N)
{
    // pre: N > 0
    int p = 0, i = 0;
    for (i; i < N-1; i++)
        if (a[i] <= a[i+1]) p = i;
    
    /* Given an array of N integers,
     * fd returns the index of the minimum value of
     * the array */

    // pos: 0 <= p< N && forall_{0 <= i< N} a[p] <= a[i]
    return p;
}

// Second
int
prod(int x, int y)
{
    // pre = True
    r = 0;
    int i = abs(y);
    for (i; i > 0; i--)
        r += (y >= 0)? x: -x;
    // pos : r == x*y && (i = abs(y)) == 0
    return r;
}




int
fc(int x, int y)
{
    // pre: x > 0 && y > 0

    // pos: r % x == 0 && r % y == 0
    return r;
}

int
main()
{
    return 0;
}
