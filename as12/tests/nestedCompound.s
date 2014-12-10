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
                                          # Assignment: begin evaluating rhs
          movl      $13, %eax             # integer literal
          pushl     %eax                  # save evaluated value
          movl      -4(%ebp), %eax        # load local variable value
          popl      -4(%ebp)              # assign rhs value to variable
          movl      -4(%ebp), %eax        # place evaluated value in result
                                          # {-> Begin compound statement
          subl      $4, %esp              # allocate local variable x
                                          # Assignment: begin evaluating rhs
          movl      $57, %eax             # integer literal
          pushl     %eax                  # save evaluated value
          movl      -8(%ebp), %eax        # load local variable value
          popl      -8(%ebp)              # assign rhs value to variable
          movl      -8(%ebp), %eax        # place evaluated value in result
          movl      -8(%ebp), %eax        # load local variable value
          pushl     %eax                  # push function argument onto stack
          call      output                # invoke function
          addl      $4, %esp              # remove arguments from stack
          addl      $4, %esp              # deallocate local variables
                                          # }<- End compound statement
          movl      -4(%ebp), %eax        # load local variable value
          pushl     %eax                  # push function argument onto stack
          call      output                # invoke function
          addl      $4, %esp              # remove arguments from stack
          addl      $4, %esp              # deallocate local variables
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
