class Padre
    @instanciaDeClase = 1
    @duda = 2
    @@deClase = 11
    @@duda = 22

    def initialize 
        @deInstancia = 333
        @duda = 444
    end

    def self.salida
        puts @instanciaDeClase+1 #imprime 2
        puts @duda+1 unless @duda.nil? #imprime 3
        puts @@deClase+1 #imprime 12
        puts @@duda+1 #imprime 23
        puts "\n"
        #puts @deInstancia+1 #error pq estamos en ambito de clase
    end

    def salida
        puts @deInstancia+1 #334
        puts @duda+1 #445
        puts @@deClase+1 #12
        puts @@duda+1 #23
        puts "\n"
        #puts @instanciaDeClase+1 #error pq no estamos en el ambito
    end
end

#Padre.salida
#Padre.new.salida

class Hija < Padre
    @instanciaDeClase = -1 #no existe @duda como instancia de clase en Hija
    @@deClase = -11 #esto ahora tbn se modifica para el padre

    def modifica
        @duda += 111
        @@deClase = 0 #tmbn se cambia en Padre
    end
end

Padre.salida
Hija.salida

p=Padre.new
p.salida
h=Hija.new
h.salida

h.modifica
h.salida
p.salida
#p.modifica -> error pq no tiene ese metodo



