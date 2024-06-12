.data
msg: 	.string "Hola, mundo!\n"
tam: 	.quad	.-msg

.text
	.global _start

write:	mov $1, %rax 
			mov $1, %rdi
			mov $msg, %rsi
			mov tam, %rdx
			syscall
			ret

exit: 	mov $60, %rax
			xor %rdi, %rdi
			syscall
			ret

_start: 	call write
			call exit
