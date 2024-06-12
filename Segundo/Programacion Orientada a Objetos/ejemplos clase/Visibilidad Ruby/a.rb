class Padre
    @a=11
    @@a=22
    @edad=10

    public
    def self.metodo_publico
        #puts "Estoy en metodo publico clase Padre\n"
        puts @edad
    end
end

class Hija < Padre
    

    public
    def self.test(p)
        Padre.metodo_publico
        metodo_publico
    end
end

h=Hija.new
#h.test(Padre.new)
Hija.test(Padre.new)