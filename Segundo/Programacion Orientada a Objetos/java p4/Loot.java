/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package deepspace;

/**
 * @brief representa el botín que se obtiene al vencer a una nave enemiga
 * @author mariacribi
 */
public class Loot {
    private  int nSupplies;
    private  int nWeapons; 
    private  int nShields; 
    private  int nHangars;
    private  int nMedals; 
    
    Loot(){}
    //Constructor con visibilidad de paquete
    Loot (int supplies, int weapons, int shields, int hangars, int medals){
        nSupplies=supplies;
        nWeapons=weapons;
        nShields=shields;
        nHangars=hangars;       
        nMedals=medals;       
    }
    
    //Consultores por cada atributo:
    public int getNSupplies(){
        return nSupplies;
    }
    
    public int getNWeapons(){
        return nWeapons;
    }
    
    public int getNShields(){
        return nShields;
    }
    
    public int getNHangars(){
        return nHangars;
    }
    
    public int getNMedals(){
        return nMedals;
    }
    
    @Override
    public String toString (){
        return ("Loot: \n" +"NSupplies: " + nSupplies + "\nnWeapons: " + nWeapons + "\nnShields: "+ nShields + "\nnHangars: " + nHangars + "\nnMedals: " + nMedals);
    }
    
    LootToUI getUIversion(){
         return new LootToUI(this);
    }
}
