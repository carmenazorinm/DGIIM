/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package deepspace;
import java.util.ArrayList;

/**
 *
 * @author carmenc
 */
public class SpaceCity extends SpaceStation{
    ArrayList<SpaceStation> collaborators = new ArrayList<>();
    
    public SpaceCity(SpaceStation base, ArrayList<SpaceStation> rest){
        super(base);
        collaborators=(ArrayList<SpaceStation>) rest.clone();
    }
    
    @Override
    public float fire(){
        float p=super.fire();
        for(int i = 0; i < collaborators.size(); i++){
            p+=collaborators.get(i).fire();
        }
        return p;
    }
    
    public ArrayList<SpaceStation> getCollaborators(){
        return collaborators;
    }
    
    @Override
    public SpaceStationToUI getUIversion(){
        return new SpaceCityToUI(this);
    }
    
    @Override
    public Transformation setLoot(Loot loot){
        return Transformation.NOTRANSFORM;
    }
    
    @Override
    public float protection(){
        float p=super.protection();
        for(int i = 0; i < collaborators.size(); i++){
            p+=collaborators.get(i).protection();
        }
        return p;
    }
    
//    @Override
//    public ShotResult receiveShot(float shot){
//        
//    }
}
