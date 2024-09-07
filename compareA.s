.global _compareA
_compareA:

#SETUP
pushl %ebp
movl  %esp, %ebp

#BODY
movl 8(%ebp), %eax #Get the value of ranNum
movl 12(%ebp), %edx #Get the value of guess
movl 16(%ebp), %esi #Get the address numGuess
movl (%esi), %ecx #Get the value of numGuess

cmpl %eax, %edx #compare ranNum to the guess
jg Greater
cmpl %eax, %edx
jl Less

movl $0, %eax
jmp Done

Greater:
movl $2, %eax
jmp Done

Less:
movl $1, %eax
jmp Done

Done:
incl %ecx #increment the numGuess
movl %ecx, (%esi)

#FINISH
movl %ebp, %esp
pop %ebp
ret
