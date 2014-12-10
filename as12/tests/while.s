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
          movl      $10, %eax             # integer literal
          pushl     %eax                  # save evaluated value
          movl      -4(%ebp), %eax        # load local variable value
          popl      -4(%ebp)              # assign rhs value to variable
          movl      -4(%ebp), %eax        # place evaluated value in result
.L0:                                      # 
                                          # relational expression: begin evaluating lhs
          movl      -4(%ebp), %eax        # load local variable value
          pushl     %eax                  # save lhs while computing rhs
          movl      $0, %eax              # integer literal
          popl      %ebx                  # restore lhs operand
          cmpl      %eax, %ebx            # comparision
          setg      %al                   # relation
          movzbl    %al,%eax              # place evaluated value in result
          cmpl      $0, %eax              # WHILE comparison
          je        .L1                   # 
                                          # {-> begin WHILE body
                                          # {-> Begin compound statement
          movl      -4(%ebp), %eax        # load local variable value
          pushl     %eax                  # push function argument onto stack
          call      output                # invoke function
          addl      $4, %esp              # remove arguments from stack
                                          # unary operation
          movl      -4(%ebp), %eax        # load local variable value
          decl      -4(%ebp)              # increment/decrement variable
          movl      -4(%ebp), %eax        # pass result
          addl      $0, %esp              # deallocate local variables
                                          # }<- End compound statement
          jmp       .L0                   # }<- end WHILE body
.L1:                                      # exit WHILE
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
