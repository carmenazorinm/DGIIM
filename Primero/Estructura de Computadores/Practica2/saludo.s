# saludo.s: Imprimir por pantalla
# Hola a todos!
# Hello, World!
# retorna: código retorno 0, programado en la penúltima línea
# comprobar desde línea de comandos bash con echo $?
# SECCIÓN DE DATOS (.data, variables globales inicializadas)
# datos hex, octal, binario, decimal, char, string:
# 0x, 0, 0b, díg<>0, ‘, ""
# ejs: 0x41, 0101, 0b01000001, 65, ‘A, "AAA"
.section .data # directivas comienzan por .
# no son instrucciones máquina, son indicaciones para as
# etiquetas recuerdan valor contador posiciones (bytes)
saludo:
	.ascii "Hola a todos!\nHello, World!\n" # \n salto de línea
longsaludo:
	.quad .-saludo # . = contador posic. Aritmética de etiquetas.
# SECCIÓN DE CÓDIGO (.text, instrucciones máquina)
.section .text # cambiamos de sección, ahora emitimos código
.global _start # muestra punto de entrada a ld (como main en C)

_start: # punto de entrada ASM (como main en C)
# Llamada al sistema WRITE, consultar "man 2 write"
# ssize_t write(int fd, const void *buf, size_t count);
	mov $1, %rax # write: servicio 1 kernel Linux
	mov $1,%rdi # fd: descriptor de fichero para stdout
	mov $saludo,%rsi # buf: dirección del texto a escribir
	mov longsaludo,%rdx # count: número de bytes a escribir
	syscall # llamar write(stdout, &saludo, longsaludo);
# Llamada al sistema EXIT, consultar "man 2 exit"
# void _exit(int status);
	mov $60, %rax # exit: servicio 60 kernel Linux
	mov $0, %rdi # status: código a retornar (0=OK)
	syscall # llamar exit(0);
