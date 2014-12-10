Team: Merv Fansler

Notes
=====

The compiler is fully functional to the limited extent that I have tested.
Passing arrays proved to be the most difficult aspect for me.  There is
much room for improvement when it comes to how the assembly is generated.
Namely, the sequential write-as-you-go mode of operation is a hinderance
and sometimes entails calculating values that "may" be used in certain
contexts, but not necessarily in the particular context at hand. I felt a
bit rushed and so certain ad hoc design decisions were made that I would not
do if I had more time.  For instance, adding the "isParameter" flag to
DeclarationNode. This arose to deal with the fact that evaluation of a
VariableExpressionNode is strongly determined by the type of the Declaration
it is referencing. I would prefer that such information was already thoroughly
annotated in previous analysis phases and not something that the code generator
should have to pick up.

The fact that portions of the generated assembly code are merely mimicking how
gcc handles things takes away from my sense of accomplishment in this particular
phase of compiler construction.  Burning up 5 or so hours trying to resolve
the array passing thing was pretty frustrating, especially given how precious
finals week hours are.
