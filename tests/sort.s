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
.globl minloc
          .type     minloc, @function     # "minloc" is type function
minloc:                                   # 
          enter     $0, $0                # save stack & frame ptrs
                                          # {-> Begin coumpound statement
          subl      $4, %esp              # allocate local variable i
          subl      $4, %esp              # allocate local variable x
          subl      $4, %esp              # allocate local variable k
          movl      12(%ebp), %eax        # load function parameter value
          pushl     %eax                  # save assigning value
          movl      -12(%ebp), %eax       # load variable value
          popl      -12(%ebp)             # pop value into variable
          movl      -12(%ebp), %eax       # pass result
          movl      12(%ebp), %eax        # load function parameter value
          movl      %eax, %ebx            # store index value in EBX
          movl      %ebp, %eax            # 
          addl      $8, %eax              # 
          movl      (%eax), %eax          # 
          leal      (%eax,%ebx,4), %ebx   # compute address
          movl      (%ebx), %eax          # load value into EAX
          pushl     %eax                  # save assigning value
          movl      -8(%ebp), %eax        # load variable value
          popl      -8(%ebp)              # pop value into variable
          movl      -8(%ebp), %eax        # pass result
          movl      $1, %eax              # integer literal
          pushl     %eax                  # push right operand to stack
          movl      12(%ebp), %eax        # load function parameter value
          popl      %ebx                  # pop right operand to EBX
          addl      %ebx, %eax            # evaluate additive expression
          pushl     %eax                  # save assigning value
          movl      -4(%ebp), %eax        # load variable value
          popl      -4(%ebp)              # pop value into variable
          movl      -4(%ebp), %eax        # pass result
.L0:                                      # 
                                          # relational expression
          movl      -4(%ebp), %eax        # load variable value
          pushl     %eax                  # stash left operand
          movl      16(%ebp), %eax        # load function parameter value
          popl      %ebx                  # restore left operand
          cmpl      %eax, %ebx            # comparision
          setl      %al                   # relation
          movzbl    %al,%eax              # return result
          cmpl      $0, %eax              # test condition
          je        .L1                   # 
                                          # {-> Begin coumpound statement
                                          # relational expression
          movl      -4(%ebp), %eax        # load variable value
          movl      %eax, %ebx            # store index value in EBX
          movl      %ebp, %eax            # 
          addl      $8, %eax              # 
          movl      (%eax), %eax          # 
          leal      (%eax,%ebx,4), %ebx   # compute address
          movl      (%ebx), %eax          # load value into EAX
          pushl     %eax                  # stash left operand
          movl      -8(%ebp), %eax        # load variable value
          popl      %ebx                  # restore left operand
          cmpl      %eax, %ebx            # comparision
          setl      %al                   # relation
          movzbl    %al,%eax              # return result
          cmpl      $0, %eax              # test condition
          je        .L2                   # 
                                          # {-> Begin coumpound statement
          movl      -4(%ebp), %eax        # load variable value
          movl      %eax, %ebx            # store index value in EBX
          movl      %ebp, %eax            # 
          addl      $8, %eax              # 
          movl      (%eax), %eax          # 
          leal      (%eax,%ebx,4), %ebx   # compute address
          movl      (%ebx), %eax          # load value into EAX
          pushl     %eax                  # save assigning value
          movl      -8(%ebp), %eax        # load variable value
          popl      -8(%ebp)              # pop value into variable
          movl      -8(%ebp), %eax        # pass result
          movl      -4(%ebp), %eax        # load variable value
          pushl     %eax                  # save assigning value
          movl      -12(%ebp), %eax       # load variable value
          popl      -12(%ebp)             # pop value into variable
          movl      -12(%ebp), %eax       # pass result
          addl      $0, %esp              # deallocate local variables
                                          # }<- End coumpound statement
.L2:                                      # 
          movl      $1, %eax              # integer literal
          pushl     %eax                  # push right operand to stack
          movl      -4(%ebp), %eax        # load variable value
          popl      %ebx                  # pop right operand to EBX
          addl      %ebx, %eax            # evaluate additive expression
          pushl     %eax                  # save assigning value
          movl      -4(%ebp), %eax        # load variable value
          popl      -4(%ebp)              # pop value into variable
          movl      -4(%ebp), %eax        # pass result
          addl      $0, %esp              # deallocate local variables
                                          # }<- End coumpound statement
          jmp       .L0                   # 
