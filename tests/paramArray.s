################################################################################
                                          # C- Compiled to IA-32 Code
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
          movl      12(%ebp), %eax        # variable expression
          movl      %eax, %ebx            # store index value in EBX
          movl      %ebp, %eax            # 
          addl      $20, %eax             # 
          leal      (%eax,%ebx,4), %ebx   # compute address
          movl      (%ebx), %eax          # load value into EAX
          pushl     %eax                  # push function argument onto stack
          call      output                # invoke function
          addl      $0, %esp              # deallocate local variables
          leave                           # 
          ret                             # 
################################################################################
.globl main
          .type     main, @function       # "main" is type function
main:                                     # 
          enter     $0, $0                # save stack & frame ptrs
          subl      $40, %esp             # allocate local array a
          subl      $4, %esp              # allocate local variable i
          movl      $0, %eax              # integer literal
          pushl     %eax                  # save assigning value
          movl      -44(%ebp), %eax       # variable expression
          popl      -44(%ebp)             # pop value into variable
          movl      -44(%ebp), %eax       # pass result
.L0:                                      # 
                                          # relational expression
          movl      -44(%ebp), %eax       # variable expression
          pushl     %eax                  # stash left operand
          movl      $10, %eax             # integer literal
          popl      %ebx                  # restore left operand
          cmpl      %eax, %ebx            # comparision
          setl      %al                   # relation
          movzbl    %al,%eax              # return result
          cmpl      $0, %eax              # test condition
          je        .L1                   # 
          movl      -44(%ebp), %eax       # variable expression
          pushl     %eax                  # save assigning value
          movl      -44(%ebp), %eax       # variable expression
          movl      %eax, %ebx            # store index value in EBX
          movl      %ebp, %eax            # 
          subl      $40, %eax             # 
          leal      (%eax,%ebx,4), %ebx   # compute address
          movl      (%ebx), %eax          # load value into EAX
          popl      (%ebx)                # pop value into variable
          movl      (%ebx), %eax          # pass result
          movl      -44(%ebp), %eax       # variable expression
          pushl     %eax                  # push function argument onto stack
          call      output                # invoke function
          movl      -44(%ebp), %eax       # variable expression
          movl      %eax, %ebx            # store index value in EBX
          movl      %ebp, %eax            # 
          subl      $40, %eax             # 
          leal      (%eax,%ebx,4), %ebx   # compute address
          movl      (%ebx), %eax          # load value into EAX
          pushl     %eax                  # push function argument onto stack
          call      output                # invoke function
          movl      -44(%ebp), %eax       # variable expression
          pushl     %eax                  # push function argument onto stack
          movl      -40(%ebp), %eax       # variable expression
          pushl     %eax                  # push function argument onto stack
          call      get                   # invoke function
          addl      $0, %esp              # deallocate local variables
          movl      -44(%ebp), %eax       # variable expression
          incl      -44(%ebp)             # increment/decrement variable
          movl      -44(%ebp), %eax       # pass result
          jmp       .L0                   # 
.L1:                                      # 
          addl      $44, %esp             # deallocate local variables
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
