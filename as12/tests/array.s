################################################################################
                                          # C- Compiled to IA-32 Code
                                          # Compiler v. 0.1.0
################################################################################
                                          # Global Variables
                                          # 
          .globl    x                     # 
          .data                           # 
          .align    4                     # 
          .type     x, @object            # 
          .size     x, 40                 # 
x:                                        # 
          .zero     40                    # initialize to zero
################################################################################
################################################################################
.globl main
          .type     main, @function       # "main" is type function
main:                                     # 
          enter     $0, $0                # save stack & frame ptrs
                                          # {-> Begin coumpound statement
          subl      $4, %esp              # allocate local variable i
          subl      $40, %esp             # allocate local array y
          movl      $0, %eax              # integer literal
          pushl     %eax                  # save assigning value
          movl      -4(%ebp), %eax        # load local variable value
          popl      -4(%ebp)              # pop value into variable
          movl      -4(%ebp), %eax        # pass result
.L0:                                      # 
                                          # relational expression
          movl      -4(%ebp), %eax        # load local variable value
          pushl     %eax                  # stash left operand
          movl      $10, %eax             # integer literal
          popl      %ebx                  # restore left operand
          cmpl      %eax, %ebx            # comparision
          setl      %al                   # relation
          movzbl    %al,%eax              # return result
          cmpl      $0, %eax              # test condition
          je        .L1                   # 
                                          # {-> Begin coumpound statement
          movl      -4(%ebp), %eax        # load local variable value
          pushl     %eax                  # save assigning value
          movl      -4(%ebp), %eax        # load local variable value
          movl      %eax, %ebx            # store index value in EBX
          movl      x(,%ebx,4), %eax      # load value into EAX
          popl      x(,%ebx,4)            # pop value into variable
          movl      x(,%ebx,4), %eax      # pass result
          addl      $0, %esp              # deallocate local variables
                                          # }<- End coumpound statement
                                          # end for body
          movl      -4(%ebp), %eax        # load local variable value
          incl      -4(%ebp)              # increment/decrement variable
          movl      -4(%ebp), %eax        # pass result
          jmp       .L0                   # return to FOR begin
.L1:                                      # 
          movl      $0, %eax              # integer literal
          pushl     %eax                  # save assigning value
          movl      -4(%ebp), %eax        # load local variable value
          popl      -4(%ebp)              # pop value into variable
          movl      -4(%ebp), %eax        # pass result
.L2:                                      # 
                                          # relational expression
          movl      -4(%ebp), %eax        # load local variable value
          pushl     %eax                  # stash left operand
          movl      $10, %eax             # integer literal
          popl      %ebx                  # restore left operand
          cmpl      %eax, %ebx            # comparision
          setl      %al                   # relation
          movzbl    %al,%eax              # return result
          cmpl      $0, %eax              # test condition
          je        .L3                   # 
                                          # {-> Begin coumpound statement
          movl      -4(%ebp), %eax        # load local variable value
          movl      %eax, %ebx            # store index value in EBX
          movl      x(,%ebx,4), %eax      # load value into EAX
          pushl     %eax                  # push function argument onto stack
          call      output                # invoke function
          addl      $4, %esp              # remove arguments from stack
          addl      $0, %esp              # deallocate local variables
                                          # }<- End coumpound statement
                                          # end for body
          movl      -4(%ebp), %eax        # load local variable value
          incl      -4(%ebp)              # increment/decrement variable
          movl      -4(%ebp), %eax        # pass result
          jmp       .L2                   # return to FOR begin
.L3:                                      # 
          movl      $0, %eax              # integer literal
          pushl     %eax                  # save assigning value
          movl      -4(%ebp), %eax        # load local variable value
          popl      -4(%ebp)              # pop value into variable
          movl      -4(%ebp), %eax        # pass result
.L4:                                      # 
                                          # relational expression
          movl      -4(%ebp), %eax        # load local variable value
          pushl     %eax                  # stash left operand
          movl      $10, %eax             # integer literal
          popl      %ebx                  # restore left operand
          cmpl      %eax, %ebx            # comparision
          setl      %al                   # relation
          movzbl    %al,%eax              # return result
          cmpl      $0, %eax              # test condition
          je        .L5                   # 
                                          # {-> Begin coumpound statement
          movl      -4(%ebp), %eax        # load local variable value
          movl      %eax, %ebx            # store index value in EBX
          movl      x(,%ebx,4), %eax      # load value into EAX
          pushl     %eax                  # push right operand to stack
          movl      -4(%ebp), %eax        # load local variable value
          movl      %eax, %ebx            # store index value in EBX
          movl      x(,%ebx,4), %eax      # load value into EAX
          popl      %ebx                  # restore right operand
          imul      %ebx, %eax            # evaluate multiplication
          pushl     %eax                  # save assigning value
          movl      -4(%ebp), %eax        # load local variable value
          movl      %eax, %ebx            # store index value in EBX
          movl      %ebp, %eax            # 
          subl      $44, %eax             # 
          leal      (%eax,%ebx,4), %ebx   # compute address
          movl      (%ebx), %eax          # load value into EAX
          popl      (%ebx)                # pop value into variable
          movl      (%ebx), %eax          # pass result
          addl      $0, %esp              # deallocate local variables
                                          # }<- End coumpound statement
                                          # end for body
          movl      -4(%ebp), %eax        # load local variable value
          incl      -4(%ebp)              # increment/decrement variable
          movl      -4(%ebp), %eax        # pass result
          jmp       .L4                   # return to FOR begin
.L5:                                      # 
          movl      $0, %eax              # integer literal
          pushl     %eax                  # save assigning value
          movl      -4(%ebp), %eax        # load local variable value
          popl      -4(%ebp)              # pop value into variable
          movl      -4(%ebp), %eax        # pass result
.L6:                                      # 
                                          # relational expression
          movl      -4(%ebp), %eax        # load local variable value
          pushl     %eax                  # stash left operand
          movl      $10, %eax             # integer literal
          popl      %ebx                  # restore left operand
          cmpl      %eax, %ebx            # comparision
          setl      %al                   # relation
          movzbl    %al,%eax              # return result
          cmpl      $0, %eax              # test condition
          je        .L7                   # 
                                          # {-> Begin coumpound statement
          movl      -4(%ebp), %eax        # load local variable value
          movl      %eax, %ebx            # store index value in EBX
          movl      %ebp, %eax            # 
          subl      $44, %eax             # 
          leal      (%eax,%ebx,4), %ebx   # compute address
          movl      (%ebx), %eax          # load value into EAX
          pushl     %eax                  # push function argument onto stack
          call      output                # invoke function
          addl      $4, %esp              # remove arguments from stack
          addl      $0, %esp              # deallocate local variables
                                          # }<- End coumpound statement
                                          # end for body
          movl      -4(%ebp), %eax        # load local variable value
          incl      -4(%ebp)              # increment/decrement variable
          movl      -4(%ebp), %eax        # pass result
          jmp       .L6                   # return to FOR begin
.L7:                                      # 
          addl      $44, %esp             # deallocate local variables
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
