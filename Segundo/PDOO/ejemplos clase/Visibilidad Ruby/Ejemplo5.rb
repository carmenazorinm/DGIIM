class FalsaSeguridad
    attr_reader :lista #NO DEVUELVE UN NEW lista, devuelve el puntero

    def initialize
        @lista = [1,2,3,4]
    end

    def info
        puts @lista.size
    end
end

f=FalsaSeguridad.new
f.info

f.lista.clear #modifica lista aunq lista es privado!!
f.info 
