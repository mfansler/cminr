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
                                          # Multiplicative expression: begin evaluating rhs
          movl      $5, %eax              # integer literal
          pushl     %eax                  # save rhs while computing lhs
          movl      $5, %eax              # integer literal
          popl      %ebx                  # restore right operand
          imul      %ebx, %eax            # evaluate multiplication
          pushl     %eax                  # push function argument onto stack
          call      output                # invoke function
          addl      $4, %esp              # remove arguments from stack
                                          # Multiplicative expression: begin evaluating rhs
          movl      $2, %eax              # integer literal
          pushl     %eax                  # save rhs while computing lhs
          movl      $10, %eax             # integer literal
          popl      %ebx                  # restore divisor
          cdq                             # change Double EAX to Quad EDX:EAX
                                          # see: http://stackoverflow.com/a/19853558
          idivl     %ebx                  # divide EDX:EAX by EBX
          pushl     %eax                  # push function argument onto stack
          call      output                # invoke function
          addl      $4, %esp              # remove arguments from stack
                                          # Multiplicative expression: begin evaluating rhs
          movl      $113, %eax            # integer literal
          pushl     %eax                  # save rhs while computing lhs
          movl      $355, %eax            # integer literal
          popl      %ebx                  # restore divisor
          cdq                             # change Double EAX to Quad EDX:EAX
                                          # see: http://stackoverflow.com/a/19853558
          idivl     %ebx                  # divide EDX:EAX by EBX
          pushl     %eax                  # push function argument onto stack
          call      output                # invoke function
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
