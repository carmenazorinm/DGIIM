class Padre
    protected
    def metodo
        puts "Estoy en protected\n"
    end

    public
    def test
        metodo
    end
end

class Hija < Padre
    protected 
    def metodo
        super 
        puts "caca"
    end

    public
    def test(p)
        metodo
        p.metodo
        p.test
    end
end

Hija.new.test(Padre.new)
        