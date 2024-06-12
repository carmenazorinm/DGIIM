module Deepspace
    class Dice
        def initialize
            @NHANGARSPROB=0.25
            @NSHIELDSPROB=0.25
            @NWEAPONSPROB=0.33
            @FIRSTSHOTPROB=0.5
            @EXTRAEFFICIENCYPROB=0.8
        end

        def extraEfficiency
            nrandom=rand
            if(nrandom<@EXTRAEFFICIENCYPROB)
                return true
            else
                return false
            end
        end

        def initWithNHangars
            nrandom=rand
            if(nrandom<@NHANGARSPROB)
                return(0)
            else
                return(1)
            end
        end

        def initWithNWeapons
            nrandom=rand
            if(nrandom<(2*@NWEAPONSPROB))
                if(nrandom<@NWEAPONSPROB)
                    return 1
                else
                    return 2
                end
            else
                return 3
            end
        end

        def initWithNShields
            nrandom=rand
            if(nrandom<@NSHIELDSPROB)
                return 0
            else
                return 1
            end
        end

        def whoStarts(nPlayers)
            rand(nPlayers)
        end

        def firstShot
            nrandom=rand
            if(nrandom<@FIRSTSHOTPROB)
                return GameCharacter::SPACESTATION
            else
                return GameCharacter::ENEMYSTARSHIP
            end
        end

        def spaceStationMoves(speed)
            nrandom=rand
            if(nrandom<speed)
                return true
            else
                return false
            end
        end

        def to_s
            mensaje = "Dice"
            return mensaje
        end
    end
end
