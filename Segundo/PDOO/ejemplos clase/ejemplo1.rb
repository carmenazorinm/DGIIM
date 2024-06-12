class Padre
    def initialize
    end

    def metodo
        puts "Metodo padre"
    end
end


class Hija < Padre
    def initialize
        super 
        @b=555
    end

    def metodo #en herencia el error mas tipico es copiar código, pero no!!
        #pero solo hace falta redefinir un par de metodos, tener eso en cuenta!!
        #
        super
        puts "Metodo hija"
        puts @b+1
        @a=88888
        super
        privado
    end
end

p=Padre.new
p.metodo
puts "________"
h=Hija.new
h.metodo