.L1:                                      # 
          movl      -12(%ebp), %eax       # load variable value
          addl      $12, %esp             # deallocate local variables
                                          # }<- End coumpound statement
          leave                           # 
          ret                             # 
################################################################################
.globl sort
          .type     sort, @function       # "sort" is type function
sort:                                     # 
          enter     $0, $0                # save stack & frame ptrs
                                          # {-> Begin coumpound statement
          subl      $4, %esp              # allocate local variable i
          subl      $4, %esp              # allocate local variable k
          movl      12(%ebp), %eax        # load function parameter value
          pushl     %eax                  # save assigning value
          movl      -4(%ebp), %eax        # load variable value
          popl      -4(%ebp)              # pop value into variable
          movl      -4(%ebp), %eax        # pass result
.L4:                                      # 
                                          # relational expression
          movl      -4(%ebp), %eax        # load variable value
          pushl     %eax                  # stash left operand
          movl      $1, %eax              # integer literal
          pushl     %eax                  # push right operand to stack
          movl      16(%ebp), %eax        # load function parameter value
          popl      %ebx                  # pop right operand to EBX
          subl      %ebx, %eax            # evaluate additive expression
          popl      %ebx                  # restore left operand
          cmpl      %eax, %ebx            # comparision
          setl      %al                   # relation
          movzbl    %al,%eax              # return result
          cmpl      $0, %eax              # test condition
          je        .L5                   # 
                                          # {-> Begin coumpound statement
          subl      $4, %esp              # allocate local variable t
          movl      16(%ebp), %eax        # load function parameter value
          pushl     %eax                  # push function argument onto stack
          movl      -4(%ebp), %eax        # load variable value
          pushl     %eax                  # push function argument onto stack
          movl      8(%ebp), %eax         # load function parameter value
          pushl     %eax                  # push function argument onto stack
          call      minloc                # invoke function
          addl      $12, %esp             # remove arguments from stack
          pushl     %eax                  # save assigning value
          movl      -8(%ebp), %eax        # load variable value
          popl      -8(%ebp)              # pop value into variable
          movl      -8(%ebp), %eax        # pass result
          movl      -8(%ebp), %eax        # load variable value
          movl      %eax, %ebx            # store index value in EBX
          movl      %ebp, %eax            # 
          addl      $8, %eax              # 
          movl      (%eax), %eax          # 
          leal      (%eax,%ebx,4), %ebx   # compute address
          movl      (%ebx), %eax          # load value into EAX
          pushl     %eax                  # save assigning value
          movl      -12(%ebp), %eax       # load variable value
          popl      -12(%ebp)             # pop value into variable
          movl      -12(%ebp), %eax       # pass result
          movl      -4(%ebp), %eax        # load variable value
          movl      %eax, %ebx            # store index value in EBX
          movl      %ebp, %eax            # 
          addl      $8, %eax              # 
          movl      (%eax), %eax          # 
          leal      (%eax,%ebx,4), %ebx   # compute address
          movl      (%ebx), %eax          # load value into EAX
          pushl     %eax                  # save assigning value
          movl      -8(%ebp), %eax        # load variable value
          movl      %eax, %ebx            # store index value in EBX
          movl      %ebp, %eax            # 
          addl      $8, %eax              # 
          movl      (%eax), %eax          # 
          leal      (%eax,%ebx,4), %ebx   # compute address
          movl      (%ebx), %eax          # load value into EAX
          popl      (%ebx)                # pop value into variable
          movl      (%ebx), %eax          # pass result
          movl      -12(%ebp), %eax       # load variable value
          pushl     %eax                  # save assigning value
          movl      -4(%ebp), %eax        # load variable value
          movl      %eax, %ebx            # store index value in EBX
          movl      %ebp, %eax            # 
          addl      $8, %eax              # 
          movl      (%eax), %eax          # 
          leal      (%eax,%ebx,4), %ebx   # compute address
          movl      (%ebx), %eax          # load value into EAX
          popl      (%ebx)                # pop value into variable
          movl      (%ebx), %eax          # pass result
          movl      $1, %eax              # integer literal
          pushl     %eax                  # push right operand to stack
          movl      -4(%ebp), %eax        # load variable value
          popl      %ebx                  # pop right operand to EBX
          addl      %ebx, %eax            # evaluate additive expression
          pushl     %eax                  # save assigning value
          movl      -4(%ebp), %eax        # load variable value
          popl      -4(%ebp)              # pop value into variable
          movl      -4(%ebp), %eax        # pass result
          addl      $4, %esp              # deallocate local variables
                                          # }<- End coumpound statement
          jmp       .L4                   # 
