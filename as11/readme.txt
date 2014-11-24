Team: Merv Fansler

Everything in the SymbolTreeVisitor works as specified as far as the tests I
performed indicate. I did run into some errors with unique_ptr that took a while
to actually figure out the issue. Specifically, when creating a new scope I was
receiving a "method not found" when attempting to push the scope table wrapped
in the unique_ptr onto the vector. The error was simple to resolve (have to
"move" the unique_ptr, i.e., can't copy it), but the message produced by the
compiler was dozens of lines of noise.

Switching to the member initialization syntax took a little bit, particularly
because I decided to roll the (line,column) info into the ultimate base class
and require every subclass have to pass the info up to its respective parent
class.  Not too difficult, but time consuming.

I thought storing a private flag for distinguishing function bodies from
compound statements would be a quick and simple solution for keeping function
parameters and local declarations in the same scope. While testing I found that
I inadvertently created a bug that prevented subsequent compound statements from
creating new scopes. It works now, but feels a bit more awkward than I'd prefer.
My test for this was:

    int main (int x) { int x; x = 50 * x; return x; } // multiple declaration

    int main (int x) { { int x; x = 50 * x; } return x; } // acceptable


The PrintVisitor is mostly working. One thing that is not working is type info
on "input" and "output" function calls. In the SymbolTableVisitor, I add those
functions to the scope table, but not explicitly to the AST structure, hence,
when it comes time for the declarations to be resolved in the PrintVisitor
they are no longer available.  Not sure the best approach for resolving this.
In our case, it might be simplest to just insert DeclarationNodes for those
global functions directly into the ProgramNode declarations vector.  However,
if the project grew that would be extremely wasteful. In C/C++ this is what
header and extern declarations are for. Obviously, I'll be resolving this in
the type checking assignment.
