/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package deepspace;

/**
 * @brief representa a las armas de las que puede disponer una estación espacial para potenciar su
energía al disparar
 * @author mariacribi
 */
public class Weapon implements CombatElement{
    private String name;
    private WeaponType type;
    private int uses; 
    
      //Constructor con visibilidad de paquete
    Weapon (String un_name, WeaponType un_type, int un_uses){
        name=un_name;
        type=un_type;
        uses=un_uses;
       
    }
    
    //Constructor de copia
    public Weapon (Weapon  s){
        name=s.name;
        type=s.type;
        uses=s.uses;
    }
    
     //Consultores   
    public WeaponType getType(){
        return type;
    }
    
    public int getUses(){
        return uses;
    }
    
    public float power(){
        //Devuelve la potencia de disparo indicada por el tipo de arma
        return type.getPower();
    }
    
    public float useIt(){
        if (uses>0){
            uses--; 
            return (power()); 
        }
        else 
            return 1.0f; 
    }
    
    @Override
    public String toString(){
        String s = "Weapon: \nName = " + name + "\nWeapon Type = "
        + type + "\nUses = " + uses;
        
        return s;
    }
    
    public WeaponToUI getUIversion(){
         return new WeaponToUI(this);
    }

    
}
