/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package deepspace;


/**
 * @brief representa a los potenciadores de escudo que pueden tener las estaciones espaciales
 * @author mariacribi
 */
public class ShieldBooster implements CombatElement{
    private String name; 
    private float boost; 
    private int uses; 
    
    //Constructor con visibilidad de paquete
    public ShieldBooster (String un_name, float un_boost, int un_uses){
        name=un_name;
        boost=un_boost;
        uses=un_uses;
       
    }
    
    //Constructor de copia
    public ShieldBooster (ShieldBooster  s){
        name=s.name;
        boost=s.boost;
        uses=s.uses;
    }
    
     //Consultores   
    public float getBoost(){
        return boost;
    }
    
    public int getUses(){
        return uses;
    }
    
    public float useIt(){
        if (uses>0){
            uses--; 
            return boost; 
        }
        else 
            return 1.0f; 
    }
    
    @Override
    public String toString(){
        String s = "Shield booster: \nName = " + name + "\nBoost = "
        + boost + "\nUses = " + uses;
        
        return s;
    }

    public ShieldToUI getUIversion(){
        return new ShieldToUI(this);
    }
    
}
