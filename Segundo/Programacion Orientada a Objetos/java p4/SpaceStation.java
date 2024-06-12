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
public class SpaceStation {
    private final int MAXFUEL = 100;
    private final float SHIELDLOSSPERUNITSHOT = 0.1f;
    private float ammoPower;
    private float fuelUnits;
    private String name;
    private int nMedals;
    private float shieldPower;
    private Damage pendingDamage; //Atributo de referencia
    private ArrayList<Weapon> weapons; //Atributo de referencia
    private ArrayList<ShieldBooster> shieldBoosters; //Atributo de referencia
    private Hangar hangar; //Atributo de referencia
    
    private void assignFuelValue (float f){
        if (f<MAXFUEL){
            fuelUnits=f;
        }else
            fuelUnits=MAXFUEL;
    }
    
    private void cleanPendingDamage (){
       if (pendingDamage!=null){
            if (pendingDamage.hasNoEffect()) {
               pendingDamage=null;
           }
       }
    }
    
    //Constructor con visibilidad de paquete
    SpaceStation (String n, SuppliesPackage supplies){
        name=n;
        ammoPower=0.0f;
        fuelUnits= 0.0f;
        shieldPower= 0.0f;
        pendingDamage=null;
        weapons=new ArrayList<> ();
        shieldBoosters=new ArrayList <> ();
        hangar=null;
        nMedals=0; 
        receiveSupplies(supplies);
        
    }
    
    public void cleanUpMountedItems(){   
        /*Iterator <Weapon> it1=weapons.iterator();
        while(it1.hasNext()){
            if (it1.next().getUses()==0)
                it1.remove();
        }
        
        Iterator <ShieldBooster> it2=shieldBoosters.iterator();
        while (it2.hasNext()){
            if (it2.next().getUses()==0)
                shieldBoosters.remove(it2.next());
        }*/
        for(int i = 0; i < weapons.size(); i++)
            if(weapons.get(i).getUses() == 0) weapons.remove(i);
        
        for (int i = 0; i < shieldBoosters.size(); i++)
            if(shieldBoosters.get(i).getUses() == 0) shieldBoosters.remove(i);
    }
    
    public void discardHangar(){
        hangar=null;
    }
    
    public void discardShieldBooster(int i){
        int size=shieldBoosters.size();
        if (i>=0 && i<size){
            ShieldBooster s=new ShieldBooster (shieldBoosters.remove(i));
           
            if(pendingDamage!=null){
                pendingDamage.discardShieldBooster();
                cleanPendingDamage();
            }
        }
    }
    
    public void discardShieldBoosterInHangar(int i){
        if (hangar!=null){
            hangar.removeShieldBooster(i);
        }
    }
    
    public void discardWeapon(int i){
        if(weapons!=null){
            int size=weapons.size();
            if (i>=0 && i<size){
                Weapon w=new Weapon(weapons.remove(i));

                if(pendingDamage!=null){
                    pendingDamage.discardWeapon(w);
                    cleanPendingDamage();
                }
            }
        }
    }
    
    public void discardWeaponInHangar(int i){
        if (hangar!=null){
            hangar.removeWeapon(i);
        }
    }
    
    public float fire(){
       //int size= weapons.size();
       float factor=1;
        for (Weapon w : weapons) {
            factor*=w.useIt();
        }
        factor*=ammoPower;
       return factor;  
    }
    
    public float getAmmoPower(){
        return ammoPower;
    }
    
    public float getFuelUnits(){
        return fuelUnits;
    }
    
    public Hangar getHangar(){
        return hangar;
    }
    
    public String getName(){
        return name;
    }
    
    public int getNMedals(){
        return nMedals;
    }
    
    public Damage getPendingDamage(){
        return pendingDamage;
    }
    
    public ArrayList<ShieldBooster> getShieldBoosters(){
        return shieldBoosters;
    }
    
    public float getShieldPower(){
        return shieldPower;
    }
    
    public float getSpeed(){
        float speed;
        if (MAXFUEL==0)
            speed=0;
        else
            speed=(fuelUnits/MAXFUEL);
        
        return speed;
    }
    
    public SpaceStationToUI getUIversion(){
        return new SpaceStationToUI(this);
    }
    
    public ArrayList<Weapon> getWeapons(){
        return weapons;
    }
    
    public void mountShieldBooster(int i){
        if (hangar!=null){
            if (i>=0 && i<hangar.getShieldBoosters().size()){
                ShieldBooster new_s=hangar.removeShieldBooster(i);
                if(new_s!=null)
                    shieldBoosters.add(new_s);
            }
        }
    }
    
    public void mountWeapon(int i){
        if (hangar!=null){
            if (i>=0 && i<hangar.getWeapons().size()){
                Weapon new_w=hangar.removeWeapon(i);
                if (new_w !=null)
                    weapons.add(new_w);
            }
        }
    }
    
    public void move(){
        if (fuelUnits>0)
           fuelUnits-=fuelUnits*getSpeed();
        else
            fuelUnits=0;
    }
    
    public float protection(){
        float factor=1;
        for (ShieldBooster s : shieldBoosters) {
            factor*=s.useIt();
        }
        factor*=shieldPower;
       return factor; 
    }
    
    public void receiveHangar(Hangar h){
        if (hangar==null)
            hangar=h;
        // Si ya tiene hangar no hace nada el metodo
    }
    
    public boolean receiveShieldBooster(ShieldBooster s){
        if (hangar!=null){
            return hangar.addShieldBooster(s);
        }else
            return false;
    }
    
    public ShotResult receiveShot (float shot){
        float myProtection=protection();
        ShotResult result=ShotResult.RESIST;
        if (myProtection>= shot){
            shieldPower-=SHIELDLOSSPERUNITSHOT*shot;
            if (shieldPower<0.0){
                shieldPower=0.0f; 
            }
        }
        
        else{
            shieldPower=0.0f;
            result=ShotResult.DONOTRESIST;
        }
        return result;
        
    }
    
    public void receiveSupplies (SuppliesPackage s){
        ammoPower+=s.getAmmoPower();
        shieldPower+=s.getShieldPower();
        assignFuelValue(fuelUnits+s.getFuelUnits());
    }
    
    public boolean receiveWeapon(Weapon w){
        if (hangar!=null){
            return hangar.addWeapon(w);
        }else
            return false;
    }
    
    public void setLoot (Loot loot){
        CardDealer dealer= CardDealer.getInstance();
        int h=loot.getNHangars();
        
        if (h>0){
            hangar=dealer.nextHangar();
            receiveHangar(hangar);
        }
        
        int elements=loot.getNSupplies();
        
        for (int i=0; i<elements; i++){
            SuppliesPackage sup = dealer.nextSuppliesPackage();
            receiveSupplies(sup);
        }
        elements=loot.getNWeapons();
        
        for (int i=0; i<elements; i++){
            Weapon weap=dealer.nextWeapon();
            receiveWeapon(weap);
        }
        elements=loot.getNShields();
        
        for (int i=0; i<elements; i++){
            ShieldBooster sh=dealer.nextShieldBooster();
            receiveShieldBooster (sh);
        }
        
        int medals=loot.getNMedals();
        nMedals+=medals; 
    }
    
    public void setPendingDamage (Damage d){
        if (d!=null)
            pendingDamage=d.adjust(weapons, shieldBoosters);
    }
    
    public boolean validState (){
       if (pendingDamage == null)
            return true;
        else
            return pendingDamage.hasNoEffect();
    }
       
}
