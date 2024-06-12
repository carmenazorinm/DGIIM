require_relative'SpaceStation'
require_relative'Transformation'

module Deepspace
    class PowerEfficientSpaceStation < SpaceStation
        EFFICIENCYFACTOR=1.10
        def fire
            return super*EFFICIENCYFACTOR
        end

        def protection
            return super*EFFICIENCYFACTOR
        end

        def setLoot(loot)
            super
            return Transformation::NOTRANSFORM
        end
    end
end