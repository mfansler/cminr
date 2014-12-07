int main (void) {
  int x = -1;
  int y = 0;

  if (x)
    y = 2;
  else
    y = 0;

  if (x < 0)
    y = x * x;
  
  x = 30;

  return 1;
}
