Team: Merv Fansler

Notes
=====

First off, I side-stepped some of the problems posed in the assignment: I used
our insight from the RD parser that we could avoid void variables/arrays
altogether by making them syntacticly invalid by adjusting the grammar.

Another issue that I dealt with in a noteworthy manner was FunctionDeclaration
types.  It was recommended that we add INT_FUNCTION and VOID_FUNCTION types.
That bothered me from the standpoint that we have FunctionDeclaration classes
with returnType members which already store all that information. Adding those
enum types just seems redundant to me.  Even though we were told that casting
shouldn't be necessary, I am convinced that using dynamic_cast is the proper
and safe way of testing whether the DeclarationNode pointer reference in a
CallExpressionNode is a FunctionDeclaration pointer.  Because we are dealing
with pointers no exceptions are thrown, rather, failure cases result in mere
nullptr's that can easily be tested for.


