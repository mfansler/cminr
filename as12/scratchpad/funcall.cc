void
square (int* x, int size)
{
  int i;

  for (i = 0; i < size; ++i)
  {
    x[i] = x[i] * x[i];
  }
}

int
main ()
{
  int a[10];
  int i;

  for (i = 0; i < 10; ++i)
  {
    a[i] = i;
  }

  square (a, 10);
}
