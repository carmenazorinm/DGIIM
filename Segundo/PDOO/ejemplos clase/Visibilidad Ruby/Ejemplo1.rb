class Padre
    private
    def privado
        puts "Estoy en privado \n"
    end

    protected
    def protegido
        puts "Estoy en protegido \n"
    end

    public 
    def publico
        puts "Estoy en publico \n"
    end

    def test(p)
        privado
        self.privado #a partir de 2.7
        #p.privado-> error pq no es la propia instancia!!
        protegido
        self.protegido
        p.protegido
    end
end

p = Padre.new
#p.privado
#p.protegido-> no esta llamando desde la misma clase o subclase
p.publico

class Hija < Padre
    def test(p)
        privado
        self.privado
        #p.privado-> no se puede cualquiercosa.privado
        protegido 
        self.protegido
        p.protegido #porque el código es Padre o hija (es hija)
        publico
        self.publico
        p.publico
    end
end

h=Hija.new
#h.privado-> pq no se puede cualquiercosa.privado
#h.protegido-> pq no estamos en clase o subclase
h.publico
h.test(p)




