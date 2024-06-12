require_relative'DamageToUI'

module Deepspace
    class Damage
        
        def initialize(s)
            @nShields = s
        end

        def getUIversion
            DamageToUI.new(self)
        end

        def to_s
			getUIversion.to_s
		end

        def copy
        end

        def nShields
            @nShields
        end

        def hasNoEffect
        end

        def discardShieldBooster
            if(@nShields>0)
                @nShields=@nShields-1
            else
                @nShields=0
            end
        end

        def discardWeapon(w)
        end

        #array de weapons contiene tal weaponType
        def arrayContainsType(w,t)
            contador=0
            encontrado=false
            while((contador < w.length) && (!encontrado))
                if(w[contador].type==t)
                    encontrado=true
                end
                contador+=1
            end
            
            if(encontrado)
                return contador-1
            else
                return -1
            end
        end

        def adjust(w,s)
            shields=@nShields
            weap=@nWeapons
            if(s.length<@nShields) 
                shields=s.length
            end
        end
        
    end
end
