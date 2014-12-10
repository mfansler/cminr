int a[10];

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
  int i;

  for (i = 0; i < 10; ++i)
  {
    a[i] = i;
  }

  square (a, 10);
}
