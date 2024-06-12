/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package deepspace;

/**
 *
 * @author mariacribi
 */
public class SuppliesPackage {
    private float ammoPower;
    private float fuelUnits; 
    private float shieldPower;
    
    //Constructor con visibilidad de paquete
    public SuppliesPackage (float ammopower, float fuelunits, float shieldpower){
        ammoPower=ammopower;
        fuelUnits=fuelunits;
        shieldPower=shieldpower;
       
    }
    
    //Constructor de copia
    public SuppliesPackage (SuppliesPackage  s){
        ammoPower=s.ammoPower;
        fuelUnits=s.fuelUnits;
        shieldPower=s.shieldPower;
    }
    
    //Consultores por cada atributo:
    public float getAmmoPower(){
        return ammoPower;
    }
    
    public float getFuelUnits(){
        return fuelUnits;
    }
    
    public float getShieldPower(){
        return shieldPower;
    }
    
    @Override
    public String toString (){
        String s="SuppliesPackage: \n" +"AmmoPower: " + ammoPower +"\nfuelUnits: " + fuelUnits + "\nShieldPower: " + shieldPower;
        return s;
    }
    
}
