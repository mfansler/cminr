################################################################################
                                          # C- Compiled to IA-32 Assembly Instructions
                                          # Compiler v. 0.1.0
################################################################################
                                          # Global Variables
                                          # 
          .globl    x                     # 
          .data                           # 
          .align    4                     # 
          .type     x, @object            # 
          .size     x, 40                 # 
x:                                        # 
          .zero     40                    # initialize to zero
################################################################################
################################################################################
.globl minloc
          .type     minloc, @function     # "minloc" is type function
minloc:                                   # 
          enter     $0, $0                # save stack & frame ptrs
                                          # {-> Begin compound statement
          subl      $4, %esp              # allocate local variable i
          subl      $4, %esp              # allocate local variable x
          subl      $4, %esp              # allocate local variable k
                                          # Assignment: begin evaluating rhs
                                          # Loading variable "low"
          movl      12(%ebp), %eax        # load function parameter value
          pushl     %eax                  # save evaluated value
                                          # Loading variable "k"
          movl      -12(%ebp), %eax       # load local variable value
          popl      -12(%ebp)             # assign rhs value to variable
          movl      -12(%ebp), %eax       # place evaluated value in result
                                          # Assignment: begin evaluating rhs
                                          # Loading subscripted array "a[_]"
                                          # Loading variable "low"
          movl      12(%ebp), %eax        # load function parameter value
          movl      %eax, %ebx            # store index value in EBX
          movl      %ebp, %eax            # 
          addl      $8, %eax              # 
          movl      (%eax), %eax          # 
          leal      (%eax,%ebx,4), %ebx   # compute address
          movl      (%ebx), %eax          # load value into EAX
          pushl     %eax                  # save evaluated value
                                          # Loading variable "x"
          movl      -8(%ebp), %eax        # load local variable value
          popl      -8(%ebp)              # assign rhs value to variable
          movl      -8(%ebp), %eax        # place evaluated value in result
                                          # Assignment: begin evaluating rhs
                                          # Additive expression: begin evaluating rhs
          movl      $1, %eax              # integer literal
          pushl     %eax                  # save rhs value while computing lhs
                                          # Loading variable "low"
          movl      12(%ebp), %eax        # load function parameter value
          popl      %ebx                  # restore rhs operand
          addl      %ebx, %eax            # evaluate additive expression
          pushl     %eax                  # save evaluated value
                                          # Loading variable "i"
          movl      -4(%ebp), %eax        # load local variable value
          popl      -4(%ebp)              # assign rhs value to variable
          movl      -4(%ebp), %eax        # place evaluated value in result
.L0:                                      # 
                                          # relational expression: begin evaluating lhs
                                          # Loading variable "i"
          movl      -4(%ebp), %eax        # load local variable value
          pushl     %eax                  # save lhs while computing rhs
                                          # Loading variable "high"
          movl      16(%ebp), %eax        # load function parameter value
          popl      %ebx                  # restore lhs operand
          cmpl      %eax, %ebx            # comparision
          setl      %al                   # relation
          movzbl    %al,%eax              # place evaluated value in result
          cmpl      $0, %eax              # WHILE comparison
          je        .L1                   # 
                                          # {-> begin WHILE body
                                          # {-> Begin compound statement
                                          # relational expression: begin evaluating lhs
                                          # Loading subscripted array "a[_]"
                                          # Loading variable "i"
          movl      -4(%ebp), %eax        # load local variable value
          movl      %eax, %ebx            # store index value in EBX
          movl      %ebp, %eax            # 
          addl      $8, %eax              # 
          movl      (%eax), %eax          # 
          leal      (%eax,%ebx,4), %ebx   # compute address
          movl      (%ebx), %eax          # load value into EAX
          pushl     %eax                  # save lhs while computing rhs
                                          # Loading variable "x"
          movl      -8(%ebp), %eax        # load local variable value
          popl      %ebx                  # restore lhs operand
          cmpl      %eax, %ebx            # comparision
          setl      %al                   # relation
          movzbl    %al,%eax              # place evaluated value in result
          cmpl      $0, %eax              # IF comparison
          je        .L2                   # 
                                          # {-> begin THEN
                                          # {-> Begin compound statement
                                          # Assignment: begin evaluating rhs
                                          # Loading subscripted array "a[_]"
                                          # Loading variable "i"
          movl      -4(%ebp), %eax        # load local variable value
          movl      %eax, %ebx            # store index value in EBX
          movl      %ebp, %eax            # 
          addl      $8, %eax              # 
          movl      (%eax), %eax          # 
          leal      (%eax,%ebx,4), %ebx   # compute address
          movl      (%ebx), %eax          # load value into EAX
          pushl     %eax                  # save evaluated value
                                          # Loading variable "x"
          movl      -8(%ebp), %eax        # load local variable value
          popl      -8(%ebp)              # assign rhs value to variable
          movl      -8(%ebp), %eax        # place evaluated value in result
                                          # Assignment: begin evaluating rhs
                                          # Loading variable "i"
          movl      -4(%ebp), %eax        # load local variable value
          pushl     %eax                  # save evaluated value
                                          # Loading variable "k"
          movl      -12(%ebp), %eax       # load local variable value
          popl      -12(%ebp)             # assign rhs value to variable
          movl      -12(%ebp), %eax       # place evaluated value in result
          addl      $0, %esp              # deallocate local variables
                                          # }<- End compound statement
