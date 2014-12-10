################################################################################
                                          # C- Compiled to IA-32 Assembly Instructions
                                          # Compiler v. 0.1.0
################################################################################
                                          # Global Variables
                                          # 
################################################################################
################################################################################
.globl triangularNumber
          .type     triangularNumber, @function# "triangularNumber" is type function
triangularNumber:                         # 
          enter     $0, $0                # save stack & frame ptrs
                                          # {-> Begin compound statement
                                          # relational expression: begin evaluating lhs
          movl      8(%ebp), %eax         # load function parameter value
          pushl     %eax                  # save lhs while computing rhs
          movl      $1, %eax              # integer literal
          popl      %ebx                  # restore lhs operand
          cmpl      %eax, %ebx            # comparision
          setl      %al                   # relation
          movzbl    %al,%eax              # place evaluated value in result
          cmpl      $0, %eax              # IF comparison
          je        .L0                   # 
                                          # {-> begin THEN
                                          # {-> Begin compound statement
          movl      $0, %eax              # integer literal
          addl      $0, %esp              # deallocate local variables
                                          # }<- End compound statement
          jmp       .L1                   # }<- end THEN
.L0:                                      # {-> begin ELSE
                                          # {-> Begin compound statement
                                          # Additive expression: begin evaluating rhs
                                          # Additive expression: begin evaluating rhs
          movl      $1, %eax              # integer literal
          pushl     %eax                  # save rhs value while computing lhs
          movl      8(%ebp), %eax         # load function parameter value
          popl      %ebx                  # restore rhs operand
          subl      %ebx, %eax            # evaluate additive expression
          pushl     %eax                  # push function argument onto stack
          call      triangularNumber      # invoke function
          addl      $4, %esp              # remove arguments from stack
          pushl     %eax                  # save rhs value while computing lhs
          movl      8(%ebp), %eax         # load function parameter value
          popl      %ebx                  # restore rhs operand
          addl      %ebx, %eax            # evaluate additive expression
          addl      $0, %esp              # deallocate local variables
                                          # }<- End compound statement
.L1:                                      # }<- end ELSE
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
          subl      $4, %esp              # allocate local variable n
          subl      $4, %esp              # allocate local variable i
                                          # Assignment: begin evaluating rhs
          call      input                 # invoke function
          addl      $0, %esp              # remove arguments from stack
          pushl     %eax                  # save evaluated value
          movl      -4(%ebp), %eax        # load local variable value
          popl      -4(%ebp)              # assign rhs value to variable
          movl      -4(%ebp), %eax        # place evaluated value in result
                                          # FOR initialization
                                          # Assignment: begin evaluating rhs
          movl      $1, %eax              # integer literal
          pushl     %eax                  # save evaluated value
          movl      -8(%ebp), %eax        # load local variable value
          popl      -8(%ebp)              # assign rhs value to variable
          movl      -8(%ebp), %eax        # place evaluated value in result
.L2:                                      # begin FOR loop
                                          # relational expression: begin evaluating lhs
          movl      -8(%ebp), %eax        # load local variable value
          pushl     %eax                  # save lhs while computing rhs
          movl      -4(%ebp), %eax        # load local variable value
          popl      %ebx                  # restore lhs operand
          cmpl      %eax, %ebx            # comparision
          setle     %al                   # relation
          movzbl    %al,%eax              # place evaluated value in result
          cmpl      $0, %eax              # FOR condition
          je        .L3                   # 
                                          # begin FOR body
                                          # {-> Begin compound statement
          movl      -8(%ebp), %eax        # load local variable value
          pushl     %eax                  # push function argument onto stack
          call      triangularNumber      # invoke function
          addl      $4, %esp              # remove arguments from stack
          pushl     %eax                  # push function argument onto stack
          call      output                # invoke function
          addl      $4, %esp              # remove arguments from stack
          addl      $0, %esp              # deallocate local variables
                                          # }<- End compound statement
                                          # end FOR body
                                          # unary operation
          movl      -8(%ebp), %eax        # load local variable value
          incl      -8(%ebp)              # increment/decrement variable
          movl      -8(%ebp), %eax        # pass result
          jmp       .L2                   # return to FOR begin
.L3:                                      # exit FOR loop
          addl      $8, %esp              # deallocate local variables
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
