/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package deepspace;

/**
 *
 * @author carmenc
 */
public class PowerEfficientSpaceStation extends SpaceStation{
    private static final float EFFICIENCYFACTOR=1.10f;
    
    public PowerEfficientSpaceStation(SpaceStation station){
        super(station);
    }
    
    @Override
    public float fire(){
        return super.fire()*EFFICIENCYFACTOR;
    }
    
    @Override
    public float protection(){
        return super.protection()*EFFICIENCYFACTOR;
    }
    
    @Override
    public Transformation setLoot(Loot loot){
        return Transformation.NOTRANSFORM;
    }
    
    @Override
    public SpaceStationToUI getUIversion(){
        return new PowerEfficientSpaceStationToUI(this);
    }
}