.L2:                                      # }<- end THEN
                                          # Assignment: begin evaluating rhs
                                          # Additive expression: begin evaluating rhs
          movl      $1, %eax              # integer literal
          pushl     %eax                  # save rhs value while computing lhs
                                          # Loading variable "i"
          movl      -4(%ebp), %eax        # load local variable value
          popl      %ebx                  # restore rhs operand
          addl      %ebx, %eax            # evaluate additive expression
          pushl     %eax                  # save evaluated value
                                          # Loading variable "i"
          movl      -4(%ebp), %eax        # load local variable value
          popl      -4(%ebp)              # assign rhs value to variable
          movl      -4(%ebp), %eax        # place evaluated value in result
          addl      $0, %esp              # deallocate local variables
                                          # }<- End compound statement
          jmp       .L0                   # }<- end WHILE body
.L1:                                      # exit WHILE
                                          # Loading variable "k"
          movl      -12(%ebp), %eax       # load local variable value
          addl      $12, %esp             # deallocate local variables
                                          # }<- End compound statement
          leave                           # 
          ret                             # 
################################################################################
.globl sort
          .type     sort, @function       # "sort" is type function
sort:                                     # 
          enter     $0, $0                # save stack & frame ptrs
                                          # {-> Begin compound statement
          subl      $4, %esp              # allocate local variable i
          subl      $4, %esp              # allocate local variable k
                                          # Assignment: begin evaluating rhs
                                          # Loading variable "low"
          movl      12(%ebp), %eax        # load function parameter value
          pushl     %eax                  # save evaluated value
                                          # Loading variable "i"
          movl      -4(%ebp), %eax        # load local variable value
          popl      -4(%ebp)              # assign rhs value to variable
          movl      -4(%ebp), %eax        # place evaluated value in result
