class Padre 
    private 
    def privado_instancia
        puts "Estoy en privado instancia \n"
    end

    def self.privado_clase
        puts "Estoy en privado clase \n"
    end

    private_class_method :privado_clase

    public 
    def publico_instancia
        puts "Estoy en publico instancia \n"
    end

    def self.publico_clase
        puts "Estoy en publico clase \n"
    end

    def test
        #self.class.algo == Padre.algo
        #self.class.privado_clase -> error pq es privado
        self.privado_instancia
        Padre.publico_clase
    end

    def self.test(p)
        privado_clase
        #privado_instancia -> pq no estamos en ambito instancia
        #p.privado_clase -> pq es privado y pq se llama desde instancia
        #p.privado_instancia -> error pq es privado
        p.publico_instancia
    end
end

p=Padre.new
p.test
Padre.test(Padre.new)