/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package deepspace;

/**
 *
 * @author carmenc
 */
public class BetaPowerEfficientSpaceStation extends PowerEfficientSpaceStation{
    private static float EXTRAEFFICIENCY=1.2f;
    private Dice dice;
    
    public BetaPowerEfficientSpaceStation(SpaceStation station){
        super(station);
        dice=new Dice();
    }
    
    @Override
    public float fire(){
        if(dice.extraEfficiency()) return super.fire()*EXTRAEFFICIENCY;
        else{
            return super.fire();
        }
    }
    
    @Override
    public SpaceStationToUI getUIversion(){
        return new BetaPowerEfficientSpaceStationToUI(this);
    }
}
