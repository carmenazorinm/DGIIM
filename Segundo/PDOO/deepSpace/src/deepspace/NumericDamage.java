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
public class NumericDamage extends Damage{
    private  int nWeapons; 
    
    public NumericDamage(int weapons, int shields){
        super(shields);
        nWeapons=weapons;
    }
    
    @Override
    public Damage adjust(ArrayList<Weapon> w, ArrayList<ShieldBooster> s){
        int shields = Integer.min(s.size(), nShields);
        return new NumericDamage(Integer.min(nWeapons, w.size()), shields);
    }
    
    @Override
    public void discardWeapon(Weapon w){
        if (nWeapons>0)
                nWeapons--;
    }
    
    @Override
    public boolean hasNoEffect(){
        return nWeapons+nShields==0;
    }
    
    
    public int getNWeapons(){
        return nWeapons; 
    }
    
    @Override
    public DamageToUI getUIversion(){
        return new NumericDamageToUI(this);
    }
}
