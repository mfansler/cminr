Team: Merv Fansler

Notes
=====

Everything is working to spec.

Using dynamic_cast is unavoidable in the CallExpressionNode in order to
retrieve the parameters member from a DeclarationNode pointer.

Global functions must have their evalType info set when they are added to the
symbol table since they will not get visited by the SemanticAnalysisVisitor.
That could be changed by having the visitor also visit the declaration
references found on all the reference nodes.  However, that would either lead
to nodes being visited multiple times, or adding a "visited" flag to prevent
that type of redundancy.