.L3:                                      # 
                                          # relational expression: begin evaluating lhs
                                          # Loading variable "i"
          movl      -4(%ebp), %eax        # load local variable value
          pushl     %eax                  # save lhs while computing rhs
                                          # Additive expression: begin evaluating rhs
          movl      $1, %eax              # integer literal
          pushl     %eax                  # save rhs value while computing lhs
                                          # Loading variable "high"
          movl      16(%ebp), %eax        # load function parameter value
          popl      %ebx                  # restore rhs operand
          subl      %ebx, %eax            # evaluate additive expression
          popl      %ebx                  # restore lhs operand
          cmpl      %eax, %ebx            # comparision
          setl      %al                   # relation
          movzbl    %al,%eax              # place evaluated value in result
          cmpl      $0, %eax              # WHILE comparison
          je        .L4                   # 
                                          # {-> begin WHILE body
                                          # {-> Begin compound statement
          subl      $4, %esp              # allocate local variable t
                                          # Assignment: begin evaluating rhs
                                          # Loading variable "high"
          movl      16(%ebp), %eax        # load function parameter value
          pushl     %eax                  # push function argument onto stack
                                          # Loading variable "i"
          movl      -4(%ebp), %eax        # load local variable value
          pushl     %eax                  # push function argument onto stack
                                          # Loading variable "a"
          movl      8(%ebp), %eax         # load function parameter value
          pushl     %eax                  # push function argument onto stack
          call      minloc                # invoke function
          addl      $12, %esp             # remove arguments from stack
          pushl     %eax                  # save evaluated value
                                          # Loading variable "k"
          movl      -8(%ebp), %eax        # load local variable value
          popl      -8(%ebp)              # assign rhs value to variable
          movl      -8(%ebp), %eax        # place evaluated value in result
                                          # Assignment: begin evaluating rhs
                                          # Loading subscripted array "a[_]"
                                          # Loading variable "k"
          movl      -8(%ebp), %eax        # load local variable value
          movl      %eax, %ebx            # store index value in EBX
          movl      %ebp, %eax            # 
          addl      $8, %eax              # 
          movl      (%eax), %eax          # 
          leal      (%eax,%ebx,4), %ebx   # compute address
          movl      (%ebx), %eax          # load value into EAX
          pushl     %eax                  # save evaluated value
                                          # Loading variable "t"
          movl      -12(%ebp), %eax       # load local variable value
          popl      -12(%ebp)             # assign rhs value to variable
          movl      -12(%ebp), %eax       # place evaluated value in result
                                          # Assignment: begin evaluating rhs
                                          # Loading subscripted array "a[_]"
                                          # Loading variable "i"
          movl      -4(%ebp), %eax        # load local variable value
          movl      %eax, %ebx            # store index value in EBX
          movl      %ebp, %eax            # 
          addl      $8, %eax              # 
          movl      (%eax), %eax          # 
          leal      (%eax,%ebx,4), %ebx   # compute address
          movl      (%ebx), %eax          # load value into EAX
          pushl     %eax                  # save evaluated value
                                          # Loading subscripted array "a[_]"
                                          # Loading variable "k"
          movl      -8(%ebp), %eax        # load local variable value
          movl      %eax, %ebx            # store index value in EBX
          movl      %ebp, %eax            # 
          addl      $8, %eax              # 
          movl      (%eax), %eax          # 
          leal      (%eax,%ebx,4), %ebx   # compute address
          movl      (%ebx), %eax          # load value into EAX
          popl      (%ebx)                # assign rhs value to variable
          movl      (%ebx), %eax          # place evaluated value in result
                                          # Assignment: begin evaluating rhs
                                          # Loading variable "t"
          movl      -12(%ebp), %eax       # load local variable value
          pushl     %eax                  # save evaluated value
                                          # Loading subscripted array "a[_]"
                                          # Loading variable "i"
          movl      -4(%ebp), %eax        # load local variable value
          movl      %eax, %ebx            # store index value in EBX
          movl      %ebp, %eax            # 
          addl      $8, %eax              # 
          movl      (%eax), %eax          # 
          leal      (%eax,%ebx,4), %ebx   # compute address
          movl      (%ebx), %eax          # load value into EAX
          popl      (%ebx)                # assign rhs value to variable
          movl      (%ebx), %eax          # place evaluated value in result
                                          # Assignment: begin evaluating rhs
                                          # Additive expression: begin evaluating rhs
          movl      $1, %eax              # integer literal
          pushl     %eax                  # save rhs value while computing lhs
                                          # Loading variable "i"
          movl      -4(%ebp), %eax        # load local variable value
          popl      %ebx                  # restore rhs operand
          addl      %ebx, %eax            # evaluate additive expression
          pushl     %eax                  # save evaluated value
                                          # Loading variable "i"
          movl      -4(%ebp), %eax        # load local variable value
          popl      -4(%ebp)              # assign rhs value to variable
          movl      -4(%ebp), %eax        # place evaluated value in result
          addl      $4, %esp              # deallocate local variables
                                          # }<- End compound statement
          jmp       .L3                   # }<- end WHILE body
.L4:                                      # exit WHILE
          addl      $8, %esp              # deallocate local variables
                                          # }<- End compound statement
          leave                           # 
          ret                             # 
################################################################################
.globl main
          .type     main, @function       # "main" is type function
main:                                     # 
          enter     $0, $0                # save stack & frame ptrs
                                          # {-> Begin compound statement
          subl      $4, %esp              # allocate local variable i
                                          # Assignment: begin evaluating rhs
          movl      $0, %eax              # integer literal
          pushl     %eax                  # save evaluated value
                                          # Loading variable "i"
          movl      -4(%ebp), %eax        # load local variable value
          popl      -4(%ebp)              # assign rhs value to variable
          movl      -4(%ebp), %eax        # place evaluated value in result
.L5:                                      # 
                                          # relational expression: begin evaluating lhs
                                          # Loading variable "i"
          movl      -4(%ebp), %eax        # load local variable value
          pushl     %eax                  # save lhs while computing rhs
          movl      $10, %eax             # integer literal
          popl      %ebx                  # restore lhs operand
          cmpl      %eax, %ebx            # comparision
          setl      %al                   # relation
          movzbl    %al,%eax              # place evaluated value in result
          cmpl      $0, %eax              # WHILE comparison
          je        .L6                   # 
                                          # {-> begin WHILE body
                                          # {-> Begin compound statement
                                          # Assignment: begin evaluating rhs
          call      input                 # invoke function
          addl      $0, %esp              # remove arguments from stack
          pushl     %eax                  # save evaluated value
                                          # Loading subscripted array "x[_]"
                                          # Loading variable "i"
          movl      -4(%ebp), %eax        # load local variable value
          movl      %eax, %ebx            # store index value in EBX
          movl      x(,%ebx,4), %eax      # load value into EAX
          popl      x(,%ebx,4)            # assign rhs value to variable
          movl      x(,%ebx,4), %eax      # place evaluated value in result
                                          # Assignment: begin evaluating rhs
                                          # Additive expression: begin evaluating rhs
          movl      $1, %eax              # integer literal
          pushl     %eax                  # save rhs value while computing lhs
                                          # Loading variable "i"
          movl      -4(%ebp), %eax        # load local variable value
          popl      %ebx                  # restore rhs operand
          addl      %ebx, %eax            # evaluate additive expression
          pushl     %eax                  # save evaluated value
                                          # Loading variable "i"
          movl      -4(%ebp), %eax        # load local variable value
          popl      -4(%ebp)              # assign rhs value to variable
          movl      -4(%ebp), %eax        # place evaluated value in result
          addl      $0, %esp              # deallocate local variables
                                          # }<- End compound statement
          jmp       .L5                   # }<- end WHILE body
