module Deepspace
    class Hangar

        def initialize(capacity)
            @maxElements = capacity
            @weapons = []
            @shieldBoosters = []
        end

        def self.newCopy(copy)
            copia = new(copy.maxElements)

            copia.shieldBoosters.each do |sb|
                copia.addShieldBooster(sb)
            end

            copia.weapons.each do |w|
                copia.addWeapon(w)
            end

            return copia
        end

        def getUIversion
            HangarToUI.new(this)
        end
    end
end