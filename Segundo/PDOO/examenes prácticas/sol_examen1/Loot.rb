require_relative'LootToUI'
require_relative 'Dice'
module Deepspace
    class Loot
        def initialize(nsu,nw,nsh,nh,nm)
            @nSupplies=nsu  
            @nWeapons=nw
            @nShields=nsh 
            @nHangars=nh
            @nMedals=nm 
            @dice=Dice.new
        end

        def nSupplies
            @nSupplies
        end 
        
        def reducirNSupplies
            num_elementos=@dice.reduccionNumElementos
            if(@nSupplies >= num_elementos)
            	return (@nSupplies - num_elementos)
            else
            	return 0
            end
        end
        
        def reducirNWeapons
            num_elementos=@dice.reduccionNumElementos
            if(@nWeapons >= num_elementos)
            	return (@nWeapons - num_elementos)
            else
            	return 0
            end
        end
        
        def reducirNShields
            num_elementos=@dice.reduccionNumElementos
            if(@nShields >= num_elementos)
            	return (@nShields - num_elementos)
            else
            	return 0
            end
        end
        
        def reducirNHangars
            num_elementos=@dice.reduccionNumElementos
            if(@nHangars >= num_elementos)
            	return (@nHangars - num_elementos)
            else
            	return 0
            end
        end
        
        def reducirNMedals
            num_elementos=@dice.reduccionNumElementos
            if(@nMedals >= num_elementos)
            	return (@nMedals - num_elementos)
            else
            	return 0
            end
        end

        def nWeapons
            @nWeapons
        end

        def nShields
            @nShields
        end

        def nHangars
            @nHangars
        end

        def nMedals
            @nMedals
        end

        def getUIversion
            LootToUI.new(self)
        end

        def to_s
            mensaje = "Loot: \nSupplies = #{nSupplies} \nWeapons = #{nWeapons} \nShields = #{nShields} \nHangars = #{nHangars} \nMedals = #{nMedals}"
            return mensaje
        end
    end
end
