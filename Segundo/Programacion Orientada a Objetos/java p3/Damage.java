/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package deepspace;
import java.util.ArrayList;
import java.util.Iterator;

/**
 *
 * @author mariacribi
 */
public class Damage {
    private  int nShields;
    private  int nWeapons; 
    private ArrayList <WeaponType> weapons;
    
    //Constructor con visibilidad de paquete
    Damage (int w, int s){
        nWeapons=w; 
        nShields=s;
        weapons=null;
    }
    
    Damage (ArrayList<WeaponType> wl, int s){
        weapons=wl;
        nShields=s;
        nWeapons=-1;
    }
    
    //Constructor de copia
    Damage (Damage d){
        nWeapons=d.nWeapons; 
        nShields=d.nShields;
        weapons=d.weapons;
    }
    
    public DamageToUI getUIversion(){
        return new DamageToUI(this);
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
    
    public Damage adjust (ArrayList<Weapon> w, ArrayList<ShieldBooster> s){
      /*  
        Iterator<WeaponType> it_w = weapons.iterator();
        int i=0;
        //tenemos que quitar las armas y escudos protectores pasados como parámetros
        while (it_w.hasNext()){
            WeaponType w_next=it_w.next();
            if (arrayContainsType(w, w_next)>0){
                discardWeapon(w.get(i));
            }
            i++;
        }
        
        int result_shield=0;
        //Para el shieldBooster hay que coger el minimo de los dos
        if(s.size()<nShields)
            result_shield=s.size();
        else
            result_shield=nShields;
        
        return new Damage(weapons, result_shield);*/
        /*int shields=nShields;
        int weap=nWeapons;
        if(s.size()<nShields){ 
            shields=s.size();
        }

        if(nWeapons != -1){
            if(w.size() < nWeapons)
                weap=w.size();
            return new Damage (weap,shields);
        }else{
            ArrayList <Weapon> w_aux=w;
            ArrayList <WeaponType> weapons_aux=weapons;
            for(int i = 0; i < weapons.size();i++){
                int posicion = arrayContainsType(w_aux,weapons.get(i));
                if(posicion<0){
                    weapons_aux.remove(weapons.get(i));
                }else
                   w_aux.remove(posicion);
            }
            
            //si @weapons sigue teneiendo más armas que w, se van quitando las últimas armas de @weapons
            if(weapons_aux.size() > w.size()){ 
                int contador=weapons_aux.size() - w.size();
                while(contador > 0){
                    weapons_aux.remove(contador);
                    contador-=1;
                }
            }
            
            return new Damage(weapons_aux,shields);
        }*/
        int shields = Integer.min(s.size(), nShields);
        if(weapons == null){
            //Caso tenemos contadores
            return new Damage(Integer.min(nWeapons, w.size()), shields);
        }
        
       ArrayList<Weapon> wAux = new ArrayList<>(w);
       ArrayList<WeaponType> toSet = new ArrayList<>();
       
       for(WeaponType element: weapons) {
           int index = arrayContainsType(wAux, element);
          
          if(index != -1){  //If the element is found
              toSet.add(element); //It can be removed
              wAux.remove(index);
          }
       }
               
        return new Damage(toSet, shields);
    }
     
    public void discardWeapon(Weapon w){
        if (nWeapons==-1){
           if (!weapons.isEmpty()){
                weapons.remove(w.getType());
            } 
            
        }else{
           if (nWeapons>0)
                nWeapons--;
        }  
        
        /*if (weapons.isEmpty()){
            if (nWeapons>0)
                nWeapons--;
        } else
            weapons.remove(w.getType());*/
    }
    
    public void discardShieldBooster(){
        if (nShields>0){
            nShields--;
        }
    }
    
    public boolean hasNoEffect(){
        if (nWeapons==-1)
            return weapons.size() + nShields==0;
        else
            return nWeapons+nShields==0;
    }
    
    public int getNShields(){
        return nShields; 
    }
    
    public int getNWeapons(){
        return nWeapons; 
    }
    
    public ArrayList<WeaponType> getWeapons(){
       return weapons; 
    }
    
}
