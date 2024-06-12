require_relative'SpaceStation'
require_relative'Transformation'

module Deepspace
    class SpaceCity < SpaceStation
        def initialize(base,rest)
            #cambiar a super(blabla)
            @ammoPower=base.ammoPower
            @fuelUnits=base.fuelUnits
            @name=base.name
            @nMedals=base.nMedals
            @shieldPower=base.shieldPower
            @pendingDamage=base.pendingDamage
            @weapons=base.weapons
            @shieldBoosters=base.shieldBooster
            @hangar=base.hangar

            @collaborators=ArrayList.new
            count = rest.length
            while(count>0)
                @rest[count]=rest[count]
                count-=1
            end
        end

        def collaborators
            return @collaborators
        end

        def fire
            suma = super
            count = 0
            while(count < @rest.length)
                suma+=@rest[count].fire
                count+=1
            end
            return suma
        end

        def protection
            suma=super
            count = 0
            while(count < @rest.length)
                suma+=@rest[count].protection
                count+=1
            end
            return suma
        end

        def setLoot(loot)
            #not sure
            super
            return Transformation::NOTRANSFORM
        end
            
    end
end