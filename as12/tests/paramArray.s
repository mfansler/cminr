################################################################################
                                          # C- Compiled to IA-32 Assembly Instructions
                                          # Compiler v. 0.1.0
################################################################################
                                          # Global Variables
                                          # 
################################################################################
################################################################################
.globl get
          .type     get, @function        # "get" is type function
get:                                      # 
          enter     $0, $0                # save stack & frame ptrs
                                          # {-> Begin compound statement
          movl      8(%ebp), %eax         # load function parameter value
          movl      %eax, %ebx            # store index value in EBX
          movl      %ebp, %eax            # 
          addl      $12, %eax             # 
          movl      (%eax), %eax          # 
          leal      (%eax,%ebx,4), %ebx   # compute address
          movl      (%ebx), %eax          # load value into EAX
          pushl     %eax                  # push function argument onto stack
          call      output                # invoke function
          addl      $4, %esp              # remove arguments from stack
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
          subl      $40, %esp             # allocate local array a
          subl      $4, %esp              # allocate local variable i
                                          # FOR initialization
                                          # Assignment: begin evaluating rhs
          movl      $0, %eax              # integer literal
          pushl     %eax                  # save evaluated value
          movl      -44(%ebp), %eax       # load local variable value
          popl      -44(%ebp)             # assign rhs value to variable
          movl      -44(%ebp), %eax       # place evaluated value in result
.L0:                                      # begin FOR loop
                                          # relational expression: begin evaluating lhs
          movl      -44(%ebp), %eax       # load local variable value
          pushl     %eax                  # save lhs while computing rhs
          movl      $10, %eax             # integer literal
          popl      %ebx                  # restore lhs operand
          cmpl      %eax, %ebx            # comparision
          setl      %al                   # relation
          movzbl    %al,%eax              # place evaluated value in result
          cmpl      $0, %eax              # FOR condition
          je        .L1                   # 
                                          # begin FOR body
                                          # {-> Begin compound statement
                                          # Assignment: begin evaluating rhs
          movl      -44(%ebp), %eax       # load local variable value
          pushl     %eax                  # save evaluated value
          movl      -44(%ebp), %eax       # load local variable value
          movl      %eax, %ebx            # store index value in EBX
          movl      %ebp, %eax            # 
          subl      $40, %eax             # 
          leal      (%eax,%ebx,4), %ebx   # compute address
          movl      (%ebx), %eax          # load value into EAX
          popl      (%ebx)                # assign rhs value to variable
          movl      (%ebx), %eax          # place evaluated value in result
          movl      -44(%ebp), %eax       # load local variable value
          pushl     %eax                  # push function argument onto stack
          call      output                # invoke function
          addl      $4, %esp              # remove arguments from stack
          movl      -44(%ebp), %eax       # load local variable value
          movl      %eax, %ebx            # store index value in EBX
          movl      %ebp, %eax            # 
          subl      $40, %eax             # 
          leal      (%eax,%ebx,4), %ebx   # compute address
          movl      (%ebx), %eax          # load value into EAX
          pushl     %eax                  # push function argument onto stack
          call      output                # invoke function
          addl      $4, %esp              # remove arguments from stack
          movl      %ebp, %eax            # prepare to compute array address
          subl      $40, %eax             # load array address
          pushl     %eax                  # push function argument onto stack
          movl      -44(%ebp), %eax       # load local variable value
          pushl     %eax                  # push function argument onto stack
          call      get                   # invoke function
          addl      $8, %esp              # remove arguments from stack
          addl      $0, %esp              # deallocate local variables
                                          # }<- End compound statement
                                          # end FOR body
                                          # unary operation
          movl      -44(%ebp), %eax       # load local variable value
          incl      -44(%ebp)             # increment/decrement variable
          movl      -44(%ebp), %eax       # pass result
          jmp       .L0                   # return to FOR begin
.L1:                                      # exit FOR loop
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
