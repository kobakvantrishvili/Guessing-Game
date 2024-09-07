.global _randomizeA
_randomizeA:

#SETUP
pushl %ebp
movl  %esp, %ebp

#BODY
movl 8(%ebp), %ecx #Get the address of seed and store it in %ecx
movl 12(%ebp), %edi #Get the number of iterations the function should do
movl (%ecx), %eax #move contents of %ecx 's to %eax
movl $0, %esi # i=0, initial value of iterations completed

.J1:
shrl $5, %eax #%eax >> 5
xorl (%ecx), %eax #(seed >> 0)^(seed >> 5)

movl (%ecx), %ebx #move contents of %ecx 's to %ebx
shrl $14, %ebx #(seed >> 14)
xorl %ebx, %eax #(seed >> 0) ^ (seed >> 5) ^ (seed >> 14)

movl (%ecx), %ebx
shrl $19, %ebx #(seed >> 19)
xorl %ebx, %eax #(seed >> 0) ^ (seed >> 5) ^ (seed >> 14) ^ (seed >> 19)

movl (%ecx), %ebx
shrl $23, %ebx #(seed >> 23)
xorl %ebx, %eax #(seed >> 0) ^ (seed >> 5) ^ (seed >> 14) ^ (seed >> 19) ^ (seed >> 23)

andl $1, %eax #we only need last bit so mask it with $1
shll $31,%eax #make bit the high order bit
shrl $1, (%ecx) #emptied a space to put a bit in
addl (%ecx), %eax #randomized result put into %eax
movl %eax, (%ecx) #change value of %ecx for future operation
addl $1, %esi #i++, increment by one
cmpl %esi, %edi # if all iterations (stored in %edi) is not yet completed re-enter the loop
jg .J1

movl 16(%ebp), %ebx #get the value of the limit
decl %ebx #limit - 1
shrl $31, %edx #all 0's in %edx
divl %ebx
incl %edx #1 + %eax % limit
movl %edx, %eax #we need random number between 1-limit (not including 100) that's why we return the result of 1 + %eax % 99

#FINISH
movl %ebp, %esp
pop %ebp
ret

