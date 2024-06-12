/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package deepspace;

/**
 * @brief 
 * @author mariacribi
 */
public class TestP1 {
    
    public static void main (String []args) {
        System.out.println("Probar que esta implementado correctamente:\n");
        
        //Println imprime con un salto de linea, mientras que print lo escribe todo en la misma linea
        //Creamos una instancia de Loot
        System.out.println("Valores de Loot(1,2,3,4,5): ");
        Loot l=new Loot(1,2,3,4,5);
        System.out.println("Supplies: " + l.getNSupplies());
        System.out.println("Weapons: " + l.getNWeapons());
        System.out.println("Shields: " + l.getNShields());
        System.out.println("Hangars: " + l.getNHangars());
        System.out.print("Medals: " + l.getNMedals()+ "\n");
        
        //Creamos una instancia de SupliesPackage
        System.out.println("Valores de SuppliesPackage(1,2,0): ");
        SuppliesPackage sp=new SuppliesPackage(1,2,0);
        System.out.println("Ammo Power: "+ sp.getAmmoPower());
        System.out.println("Fuel: " + sp.getFuelUnits());
        System.out.println("Shield Power: "+ sp.getShieldPower());
        SuppliesPackage copy_sp=new SuppliesPackage(sp);
        System.out.println("Ammo Power copia: "+ copy_sp.getAmmoPower());
        System.out.println("Fuel copia: " + copy_sp.getFuelUnits());
        System.out.println("Shield Power copia: "+ copy_sp.getShieldPower());
        
        
        //Creamos una instancia de ShieldBooster
        System.out.println("Valores de ShieldBooster(shboost,2.98,3): ");
        ShieldBooster sb=new ShieldBooster("shboost", 2.98f ,3);
        System.out.println("Boost: "+sb.getBoost());
        System.out.println("Uses: " + sb.getUses());
        ShieldBooster copy_sb=new ShieldBooster(sb);
        System.out.println("Boost copia: "+ copy_sb.getBoost());
        System.out.println("Uses copia: " + copy_sb.getUses());
        
        
        //Creamos una instancia de Weapon
        System.out.println("Valores de Weapon(weapon,laser,0): ");
        Weapon w=new Weapon("weapon laser", WeaponType.LASER ,0);
        System.out.println("Weapon type: "+w.getType());
        System.out.println("Uses: " + w.getUses());
        Weapon copy_w=new Weapon(w);
        System.out.println("Weapon type: "+copy_w.getType());
        System.out.println("Uses copia: " + copy_w.getUses());
        
        
        //Creamos una instancia de Dice
        System.out.println("Valores de Dice: ");
        Dice d=new Dice();
        System.out.println("Numero hangares recibidos aleatoriamente: "+d.initWithNHangars());
        System.out.println("Numero de armas recibidas aleatoriamente: " + d.initWithNWeapons());
        System.out.println("Numero de potenciadores de escudo recibidos: " + d.initWithNShields());
        System.out.println("Que jugador inicia la partida: " + d.whoStarts(3));
        System.out.println("Quien dispara primero: " + d.firstShot());
        System.out.println("La estacion esquiva el disparo: " + d.spaceStationMoves(2.98f));
       
        
    }
            
}
