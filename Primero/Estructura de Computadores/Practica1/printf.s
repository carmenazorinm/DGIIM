.data
i:		.int 12345
f:		.string "i = %d\n"

.text
		.global _start

_start:	mov $f, %rdi
			mov i, %rsi
			xor %rax, %rax
			call printf
			
			xor %rdi, %rdi
			call exit
