################################################################################
                                          # C- Compiled to IA-32 Code
                                          # Compiler v. 0.1.0
################################################################################
                                          # Global Variables
                                          # 
################################################################################
################################################################################
.globl gcd
          .type     gcd, @function        # "gcd" is type function
gcd:                                      # 
          enter     $0, $0                # save stack & frame ptrs
                                          # {-> Begin coumpound statement
                                          # relational expression
          movl      12(%ebp), %eax        # load function parameter value
          pushl     %eax                  # stash left operand
          movl      $0, %eax              # integer literal
          popl      %ebx                  # restore left operand
          cmpl      %eax, %ebx            # comparision
          sete      %al                   # relation
          movzbl    %al,%eax              # return result
          cmpl      $0, %eax              # test condition
          je        .L0                   # 
          movl      8(%ebp), %eax         # load function parameter value
          jmp       .L1                   # 
.L0:                                      # 
          movl      12(%ebp), %eax        # load function parameter value
          pushl     %eax                  # push right operand to stack
          movl      12(%ebp), %eax        # load function parameter value
          pushl     %eax                  # push right operand to stack
          movl      8(%ebp), %eax         # load function parameter value
          popl      %ebx                  # restore divisor
          cdq                             # change Double EAX to Quad EDX:EAX
                                          # see: http://stackoverflow.com/a/19853558
          idivl     %ebx                  # divide EDX:EAX by EBX
          popl      %ebx                  # restore right operand
          imul      %ebx, %eax            # evaluate multiplication
          pushl     %eax                  # push right operand to stack
          movl      8(%ebp), %eax         # load function parameter value
          popl      %ebx                  # pop right operand to EBX
          subl      %ebx, %eax            # evaluate additive expression
          pushl     %eax                  # push function argument onto stack
          movl      12(%ebp), %eax        # load function parameter value
          pushl     %eax                  # push function argument onto stack
          call      gcd                   # invoke function
          addl      $8, %esp              # remove arguments from stack
.L1:                                      # 
          addl      $0, %esp              # deallocate local variables
                                          # }<- End coumpound statement
          leave                           # 
          ret                             # 
################################################################################
.globl main
          .type     main, @function       # "main" is type function
main:                                     # 
          enter     $0, $0                # save stack & frame ptrs
                                          # {-> Begin coumpound statement
          subl      $4, %esp              # allocate local variable x
          subl      $4, %esp              # allocate local variable y
          call      input                 # invoke function
          addl      $0, %esp              # remove arguments from stack
          pushl     %eax                  # save assigning value
          movl      -4(%ebp), %eax        # load variable value
          popl      -4(%ebp)              # pop value into variable
          movl      -4(%ebp), %eax        # pass result
          call      input                 # invoke function
          addl      $0, %esp              # remove arguments from stack
          pushl     %eax                  # save assigning value
          movl      -8(%ebp), %eax        # load variable value
          popl      -8(%ebp)              # pop value into variable
          movl      -8(%ebp), %eax        # pass result
          movl      -8(%ebp), %eax        # load variable value
          pushl     %eax                  # push function argument onto stack
          movl      -4(%ebp), %eax        # load variable value
          pushl     %eax                  # push function argument onto stack
          call      gcd                   # invoke function
          addl      $8, %esp              # remove arguments from stack
          pushl     %eax                  # push function argument onto stack
          call      output                # invoke function
          addl      $4, %esp              # remove arguments from stack
          addl      $8, %esp              # deallocate local variables
                                          # }<- End coumpound statement
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
