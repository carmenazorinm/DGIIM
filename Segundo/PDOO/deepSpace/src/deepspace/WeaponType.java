/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Enum.java to edit this template
 */
package deepspace;

/**
 * @brief 
 * @author mariacribi
 */
public enum WeaponType {
    //Los tres valores posibles asociado con su power
    LASER (2.0f),
    MISSILE (3.0f),
    PLASMA (4.0f); 
    
    private final float power; //Atributo de instancia privado
    WeaponType (float p){ //Constructor público
      power=p;  
    } 
    
    public float getPower() {   //Consultor con visibilidad de paquete
      return power; 
    }
    
}