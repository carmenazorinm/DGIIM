class A 
    protected
    def protegidoA
        puts "Estoy en protegidoA \n"
    end
    
    public
    def llamarProtegidoA
        self.protegidoA
    end
end

class B < A 
    protected
    def protegidoB
        puts "Estoy en protegidoB \n"
    end

    public
    def llamarProtegidoB
        self.protegidoB
    end
end

a = A.new
#a.protegidoA -> no se puede llamar pq no estoy en el codigo de una clase ni subclase
b=B.new
#b.protegidoA ->lo mismo
#b.protegidoB -> lo mismo

#a.llamarProtegidoA ->funciona
#b.llamarProtegidoA -> funciona
#b.llamarProtegidoB -> funciona

class C < B 
    protected
    def protegidoC
        puts "Estoy en protegidoC \n"
    end

    public
    def test
        A.new.protegidoA
        B.new.protegidoA
        B.new.protegidoB
        C.new.protegidoA
        C.new.protegidoB
        C.new.protegidoC
        D.new.protegidoA #funciona pq el código esta en una clase hija de donde se ha definido protegidoA
        #D.new.protegidoD -> error pq C NO es subclase ni clase D
    end
end

class D < C 
    protected
    def protegidoD
        puts "Estoy en protegidoD \n"
    end
end

C.new.test
#C.new.protegidoC -> error pq no estamos en clase ni subclase
        
