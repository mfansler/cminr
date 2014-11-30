Team: Merv Fansler

Notes
=====

Using dynamic_cast is unavoidable in the CallExpressionNode in order to
retrieve the parameter member from a DeclarationNode pointer.

My program deviates from the recommendations.  Specifically, it was recommended
that we add INT_FUNCTION and VOID_FUNCTION enum values. That bothered me from
the standpoint that we have a FunctionDeclaration class with returnType member
that already stores all that information. Adding those enum types just seems
redundant to me. Alternatively, I elected to use dynamic_cast to retrieve the
information. It may be slow, but I argue it makes for a cleaner solution, and
given the simplicity of the C- spec, I think it is effective.

On a side note, I would really like to remove ParameterNode and replace it with
using VariableDeclarationNode and ArrayDeclarationNode.  I didn't do it, but I
think it would have simplified things, particularly when determining array types.
