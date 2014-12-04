################################################################################
                                          # C- Compiled to IA-32 Code
                                          # 
                                          # Compiler v. 0.1.0
################################################################################
                                          # array
                                          # Addition!
                                          # less than
                                          # less than
                                          # Addition!
                                          # array
                                          # less than
                                          # Subtraction
                                          # Addition!
                                          # less than
                                          # function ()
                                          # Addition!
                                          # less than
                                          # Addition!
################################################################################
                                          # Input Routine
.globl input
               .type      input, @function# 
                                    input:# 
               enter                $0, $0# 
                subl              $4, %esp# create slot for result
               pushl                  %esp# push slot's address
               pushl               $.inStr# push conversion spec
                call                 scanf# read an integer
                movl         8(%esp), %eax# move int to %eax
               leave                      # reset stack & frame pointers
                 ret                      # return to caller
