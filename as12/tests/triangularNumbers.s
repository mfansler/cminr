################################################################################
                                          # C- Compiled to IA-32 Code
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
                                          # relational expression
          movl      8(%ebp), %eax         # local variable
          pushl     %eax                  # stash left operand
          movl      $1, %eax              # integer literal
          popl      %ebx                  # restore left operand
          cmpl      %eax, %ebx            # comparision
          setl      %al                   # relation
          movzbl    %al,%eax              # return result
          cmpl      $0, %eax              # test condition
          je        .L0                   # 
          movl      $0, %eax              # integer literal
          addl      $0, %esp              # deallocate local variables
          jmp       .L1                   # 
.L0:                                      # 
          movl      $1, %eax              # integer literal
          pushl     %eax                  # push right operand to stack
          movl      8(%ebp), %eax         # local variable
          popl      %ebx                  # pop right operand to EBX
          subl      %ebx, %eax            # evaluate additive expression
          pushl     %eax                  # push function argument onto stack
          call      triangularNumber      # invoke function
          pushl     %eax                  # push right operand to stack
          movl      8(%ebp), %eax         # local variable
          popl      %ebx                  # pop right operand to EBX
          addl      %ebx, %eax            # evaluate additive expression
          addl      $0, %esp              # deallocate local variables
.L1:                                      # 
          addl      $0, %esp              # deallocate local variables
          leave                           # 
          ret                             # 
################################################################################
.globl main
          .type     main, @function       # "main" is type function
main:                                     # 
          enter     $0, $0                # save stack & frame ptrs
          subl      $4, %esp              # allocate local variable n
          subl      $4, %esp              # allocate local variable i
          call      input                 # invoke function
          pushl     %eax                  # save assigning value
          movl      -4(%ebp), %eax        # local variable
          popl      -4(%ebp)              # pop value into variable
          movl      -4(%ebp), %eax        # pass result
          movl      $1, %eax              # integer literal
          pushl     %eax                  # save assigning value
          movl      -8(%ebp), %eax        # local variable
          popl      -8(%ebp)              # pop value into variable
          movl      -8(%ebp), %eax        # pass result
.L2:                                      # 
                                          # relational expression
          movl      -8(%ebp), %eax        # local variable
          pushl     %eax                  # stash left operand
          movl      -4(%ebp), %eax        # local variable
          popl      %ebx                  # restore left operand
          cmpl      %eax, %ebx            # comparision
          setle     %al                   # relation
          movzbl    %al,%eax              # return result
          cmpl      $0, %eax              # test condition
          je        .L3                   # 
          movl      -8(%ebp), %eax        # local variable
          pushl     %eax                  # push function argument onto stack
          call      triangularNumber      # invoke function
          pushl     %eax                  # push function argument onto stack
          call      output                # invoke function
          addl      $0, %esp              # deallocate local variables
          movl      -8(%ebp), %eax        # local variable
          incl      -8(%ebp)              # increment/decrement variable
          movl      -8(%ebp), %eax        # pass result
          jmp       .L2                   # 
.L3:                                      # 
          addl      $8, %esp              # deallocate local variables
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
