################################################################################
                                          # C- Compiled to IA-32 Code
                                          # 
                                          # Compiler v. 0.1.0
################################################################################
################################################################################
.globl main
          .type     main, @function       # "main" is type function
main:                                     # 
          enter     $0, $0                # save stack & frame ptrs
          movl      $5, %eax              # integer literal
          pushl     %eax                  # push right operand to stack
          movl      $5, %eax              # integer literal
          popl      %ebx                  # restore right operand
          imul      %ebx, %eax            # evaluate multiplication
          pushl     %eax                  # push function argument onto stack
          call      output                # invoke function
          movl      $2, %eax              # integer literal
          pushl     %eax                  # push right operand to stack
          movl      $10, %eax             # integer literal
          popl      %ebx                  # restore divisor
          movl      $0, %edx              # initialize EDX to 0
          idivl     %ebx                  # divide EDX:EAX by EBX
          pushl     %eax                  # push function argument onto stack
          call      output                # invoke function
          movl      $113, %eax            # integer literal
          pushl     %eax                  # push right operand to stack
          movl      $355, %eax            # integer literal
          popl      %ebx                  # restore divisor
          movl      $0, %edx              # initialize EDX to 0
          idivl     %ebx                  # divide EDX:EAX by EBX
          pushl     %eax                  # push function argument onto stack
          call      output                # invoke function
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
