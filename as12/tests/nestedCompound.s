################################################################################
                                          # C- Compiled to IA-32 Code
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
                                          # {-> Begin coumpound statement
          subl      $4, %esp              # allocate local variable x
          movl      $13, %eax             # integer literal
          pushl     %eax                  # save assigning value
          movl      -4(%ebp), %eax        # load local variable value
          popl      -4(%ebp)              # pop value into variable
          movl      -4(%ebp), %eax        # pass result
                                          # {-> Begin coumpound statement
          subl      $4, %esp              # allocate local variable x
          movl      $57, %eax             # integer literal
          pushl     %eax                  # save assigning value
          movl      -8(%ebp), %eax        # load local variable value
          popl      -8(%ebp)              # pop value into variable
          movl      -8(%ebp), %eax        # pass result
          movl      -8(%ebp), %eax        # load local variable value
          pushl     %eax                  # push function argument onto stack
          call      output                # invoke function
          addl      $4, %esp              # remove arguments from stack
          addl      $4, %esp              # deallocate local variables
                                          # }<- End coumpound statement
          movl      -4(%ebp), %eax        # load local variable value
          pushl     %eax                  # push function argument onto stack
          call      output                # invoke function
          addl      $4, %esp              # remove arguments from stack
          addl      $4, %esp              # deallocate local variables
                                          # }<- End coumpound statement
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
