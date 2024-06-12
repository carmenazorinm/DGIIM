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
public abstract class Damage {
    int nShields;
    //private  int nWeapons; 
    //private ArrayList <WeaponType> weapons;
    
    //Constructor con visibilidad de paquete
    Damage (int s){
        //nWeapons=w; 
        nShields=s;
        //weapons=null;
    }
    
    //Constructor de copia
    Damage (Damage d){
        nShields=d.nShields;
    }
    
    public abstract DamageToUI getUIversion();
    
    public abstract Damage adjust (ArrayList<Weapon> w, ArrayList<ShieldBooster> s);
     
    public abstract void discardWeapon(Weapon w);
    
    public void discardShieldBooster(){
        if (nShields>0){
            nShields--;
        }
    }
    
    public abstract boolean hasNoEffect();
    
    public int getNShields(){
        return nShields; 
    }
}
