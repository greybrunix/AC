/**
 * File: Complexity Theory
 */

/* Unsorted array search */
int
search(int x,int N,int*v)
{ int i, res;
  i = 0;
  while ((i<N) && (v[i] != x))
  { i++;
  }
  if (i==N)
  { res = -1;
  }
  else
  { res = i;
  }
  return res;
}
/*
 * T(search) = SUM (0;N-1) 1 + 2
 *           = N + 2 => T(search) IN O(N) worst case
 * T(search) = 1 + 2
 *           = 3 => T(search) IN O(1) best case
 * T(search) = N average case
*/
int
main(int argc, char**argv)
{ return 0;
}
