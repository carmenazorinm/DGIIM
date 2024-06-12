/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package deepspace;
import java.util.ArrayList;
import java.util.Iterator;

/**
 *
 * @author carmenc
 */
public class SpecificDamage extends Damage{
    private ArrayList <WeaponType> weapons;
    
    public SpecificDamage(ArrayList <WeaponType> w, int shields){
        super(shields);
        weapons = w;
    }
    
    private int arrayContainsType(ArrayList<Weapon> w, WeaponType t){
        Iterator<Weapon> it = w.iterator();
        int resultado=-1;
        int i=0;
        boolean encontrado=false;
        while (it.hasNext() && !encontrado){
            if (it.next().getType()==t){
                encontrado=true;
                resultado=i;
            }
            i++;
        }
        if(encontrado) return resultado; 
        else return -1;
    }
    
    @Override
    public Damage adjust(ArrayList<Weapon> w, ArrayList<ShieldBooster> s){
        int shields = Integer.min(s.size(), nShields);
        ArrayList<Weapon> wAux = new ArrayList<>(w);
       ArrayList<WeaponType> toSet = new ArrayList<>();
       
       for(WeaponType element: weapons) {
           int index = arrayContainsType(wAux, element);
          
          if(index != -1){  //If the element is found
              toSet.add(element); //It can be removed
              wAux.remove(index);
          }
       }
               
        return new SpecificDamage(toSet, shields);
    }
    
    @Override
    public void discardWeapon(Weapon w){
        if (!weapons.isEmpty()){
                weapons.remove(w.getType());
            }
    }
    
    @Override
    public boolean hasNoEffect(){
        return weapons.size() + nShields==0;
    }
    
    
    public ArrayList<WeaponType> getWeapons(){
       return weapons; 
    }
    
    @Override
    public DamageToUI getUIversion(){
        return new SpecificDamageToUI(this);
    }
}
