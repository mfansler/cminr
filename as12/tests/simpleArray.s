################################################################################
                                          # C- Compiled to IA-32 Assembly Instructions
                                          # Compiler v. 0.1.0
################################################################################
                                          # Global Variables
                                          # 
          .globl    a                     # 
          .data                           # 
          .align    4                     # 
          .type     a, @object            # 
          .size     a, 40                 # 
a:                                        # 
          .zero     40                    # initialize to zero
################################################################################
################################################################################
.globl printThird
          .type     printThird, @function # "printThird" is type function
printThird:                               # 
          enter     $0, $0                # save stack & frame ptrs
                                          # {-> Begin compound statement
          movl      $3, %eax              # integer literal
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
          leave                           # 
          ret                             # 
################################################################################
.globl main
          .type     main, @function       # "main" is type function
main:                                     # 
          enter     $0, $0                # save stack & frame ptrs
                                          # {-> Begin compound statement
                                          # Assignment: begin evaluating rhs
          movl      $17, %eax             # integer literal
          pushl     %eax                  # save evaluated value
          movl      $3, %eax              # integer literal
          movl      %eax, %ebx            # store index value in EBX
          movl      a(,%ebx,4), %eax      # load value into EAX
          popl      a(,%ebx,4)            # assign rhs value to variable
          movl      a(,%ebx,4), %eax      # place evaluated value in result
          movl      $a, %eax              # load global value
          pushl     %eax                  # push function argument onto stack
          call      printThird            # invoke function
          addl      $4, %esp              # remove arguments from stack
          addl      $0, %esp              # deallocate local variables
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
