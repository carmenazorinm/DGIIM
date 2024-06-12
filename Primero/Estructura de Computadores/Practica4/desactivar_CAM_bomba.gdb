# CONTRASEÑA: animoFiera
# PIN: 9876

# CONTRASEÑA MODIFICADA: hola
# PIN: 1234

file CAM_bomba

br *main+88
run < <(echo -e hola\\n1234\\n)


# Introducimos "hola" como contraseña

p(char*) $rax	
		 
# $rax = "hola\n" es el valor de la contraseña leída antes de entrar al bucle para 								  
# codificarse

# Vemos que se hace un bucle desde main+96 hasta main+116, si en main+113 ejecutamos p(char*) $rax cada vez  # que llegamos a dicha instrucción, observamos que se está codificando la contraseña introducida.

# Podríamos observar todas las ejecuciones del bucle así
# br *main+96 
# br *main+113
# cont
# cont
 
# p(char*) $rax 				# $rax = "ola\n"
# cont
# cont
# p(char*) $rax 				# $rax = "la\n"
# cont
# cont
# p(char*) $rax 				# $rax = "a\n"
# cont
# cont
# p(char*) $rax 				# $rax = "\n"
# cont
# cont
# p(char*) $rax 				# $rax = ""
# cont
#  cont
# p(char*) $rax 				# $rax = ""

# Observamos que desde main+136 hasta main+156 hay otro bucle
								
br *main+125           
# $rax = "animoFiera\n" es el valor de la contraseña leída antes de entrar al bucle 								
# para codificarse

cont
p(char*) $rax

# Podríamos observar todas las ejecuciones del bucle así

# br *main+136
# cont
# br *main+153
# p(char*) $eax 				# $rax = "nimoFiera"
# cont

# Vemos que en main+190 tenemos un test %eax,%eax que si nos da diferente salta hasta main+253 donde se 
# encuentra boom. Por tanto, tenemos que conseguir que %eax sea 0

br *main+190
cont
set $rax=0


# En la instrucción main+241 vemos que se hace una comparación antes de saltar a boom, de forma que si 
# $eax == 0x8(%rsp), entonces hacemos un salto hasta defused. Basta entonces con hacer un breakpoint en esta
# instrucción, observar cuál es el valor de %eax (para saber el pin original) y modificarlo al valor del 
# pin que nosotros hayamos incluido

br *main+247
cont

# introducimos como pon: 1234

p(int) $eax 				
# observamos que el pin original era 9876
set $eax=1234
cont
