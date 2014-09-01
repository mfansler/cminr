%{
  #include <cstdio>

  extern "C" int yylex ();
%}

%%

username    { printf ("%s", cuserid (NULL)); }

%%

int
main ()
{
  yylex ();

  return 0;
}
