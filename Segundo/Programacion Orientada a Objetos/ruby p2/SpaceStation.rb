module Deepspace
    class SpaceStation

        @@MAXFUEL=100
        @@SHIELDLOSSPERUNITSHOT=0.1

        def initialize(n,supplies,han:nil,sb:nil,w:nil,dam:nil)
            @ammoPower=supplies.ammoPower
            @fuelUnits=supplies.fuelUnits
            @name=n
            @nMedals=0
            @shieldPower=supplies.shieldPower
            @pendingDamage=dam
            @weapons=w
            @shieldBoosters=sb
            @hangar=han
        end

        def getUIversion
            SpaceStationToUI.new(this)
        end

        def assignFuelValue(f)
            if((@fuelUnits + f)<@@MAXFUEL)
                @fuelUnits+=f
            else
                @fuelUnits=@@MAXFUEL
            end
        end

        def cleanPendingDamage
            if(@pendingDamage.hasNoEffect)
                @pendingDamage=nil
            end
        end

        def receiveWeapon(w)
            if(@hangar!=nil)
                return @hangar.addWeapon(w)
            else
                return false
            end
        end

        def receiveShieldBooster(s)
            if(@hangar!=nil)
                return @hangar.addShieldBooster(s)
            else
                return false
            end
        end

        def receiveHangar(h)
            if(@hangar==nil)
                @hangar=h
            end
        end

        def discardHangar
            @hangar=nil
        end

        def receiveSupplies(s)
            @ammoPower+=s.ammoPower
            @shieldPower+=s.shieldPower
            assignFuelValue(s.fuelUnits)
        end

        #terminar en java
        def setPendingDamage(d)
            damage=Damage.newCopy(d)
            damage=damage.adjust(@weapons,@shieldBoosters)
            @pendingDamage=damage
        end

        def mountWeapon(i)
            if(@hangar!=nil)
                arma=@hangar.removeWeapon(i)
                if(arma!=nil)
                    weapons << arma
                end
            end
        end

        def mountShieldBooster(i)
            if(@hangar!=nil)
                potenciador=@hangar.removeShieldBooster(i)
                if(potenciador!=nil)
                    shieldBoosters << potenciador
                end
            end
        end

        def discardWeaponInHangar(i)
            if(@hangar!=nil)
                @hangar.removeWeapon(i)
            end
        end

        def discardShieldBoosterInHangar(i)
            if(@hangar!=nil)
                @hangar.removeShieldBooster(i)
            end
        end

        def getSpeed
            speed=@fuelUnits/@@MAXFUEL
            speed
        end

        def move
            @fuelUnits=@fuelUnits-getSpeed
            if(@fuelUnits<0)
                @fuelUnits=0
            end
        end

        def validState
            return(@pendingDamage== nil || @pendingDamage.hasNoEffect)
        end

        def cleanUpMountedItems
            contador=0
            while(contador<weapons.length)
                if(weapons[contador].getUses==0)
                    weapons.delete_at(contador)
                end
            end

            contador=0
            while(contador<shieldBoosters.length)
                if(shieldBoosters[contador].getUses==0)
                    shieldBoosters.delete_at(contador)
                end
            end
        end

        def getAmmoPower
            @ammoPower
        end

        def fuelUnits
            @fuelUnits
        end

        def getHangar
            @hangar
        end

        def getName
            @name
        end

        def getNMedals
            @nMedals
        end

        def getPendingDamage
            @pendingDamage
        end

        def getShieldBoosters
            @shieldBoosters
        end

        def getShieldPower
            @shieldPower
        end

        def getWeapons
            @weapons
        end

    end
end
