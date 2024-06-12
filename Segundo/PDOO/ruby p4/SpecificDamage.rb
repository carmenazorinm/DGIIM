require_relative 'Damage'
require_relative'SpecificDamageToUI'

module Deepspace
    class SpecificDamage < Damage
        def initialize(wl,s)
            super(s)
            @weapons=wl
        end

        def copy
            copia=SpecificDamage.new(@weapons,@nShields)
            copia
        end

        def getUIversion
            SpecificDamageToUI.new(self)
        end

        def weapons
            @weapons
        end

        def hasNoEffect
            return (@weapons.length + @nShields)==0
        end

        def discardWeapon(w)
            if(@weapons.length > 0)
                indice = @weapons.index(w.type)
                if(indice >= 0)
                    @weapons.delete_at(indice)
                end
            end
        end

        def adjust(w,s)
            super
            contador=0
            weapons_aux=@weapons.clone
            w_aux=w.clone
            #en este while se quitan los weapons que están en @weapons pero no están en w
            while(contador < @weapons.length)
                posicion=arrayContainsType(w_aux,@weapons[contador])
                #puts posicion
                if(posicion < 0)
                    indice=weapons_aux.index(@weapons[contador])
                    #puts indice
                    if(indice>=0)
                        weapons_aux.delete_at(indice)
                    end
                else
                    w_aux.delete_at(posicion)
                end
                contador+=1
            end

            #si @weapons sigue teneiendo más armas que w, se van quitando las últimas armas de @weapons
            if(weapons_aux.length > w.length) 
                contador=weapons_aux.length - w.length
                while(contador > 0)
                    weapons_aux.delete_at(contador)
                    contador-=1
                end
            end
            damage = SpecificDamage.new(weapons_aux,shields)
        end
    end
end
