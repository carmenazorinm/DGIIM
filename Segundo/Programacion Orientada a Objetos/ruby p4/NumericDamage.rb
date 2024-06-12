require_relative 'Damage'
require_relative'NumericDamageToUI'

module Deepspace
    class NumericDamage < Damage
        def initialize(w,s)
            super(s)
            @nWeapons=w
        end

        def getUIversion
            NumericDamageToUI.new(self)
        end

        def copy
            copia=NumericDamage.new(@nWeapons,@nShields)
            copia
        end

        def nWeapons
            @nWeapons
        end

        def hasNoEffect
            return (@nWeapons + @nShields) == 0
        end

        def discardWeapon(w)
            if(@nWeapons > 0)
                @nWeapons -= 1
            end
        end

        def adjust(w,s)
            super
            if(w.length < @nWeapons) 
                weap=w.length
            end
            return NumericDamage.new(weap,shields)
        end
    end
end