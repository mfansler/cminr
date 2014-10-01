void 
A ()
{
  // To handle production 
  //   A --> rhs_1 | rhs_2 | ... | rhs_n 
  if (lookahead in FIRST (rhs_1))
    // Use A --> rhs_1 
  else if (lookahead in FIRST (rhs_2))
    // Use A --> rhs_2
  else if (lookahead in FIRST (rhs_3))
    // Use A --> rhs_3

  ...

  else if (lookahead in FIRST (rhs_n)
    // Use A --> rhs_n

  else if (lookahead in FOLLOW (A))
    // Use A --> epsilon if it's a choice
  else
    error ("parse error in A");
}
