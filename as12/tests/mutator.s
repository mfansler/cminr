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
          .size     x, 4                  # 
x:                                        # 
          .zero     4                     # 
          .globl    y                     # 
          .data                           # 
          .align    4                     # 
          .type     y, @object            # 
          .size     y, 40                 # 
y:                                        # 
          .zero     40                    # initialize to zero
################################################################################
################################################################################
.globl outputArray
          .type     outputArray, @function# "outputArray" is type function
outputArray:                              # 
          enter     $0, $0                # save stack & frame ptrs
                                          # {-> Begin compound statement
          subl      $4, %esp              # allocate local variable i
                                          # FOR initialization
                                          # Assignment: begin evaluating rhs
          movl      $0, %eax              # integer literal
          pushl     %eax                  # save evaluated value
          movl      -4(%ebp), %eax        # load local variable value
          popl      -4(%ebp)              # assign rhs value to variable
          movl      -4(%ebp), %eax        # place evaluated value in result
.L0:                                      # begin FOR loop
                                          # relational expression: begin evaluating lhs
          movl      -4(%ebp), %eax        # load local variable value
          pushl     %eax                  # save lhs while computing rhs
          movl      12(%ebp), %eax        # load function parameter value
          popl      %ebx                  # restore lhs operand
          cmpl      %eax, %ebx            # comparision
          setl      %al                   # relation
          movzbl    %al,%eax              # place evaluated value in result
          cmpl      $0, %eax              # FOR condition
          je        .L1                   # 
                                          # begin FOR body
                                          # {-> Begin compound statement
          movl      -4(%ebp), %eax        # load local variable value
          movl      %eax, %ebx            # store index value in EBX
          movl      %ebp, %eax            # 
          addl      $8, %eax              # 
          movl      (%eax), %eax          # 
          leal      (%eax,%ebx,4), %ebx   # compute address
          movl      (%ebx), %eax          # load value into EAX
          pushl     %eax                  # push function argument onto stack
          call      output                # invoke function
          addl      $4, %esp              # remove arguments from stack
          addl      $0, %esp              # deallocate local variables
                                          # }<- End compound statement
                                          # end FOR body
                                          # unary operation
          movl      -4(%ebp), %eax        # load local variable value
          incl      -4(%ebp)              # increment/decrement variable
          movl      -4(%ebp), %eax        # pass result
          jmp       .L0                   # return to FOR begin
.L1:                                      # exit FOR loop
          addl      $4, %esp              # deallocate local variables
                                          # }<- End compound statement
          leave                           # 
          ret                             # 
################################################################################
.globl initArray
          .type     initArray, @function  # "initArray" is type function
initArray:                                # 
          enter     $0, $0                # save stack & frame ptrs
                                          # {-> Begin compound statement
          subl      $4, %esp              # allocate local variable i
                                          # FOR initialization
                                          # Assignment: begin evaluating rhs
          movl      $0, %eax              # integer literal
          pushl     %eax                  # save evaluated value
          movl      -4(%ebp), %eax        # load local variable value
          popl      -4(%ebp)              # assign rhs value to variable
          movl      -4(%ebp), %eax        # place evaluated value in result
.L2:                                      # begin FOR loop
                                          # relational expression: begin evaluating lhs
          movl      -4(%ebp), %eax        # load local variable value
          pushl     %eax                  # save lhs while computing rhs
          movl      12(%ebp), %eax        # load function parameter value
          popl      %ebx                  # restore lhs operand
          cmpl      %eax, %ebx            # comparision
          setl      %al                   # relation
          movzbl    %al,%eax              # place evaluated value in result
          cmpl      $0, %eax              # FOR condition
          je        .L3                   # 
                                          # begin FOR body
                                          # {-> Begin compound statement
                                          # Assignment: begin evaluating rhs
          movl      -4(%ebp), %eax        # load local variable value
          pushl     %eax                  # save evaluated value
          movl      -4(%ebp), %eax        # load local variable value
          movl      %eax, %ebx            # store index value in EBX
          movl      %ebp, %eax            # 
          addl      $8, %eax              # 
          movl      (%eax), %eax          # 
          leal      (%eax,%ebx,4), %ebx   # compute address
          movl      (%ebx), %eax          # load value into EAX
          popl      (%ebx)                # assign rhs value to variable
          movl      (%ebx), %eax          # place evaluated value in result
          addl      $0, %esp              # deallocate local variables
                                          # }<- End compound statement
                                          # end FOR body
                                          # unary operation
          movl      -4(%ebp), %eax        # load local variable value
          incl      -4(%ebp)              # increment/decrement variable
          movl      -4(%ebp), %eax        # pass result
          jmp       .L2                   # return to FOR begin
.L3:                                      # exit FOR loop
          addl      $4, %esp              # deallocate local variables
                                          # }<- End compound statement
          leave                           # 
          ret                             # 
