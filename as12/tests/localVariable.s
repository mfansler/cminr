################################################################################
                                          # C- Compiled to IA-32 Assembly Instructions
                                          # Compiler v. 0.1.0
################################################################################
                                          # Global Variables
                                          # 
################################################################################
################################################################################
.globl main
          .type     main, @function       # "main" is type function
main:                                     # 
          enter     $0, $0                # save stack & frame ptrs
                                          # {-> Begin compound statement
          subl      $4, %esp              # allocate local variable x
          subl      $4, %esp              # allocate local variable y
                                          # Assignment: begin evaluating rhs
          call      input                 # invoke function
          addl      $0, %esp              # remove arguments from stack
          pushl     %eax                  # save evaluated value
          movl      -4(%ebp), %eax        # load local variable value
          popl      -4(%ebp)              # assign rhs value to variable
          movl      -4(%ebp), %eax        # place evaluated value in result
                                          # Assignment: begin evaluating rhs
          call      input                 # invoke function
          addl      $0, %esp              # remove arguments from stack
          pushl     %eax                  # save evaluated value
          movl      -8(%ebp), %eax        # load local variable value
          popl      -8(%ebp)              # assign rhs value to variable
          movl      -8(%ebp), %eax        # place evaluated value in result
                                          # Additive expression: begin evaluating rhs
          movl      -8(%ebp), %eax        # load local variable value
          pushl     %eax                  # save rhs value while computing lhs
          movl      -4(%ebp), %eax        # load local variable value
          popl      %ebx                  # restore rhs operand
          addl      %ebx, %eax            # evaluate additive expression
          pushl     %eax                  # push function argument onto stack
          call      output                # invoke function
          addl      $4, %esp              # remove arguments from stack
                                          # Multiplicative expression: begin evaluating rhs
          movl      -8(%ebp), %eax        # load local variable value
          pushl     %eax                  # save rhs while computing lhs
          movl      -4(%ebp), %eax        # load local variable value
          popl      %ebx                  # restore right operand
          imul      %ebx, %eax            # evaluate multiplication
          pushl     %eax                  # push function argument onto stack
          call      output                # invoke function
          addl      $4, %esp              # remove arguments from stack
                                          # Additive expression: begin evaluating rhs
          movl      -4(%ebp), %eax        # load local variable value
          pushl     %eax                  # save rhs value while computing lhs
          movl      -8(%ebp), %eax        # load local variable value
          popl      %ebx                  # restore rhs operand
          subl      %ebx, %eax            # evaluate additive expression
          pushl     %eax                  # push function argument onto stack
          call      output                # invoke function
          addl      $4, %esp              # remove arguments from stack
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
