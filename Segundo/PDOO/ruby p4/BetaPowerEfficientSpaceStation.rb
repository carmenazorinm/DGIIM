require_relative'PowerEfficientSpaceStation'
require_relative'Dice'
module Deepspace
    class BetaPowerEfficientSpaceStation < PowerEfficientSpaceStation
        EXTRAEFFICIENCY=1.2
        def fire
            dice=Dice.new
            if(dice.extraEfficiency)
                super
            else #esta mal->arreglar
                normal=SpaceStation.new(this)
                normal.fire
            end
        end
    end
end