.L5:                                      # 
          addl      $8, %esp              # deallocate local variables
                                          # }<- End coumpound statement
          leave                           # 
          ret                             # 
################################################################################
.globl main
          .type     main, @function       # "main" is type function
main:                                     # 
          enter     $0, $0                # save stack & frame ptrs
                                          # {-> Begin coumpound statement
          subl      $4, %esp              # allocate local variable i
          movl      $0, %eax              # integer literal
          pushl     %eax                  # save assigning value
          movl      -4(%ebp), %eax        # load variable value
          popl      -4(%ebp)              # pop value into variable
          movl      -4(%ebp), %eax        # pass result
.L6:                                      # 
                                          # relational expression
          movl      -4(%ebp), %eax        # load variable value
          pushl     %eax                  # stash left operand
          movl      $10, %eax             # integer literal
          popl      %ebx                  # restore left operand
          cmpl      %eax, %ebx            # comparision
          setl      %al                   # relation
          movzbl    %al,%eax              # return result
          cmpl      $0, %eax              # test condition
          je        .L7                   # 
                                          # {-> Begin coumpound statement
          call      input                 # invoke function
          addl      $0, %esp              # remove arguments from stack
          pushl     %eax                  # save assigning value
          movl      -4(%ebp), %eax        # load variable value
          movl      %eax, %ebx            # store index value in EBX
          movl      x(,%ebx,4), %eax      # load value into EAX
          popl      x(,%ebx,4)            # pop value into variable
          movl      x(,%ebx,4), %eax      # pass result
          movl      $1, %eax              # integer literal
          pushl     %eax                  # push right operand to stack
          movl      -4(%ebp), %eax        # load variable value
          popl      %ebx                  # pop right operand to EBX
          addl      %ebx, %eax            # evaluate additive expression
          pushl     %eax                  # save assigning value
          movl      -4(%ebp), %eax        # load variable value
          popl      -4(%ebp)              # pop value into variable
          movl      -4(%ebp), %eax        # pass result
          addl      $0, %esp              # deallocate local variables
                                          # }<- End coumpound statement
          jmp       .L6                   # 
.L7:                                      # 
          movl      $10, %eax             # integer literal
          pushl     %eax                  # push function argument onto stack
          movl      $0, %eax              # integer literal
          pushl     %eax                  # push function argument onto stack
          movl      x, %eax               # load global value
          pushl     %eax                  # push function argument onto stack
          call      sort                  # invoke function
          addl      $12, %esp             # remove arguments from stack
          movl      $0, %eax              # integer literal
          pushl     %eax                  # save assigning value
          movl      -4(%ebp), %eax        # load variable value
          popl      -4(%ebp)              # pop value into variable
          movl      -4(%ebp), %eax        # pass result
.L8:                                      # 
                                          # relational expression
          movl      -4(%ebp), %eax        # load variable value
          pushl     %eax                  # stash left operand
          movl      $10, %eax             # integer literal
          popl      %ebx                  # restore left operand
          cmpl      %eax, %ebx            # comparision
          setl      %al                   # relation
          movzbl    %al,%eax              # return result
          cmpl      $0, %eax              # test condition
          je        .L9                   # 
                                          # {-> Begin coumpound statement
          movl      -4(%ebp), %eax        # load variable value
          movl      %eax, %ebx            # store index value in EBX
          movl      x(,%ebx,4), %eax      # load value into EAX
          pushl     %eax                  # push function argument onto stack
          call      output                # invoke function
          addl      $4, %esp              # remove arguments from stack
          movl      $1, %eax              # integer literal
          pushl     %eax                  # push right operand to stack
          movl      -4(%ebp), %eax        # load variable value
          popl      %ebx                  # pop right operand to EBX
          addl      %ebx, %eax            # evaluate additive expression
          pushl     %eax                  # save assigning value
          movl      -4(%ebp), %eax        # load variable value
          popl      -4(%ebp)              # pop value into variable
          movl      -4(%ebp), %eax        # pass result
          addl      $0, %esp              # deallocate local variables
                                          # }<- End coumpound statement
          jmp       .L8                   # 
.L9:                                      # 
          addl      $4, %esp              # deallocate local variables
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