################################################################################
.globl mutateSquare
          .type     mutateSquare, @function# "mutateSquare" is type function
mutateSquare:                             # 
          enter     $0, $0                # save stack & frame ptrs
                                          # {-> Begin compound statement
                                          # Assignment: begin evaluating rhs
                                          # Multiplicative expression: begin evaluating rhs
          movl      8(%ebp), %eax         # load function parameter value
          pushl     %eax                  # save rhs while computing lhs
          movl      8(%ebp), %eax         # load function parameter value
          popl      %ebx                  # restore right operand
          imul      %ebx, %eax            # evaluate multiplication
          pushl     %eax                  # save evaluated value
          movl      8(%ebp), %eax         # load function parameter value
          popl      8(%ebp)               # assign rhs value to variable
          movl      8(%ebp), %eax         # place evaluated value in result
          addl      $0, %esp              # deallocate local variables
                                          # }<- End compound statement
          leave                           # 
          ret                             # 
################################################################################
.globl main
          .type     main, @function       # "main" is type function
main:                                     # 
          enter     $0, $0                # save stack & frame ptrs
                                          # {-> Begin compound statement
          subl      $4, %esp              # allocate local variable t
          subl      $40, %esp             # allocate local array u
                                          # Assignment: begin evaluating rhs
          movl      $4, %eax              # integer literal
          pushl     %eax                  # save evaluated value
          movl      x, %eax               # load global value
          popl      x                     # assign rhs value to variable
          movl      x, %eax               # place evaluated value in result
                                          # Assignment: begin evaluating rhs
          movl      $13, %eax             # integer literal
          pushl     %eax                  # save evaluated value
          movl      -4(%ebp), %eax        # load local variable value
          popl      -4(%ebp)              # assign rhs value to variable
          movl      -4(%ebp), %eax        # place evaluated value in result
          movl      $10, %eax             # integer literal
          pushl     %eax                  # push function argument onto stack
          movl      $y, %eax              # load global value
          pushl     %eax                  # push function argument onto stack
          call      outputArray           # invoke function
          addl      $8, %esp              # remove arguments from stack
          movl      $10, %eax             # integer literal
          pushl     %eax                  # push function argument onto stack
          movl      $y, %eax              # load global value
          pushl     %eax                  # push function argument onto stack
          call      initArray             # invoke function
          addl      $8, %esp              # remove arguments from stack
          movl      $10, %eax             # integer literal
          pushl     %eax                  # push function argument onto stack
          movl      $y, %eax              # load global value
          pushl     %eax                  # push function argument onto stack
          call      outputArray           # invoke function
          addl      $8, %esp              # remove arguments from stack
          movl      x, %eax               # load global value
          pushl     %eax                  # push function argument onto stack
          call      output                # invoke function
          addl      $4, %esp              # remove arguments from stack
          movl      x, %eax               # load global value
          pushl     %eax                  # push function argument onto stack
          call      mutateSquare          # invoke function
          addl      $4, %esp              # remove arguments from stack
          movl      x, %eax               # load global value
          pushl     %eax                  # push function argument onto stack
          call      output                # invoke function
          addl      $4, %esp              # remove arguments from stack
          movl      $10, %eax             # integer literal
          pushl     %eax                  # push function argument onto stack
          movl      %ebp, %eax            # prepare to compute array address
          subl      $44, %eax             # load array address
          pushl     %eax                  # push function argument onto stack
          call      outputArray           # invoke function
          addl      $8, %esp              # remove arguments from stack
          movl      $10, %eax             # integer literal
          pushl     %eax                  # push function argument onto stack
          movl      %ebp, %eax            # prepare to compute array address
          subl      $44, %eax             # load array address
          pushl     %eax                  # push function argument onto stack
          call      initArray             # invoke function
          addl      $8, %esp              # remove arguments from stack
          movl      $10, %eax             # integer literal
          pushl     %eax                  # push function argument onto stack
          movl      %ebp, %eax            # prepare to compute array address
          subl      $44, %eax             # load array address
          pushl     %eax                  # push function argument onto stack
          call      outputArray           # invoke function
          addl      $8, %esp              # remove arguments from stack
          movl      -4(%ebp), %eax        # load local variable value
          pushl     %eax                  # push function argument onto stack
          call      output                # invoke function
          addl      $4, %esp              # remove arguments from stack
          movl      -4(%ebp), %eax        # load local variable value
          pushl     %eax                  # push function argument onto stack
          call      mutateSquare          # invoke function
          addl      $4, %esp              # remove arguments from stack
          movl      -4(%ebp), %eax        # load local variable value
          pushl     %eax                  # push function argument onto stack
          call      output                # invoke function
          addl      $4, %esp              # remove arguments from stack
          addl      $44, %esp             # deallocate local variables
                                          # }<- End compound statement
          leave                           # 
          ret                             # 
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
