/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package deepspace;
import java.util.ArrayList;

/**
 *
 * @author mariacribi
 */
public class Hangar {
    private int maxElements;
    private  ArrayList<Weapon> weapons;
    private  ArrayList<ShieldBooster> shieldBoosters;
    
    //Constructor con visibilidad de paquete
    Hangar (int capacity){
        weapons= new ArrayList <> (); 
        shieldBoosters=new ArrayList<>();
        maxElements=capacity;
    }
    
    //Constructor de copia
    Hangar (Hangar h){
        maxElements=h.maxElements;
        shieldBoosters=h.shieldBoosters;
        weapons=h.weapons;
    }
    
    public HangarToUI getUIversion(){
        return new HangarToUI(this);
    }
    
    private boolean spaceAvailable(){
       return ((weapons.size()+shieldBoosters.size()) <maxElements);//queda espacio 
    }
    
    public boolean addWeapon (Weapon w){
        if (spaceAvailable()){//Si queda espacio
            return weapons.add(w);
        }else
            return false;
    }
    
    public boolean addShieldBooster (ShieldBooster s){
        if (spaceAvailable()){//Si queda espacio
            return shieldBoosters.add(s);
        }else
            return false;
    }
    
    public int getMaxElements(){
        return maxElements;
    }
    
    public ArrayList<ShieldBooster> getShieldBoosters (){
        return shieldBoosters;
    }
    
    public ArrayList<Weapon> getWeapons(){
        return weapons;
    }
    
    public ShieldBooster removeShieldBooster (int s){
        if (s>=0 && s<shieldBoosters.size()){
            return shieldBoosters.remove(s);
        }else
            return null;
    }
    
    public Weapon removeWeapon (int w){
        if (w>=0 && w<weapons.size()){
            return weapons.remove(w);
        }else
            return null;
    }
}
