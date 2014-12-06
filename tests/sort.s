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
                                          # array
################################################################################
.globl minloc
          .type     minloc, @function     # "minloc" is type function
minloc:                                   # 
          enter     $0, $0                # save stack & frame ptrs
                                          # local var
                                          # local var
                                          # local var
                                          # local variable
          pushl     %eax                  # save assigning value
                                          # local variable
          popl      (%eax)                # pop value into variable
          movl      (%eax), %eax          # pass result
                                          # local variable
          pushl     %eax                  # save assigning value
                                          # local variable
          popl      (%eax)                # pop value into variable
          movl      (%eax), %eax          # pass result
                                          # local variable
          pushl     %eax                  # push left operand to stack
          movl      $1, %eax              # integer literal
          popl      %ebx                  # pop left operand to EBX
          addl      %ebx, %eax            # evaluate additive expression
          pushl     %eax                  # save assigning value
                                          # local variable
          popl      (%eax)                # pop value into variable
          movl      (%eax), %eax          # pass result
                                          # relational expression
                                          # local variable
          pushl     %eax                  # stash left operand
                                          # local variable
          popl      %ebx                  # restore left operand
          cmpl      %eax, %ebx            # comparision
          setl      %al                   # relation
          movzbl    %al,%eax              # return result
                                          # relational expression
                                          # local variable
          pushl     %eax                  # stash left operand
                                          # local variable
          popl      %ebx                  # restore left operand
          cmpl      %eax, %ebx            # comparision
          setl      %al                   # relation
          movzbl    %al,%eax              # return result
                                          # local variable
          pushl     %eax                  # save assigning value
                                          # local variable
          popl      (%eax)                # pop value into variable
          movl      (%eax), %eax          # pass result
                                          # local variable
          pushl     %eax                  # save assigning value
                                          # local variable
          popl      (%eax)                # pop value into variable
          movl      (%eax), %eax          # pass result
                                          # local variable
          pushl     %eax                  # push left operand to stack
          movl      $1, %eax              # integer literal
          popl      %ebx                  # pop left operand to EBX
          addl      %ebx, %eax            # evaluate additive expression
          pushl     %eax                  # save assigning value
                                          # local variable
          popl      (%eax)                # pop value into variable
          movl      (%eax), %eax          # pass result
                                          # local variable
          leave                           # 
          ret                             # 
                                          # array
################################################################################
.globl sort
          .type     sort, @function       # "sort" is type function
sort:                                     # 
          enter     $0, $0                # save stack & frame ptrs
                                          # local var
                                          # local var
                                          # local variable
          pushl     %eax                  # save assigning value
                                          # local variable
          popl      (%eax)                # pop value into variable
          movl      (%eax), %eax          # pass result
                                          # relational expression
                                          # local variable
          pushl     %eax                  # stash left operand
                                          # local variable
          pushl     %eax                  # push left operand to stack
          movl      $1, %eax              # integer literal
          popl      %ebx                  # pop left operand to EBX
          subl      %ebx, %eax            # evaluate additive expression
          popl      %ebx                  # restore left operand
          cmpl      %eax, %ebx            # comparision
          setl      %al                   # relation
          movzbl    %al,%eax              # return result
                                          # local var
                                          # local variable
          pushl     %eax                  # push function argument onto stack
                                          # local variable
          pushl     %eax                  # push function argument onto stack
                                          # local variable
          pushl     %eax                  # push function argument onto stack
          call      minloc                # invoke function
          pushl     %eax                  # save assigning value
                                          # local variable
          popl      (%eax)                # pop value into variable
          movl      (%eax), %eax          # pass result
                                          # local variable
          pushl     %eax                  # save assigning value
                                          # local variable
          popl      (%eax)                # pop value into variable
          movl      (%eax), %eax          # pass result
                                          # local variable
          pushl     %eax                  # save assigning value
                                          # local variable
          popl      (%eax)                # pop value into variable
          movl      (%eax), %eax          # pass result
                                          # local variable
          pushl     %eax                  # save assigning value
                                          # local variable
          popl      (%eax)                # pop value into variable
          movl      (%eax), %eax          # pass result
                                          # local variable
          pushl     %eax                  # push left operand to stack
          movl      $1, %eax              # integer literal
          popl      %ebx                  # pop left operand to EBX
          addl      %ebx, %eax            # evaluate additive expression
          pushl     %eax                  # save assigning value
                                          # local variable
          popl      (%eax)                # pop value into variable
          movl      (%eax), %eax          # pass result
          leave                           # 
          ret                             # 
################################################################################
.globl main
          .type     main, @function       # "main" is type function
main:                                     # 
          enter     $0, $0                # save stack & frame ptrs
                                          # local var
          movl      $0, %eax              # integer literal
          pushl     %eax                  # save assigning value
                                          # local variable
          popl      (%eax)                # pop value into variable
          movl      (%eax), %eax          # pass result
                                          # relational expression
                                          # local variable
          pushl     %eax                  # stash left operand
          movl      $10, %eax             # integer literal
          popl      %ebx                  # restore left operand
          cmpl      %eax, %ebx            # comparision
          setl      %al                   # relation
          movzbl    %al,%eax              # return result
          call      input                 # invoke function
          pushl     %eax                  # save assigning value
                                          # local variable
          popl      (%eax)                # pop value into variable
          movl      (%eax), %eax          # pass result
                                          # local variable
          pushl     %eax                  # push left operand to stack
          movl      $1, %eax              # integer literal
          popl      %ebx                  # pop left operand to EBX
          addl      %ebx, %eax            # evaluate additive expression
          pushl     %eax                  # save assigning value
                                          # local variable
          popl      (%eax)                # pop value into variable
          movl      (%eax), %eax          # pass result
          movl      $10, %eax             # integer literal
          pushl     %eax                  # push function argument onto stack
          movl      $0, %eax              # integer literal
          pushl     %eax                  # push function argument onto stack
          movl      (x), %eax             # load global variable reference
          pushl     %eax                  # push function argument onto stack
          call      sort                  # invoke function
          movl      $0, %eax              # integer literal
          pushl     %eax                  # save assigning value
                                          # local variable
          popl      (%eax)                # pop value into variable
          movl      (%eax), %eax          # pass result
                                          # relational expression
                                          # local variable
          pushl     %eax                  # stash left operand
          movl      $10, %eax             # integer literal
          popl      %ebx                  # restore left operand
          cmpl      %eax, %ebx            # comparision
          setl      %al                   # relation
          movzbl    %al,%eax              # return result
                                          # local variable
          pushl     %eax                  # push function argument onto stack
          call      output                # invoke function
                                          # local variable
          pushl     %eax                  # push left operand to stack
          movl      $1, %eax              # integer literal
          popl      %ebx                  # pop left operand to EBX
          addl      %ebx, %eax            # evaluate additive expression
          pushl     %eax                  # save assigning value
                                          # local variable
          popl      (%eax)                # pop value into variable
          movl      (%eax), %eax          # pass result
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
