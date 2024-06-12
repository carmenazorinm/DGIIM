
/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package deepspace;

/**
 *
 * @author mariacribi
 */
public class EnemyStarShip {
    private  float ammoPower;
    private  String name; 
    private  float shieldPower; 
    private Loot loot;
    private Damage damage;
    
    //Constructor con visibilidad de paquete
    EnemyStarShip (String n, float a, float s, Loot l, Damage d){
        name=n;
        ammoPower=a;
        shieldPower=s;
        loot=l;
        damage=d;
    }
    
    //Constructor de copia
    EnemyStarShip (EnemyStarShip e){
        name=e.name;
        ammoPower=e.ammoPower;
        shieldPower=e.shieldPower;
        loot=e.loot;
        damage=e.damage;   
    }
    
    EnemyToUI getUIversion(){
        return new EnemyToUI(this);
    }
    
    public float fire(){
        return (getAmmoPower());  
    }
    
    public float getAmmoPower(){
        return ammoPower;   
    }
    
    public Damage getDamage() {
        return damage;
    }
    
    public Loot getLoot() {
        return loot;   
    }
    
    public String getName() {
        return name;  
    }
    
    public float getShieldPower() {
        return shieldPower;   
    }
    
    public float protection() {
       return (getShieldPower());  
    }
    
    public ShotResult receiveShot(float shot) {
        if (shieldPower<shot){
            return (ShotResult.DONOTRESIST);
        }else
            return (ShotResult.RESIST);
    }
}
