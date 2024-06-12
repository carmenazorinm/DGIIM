

.section .data
	lista:		.int 0xffffffff, 0xffffffff
	longlista:	.int (.-lista)/4
	resultado:	.quad 0
	formato:		.string "suma = %llu = 0x%016llx\n"

.section .text
			.global _start
			
_start:			
			call trabajar
			call imprim_c
			call acabar_c
			ret

trabajar:
			mov $lista, %rdi
			mov longlista, %rsi
			xor %rdx, %rdx 		/* acarreo */
			xor %rax, %rax 		/* acumulador suma */
			xor %rcx, %rcx 		/* indice */
			call bucle
			mov %eax, resultado
			mov %edx, resultado+4
			ret

bucle:
			cmp %rcx, %rsi 		/* comparar el índice y la longitud */
			je .Lfin 	 				/* terminar si son iguales */
			addq (%rdi, %rcx, 4), %rax 	/* añadir el siguiente numero a suma */
			jnc .Lsin_acarreo 	/* si no hay acarreo */
			inc %rdx
			
.Lsin_acarreo:
			inc %rcx
			jmp bucle
			
.Lfin:
			ret

imprim_c:			# requiere libC
	mov   $formato, %rdi
	mov   resultado,%rsi
	mov   resultado,%rdx
	xor   %eax, %eax	
	call  printf		# == printf(formato, res, res);
	ret


acabar_c:			# requiere libC
	mov  resultado, %edi
	call _exit		# ==  exit(resultado)
	ret
			
