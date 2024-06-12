module Deepspace
    class Damage
        
        def initialize(w, s, wl)
            @nShields = s
            @nWeapons = w
            @weapons = wl
        end

        def getUIversion
            DamageToUI.new(this)
        end

        def self.newSpecificWeapons(wl,s)
            new(-1,s,wl)
        end

        def self.newNumericWeapons(w,s)
            new(w,s,nil)
        end

        def self.newCopy(copy)
            new(copy.nWeapons,copy.nShields,copy.weapons)
        end

        def getWeapons
            @weapons
        end

        def getNWeapons
            @nWeapons
        end

        def getNShields
            @nShields
        end

        def hasNoEffect
            if(@nShields==0){
                if(@nWeapons==0 || @nWeapons==-1)
                    if(@weapons==nil || @weapons.size==0)
                        return true
            }
            else return false
            end
        end

        def discardShieldBooster
            if(@nShields>1)
                @nShields=@nShields-1
            else
                @nShields=0
            end
        end

        def discardWeapon(w)
            if(@nWeapons>-1)
                if(@nWeapons>1)
                    @nWeapons=@nWeapons-1
                else
                    @nWeapons=0
                end
            else
                if(@weapons.length != 0)
                    position=@weapons.index(w.type)
                    if(position!=nil) @weapons.delete_at(position)
                    end
                end
            end
        end

        def arrayContainsType(w,t)
            contador=0
            encontrado=false
            while(contador<w.length && !encontrado)
                if(w[contador].type==t)
                    encontrado=true
                end
            end
            encontrado
        end

        def adjust(w,s)
            damage = newCopy(this)
            if(s.length<@nShields) damage.nShields=s
            end

            if(damage.nWeapons != -1)
                if(w<@nWeapons) damage.nWeapons=w
                end
            else
                if(@weapons.length>w.length) 
                    contador=0
                    sigue=true
                    #que quite los tipos de arma que no tiene
                    while(contador<@weapons.length)
                        #si w no contiene un tipo de arma en el damage, que se quite
                        #va pasando por todos los tipos de armas de weapons y comparandolos con los que tiene w
                        if(!arrayContainsType(w,@weapons[contador]))
                            #si w no tiene ese tipo de arma, que se lo quite al daño
                            damage.discardWeapon(@weapons[contador])
                            end
                        end
                        contador++
                    end

                    #si aun asi, el daño tiene mas armas que el propio hangar, que se quiten al daño
                    if(@weapons.length>w.length)
                        contador=@weapons.length-w.length
                        while(contador>0)
                            @weapons.pop
                            contador--
                        end
                    end
                end
            end
        end
        
    end
end