.L6:                                      # exit WHILE
          movl      $10, %eax             # integer literal
          pushl     %eax                  # push function argument onto stack
          movl      $0, %eax              # integer literal
          pushl     %eax                  # push function argument onto stack
                                          # Loading variable "x"
          movl      $x, %eax              # load global value
          pushl     %eax                  # push function argument onto stack
          call      sort                  # invoke function
          addl      $12, %esp             # remove arguments from stack
                                          # Assignment: begin evaluating rhs
          movl      $0, %eax              # integer literal
          pushl     %eax                  # save evaluated value
                                          # Loading variable "i"
          movl      -4(%ebp), %eax        # load local variable value
          popl      -4(%ebp)              # assign rhs value to variable
          movl      -4(%ebp), %eax        # place evaluated value in result
.L7:                                      # 
                                          # relational expression: begin evaluating lhs
                                          # Loading variable "i"
          movl      -4(%ebp), %eax        # load local variable value
          pushl     %eax                  # save lhs while computing rhs
          movl      $10, %eax             # integer literal
          popl      %ebx                  # restore lhs operand
          cmpl      %eax, %ebx            # comparision
          setl      %al                   # relation
          movzbl    %al,%eax              # place evaluated value in result
          cmpl      $0, %eax              # WHILE comparison
          je        .L8                   # 
                                          # {-> begin WHILE body
                                          # {-> Begin compound statement
                                          # Loading subscripted array "x[_]"
                                          # Loading variable "i"
          movl      -4(%ebp), %eax        # load local variable value
          movl      %eax, %ebx            # store index value in EBX
          movl      x(,%ebx,4), %eax      # load value into EAX
          pushl     %eax                  # push function argument onto stack
          call      output                # invoke function
          addl      $4, %esp              # remove arguments from stack
                                          # Assignment: begin evaluating rhs
                                          # Additive expression: begin evaluating rhs
          movl      $1, %eax              # integer literal
          pushl     %eax                  # save rhs value while computing lhs
                                          # Loading variable "i"
          movl      -4(%ebp), %eax        # load local variable value
          popl      %ebx                  # restore rhs operand
          addl      %ebx, %eax            # evaluate additive expression
          pushl     %eax                  # save evaluated value
                                          # Loading variable "i"
          movl      -4(%ebp), %eax        # load local variable value
          popl      -4(%ebp)              # assign rhs value to variable
          movl      -4(%ebp), %eax        # place evaluated value in result
          addl      $0, %esp              # deallocate local variables
                                          # }<- End compound statement
          jmp       .L7                   # }<- end WHILE body
.L8:                                      # exit WHILE
          addl      $4, %esp              # deallocate local variables
                                          # }<- End compound statement
          leave                           # 
          ret                             # 
################################################################################
                                          # Conversion string
          .section  .rodata               # 
.inStr:   .string   "%d"                  
################################################################################
                                          # Input Routine
.globl input
          .type     input, @function      # "input" is type function
input:                                    # 
          enter     $0, $0                # save stack & frame ptrs
          subl      $4, %esp              # create slot for result
          pushl     %esp                  # push slot's address
          pushl     $.inStr               # push conversion spec
          call      scanf                 # read an integer
          movl      8(%esp), %eax         # move int to %eax
          leave                           # reset stack & frame pointers
          ret                             # return to caller
################################################################################
                                          # Conversion string
          .section  .rodata               # 
.outStr:  .string   "%d\n"                
################################################################################
                                          # Output Routine
.globl output
          .type     output, @function     # "output" is type function
output:                                   # 
          enter     $0, $0                # save stack & frame ptrs
          pushl     8(%ebp)               # retrieve the integer to output
          pushl     $.outStr              # push conversion spec
          call      printf                # call printf
          leave                           # reset stack & frame pointers
          ret                             # return to caller
