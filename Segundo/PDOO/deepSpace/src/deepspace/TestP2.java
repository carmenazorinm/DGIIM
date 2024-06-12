/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package deepspace;

import java.util.ArrayList;

/**
 * Class to test the second practice of the subject
 * @author Javier Gómez López
 */
public class TestP2 {
    public static void main (String[] args){
        // Testing Hangar
        // ********************************
        System.out.println("Testing Hangar");
        System.out.println("****************************");
        
        //Creating a new hangar
        Hangar hangar_test = new Hangar(9);
        System.out.println("The created Hangar is:");
        System.out.println(hangar_test);
        
        //Testing the copy constructor
        Hangar hangar_copy = new Hangar(hangar_test);
        System.out.println("The copy of the previous Hangar is:");
        System.out.println(hangar_copy);
        System.out.println();
        
        //Testing UI version
        HangarToUI hangar_UI = hangar_test.getUIversion();
        System.out.println("The Hangar UI Version is; ");
        System.out.println(hangar_UI);
        System.out.println("-----------");
        System.out.println();
        
        
        //Testing add shield and weapon
        Weapon weapon_test = new Weapon("Weapon test", WeaponType.PLASMA, 2);
        ShieldBooster shield_test = new ShieldBooster("Shield test", 3.1415f,4);
        
        
        System.out.println("Adding some weapons and shields:");
        System.out.println();
        
        for(int i = 0; i < 5; i++){
            if(hangar_test.addShieldBooster(shield_test)){
                System.out.println("#" + i + " ShieldBooster added succesfully!");
            }
            else{
                System.out.println("#" + i + " ShieldBooster failed to add");
            }
        }
        
        System.out.println();
        
        //The last weapon has to fail because of the space available
        for(int i = 0; i < 5; i++){
            if(hangar_test.addWeapon(weapon_test)){
                System.out.println("#" + i + " Weapon added succesfully!");
            }
            else{
                System.out.println("#" + i + " Weapon failed to add");
            }
        }
        
        System.out.println();
        
        //Now show the copy
        System.out.println("State of the original hangar: ");
        System.out.println(hangar_test);
        System.out.println();
        
        System.out.println("State of the copy: ");
        System.out.println(hangar_copy);
        System.out.println("-----------");
        System.out.println();
        
        //Removing some weapons and shields
        System.out.println("Removing three shields...");
        for(int i = 0; i < 3; i++){
            hangar_test.removeShieldBooster(0);
        }
        
        System.out.println();
        
        System.out.println("Removing two weapons...");
        for(int i = 0; i < 2; i++){
            hangar_test.removeWeapon(0);
        }
        
        System.out.println();
        
        //Now show the copy
        System.out.println("State of the original hangar: ");
        System.out.println(hangar_test);
        System.out.println();
        
        System.out.println("State of the copy: ");
        System.out.println(hangar_copy);
        System.out.println("-----------");
        System.out.println();
        
        System.out.println();
        
        // Testing Damage
        // ********************************
        System.out.println("Testing Damage");
        System.out.println("****************************");
        
        ArrayList<WeaponType> weapon_type_list = new ArrayList<>(0);
        weapon_type_list.add(WeaponType.LASER);
        weapon_type_list.add(WeaponType.PLASMA);
        weapon_type_list.add(WeaponType.LASER);
        weapon_type_list.add(WeaponType.MISSILE);
        
        Damage damage_numeric = new Damage(4,3);
        Damage damage_specific = new Damage(weapon_type_list, 3);
        
        System.out.println("Numeric Damage: ");
        System.out.println(damage_numeric);
        System.out.println("Specific Damage: ");
        System.out.println(damage_specific);
        System.out.println("-----------");
        
        //Testing copy constructor
        Damage damage_numeric_copy = new Damage(damage_numeric);
        Damage damage_specific_copy = new Damage(damage_specific);
        
        System.out.println("The copy of the Numeric Damage is:");
        System.out.println(damage_numeric_copy);
        System.out.println("The copy of the Specific Damage is:");
        System.out.println(damage_specific_copy);
        System.out.println("-----------");
        System.out.println();
        
        //Testing UI Version
        DamageToUI damage_UI = damage_numeric.getUIversion();
        System.out.println("UI Numeric Version: ");
        System.out.println(damage_UI);
        System.out.println();
        
        //Testing adjust method
        System.out.println("Testing Damage.adjust()...");
        
        ArrayList<Weapon> weapons_to_adjust = new ArrayList<>(0);
        weapons_to_adjust.add(new Weapon("First weapon", WeaponType.LASER, 3));
        weapons_to_adjust.add(new Weapon("Second Weapon", WeaponType.PLASMA, 4));
        weapons_to_adjust.add(new Weapon("Third Weapon", WeaponType.MISSILE,1));
        
        ArrayList<ShieldBooster> shields_to_adjust = new ArrayList<>(0);
        shields_to_adjust.add(new ShieldBooster("First shield", 3.4f, 3));
        shields_to_adjust.add(new ShieldBooster("Second Shield", 6f, 1));
        
        Damage adjusted_damage = damage_numeric.adjust(weapons_to_adjust, shields_to_adjust);
        System.out.println("Numeric adjusted damage is ");
        System.out.println(adjusted_damage);
        System.out.println();
        
        adjusted_damage = damage_specific.adjust(weapons_to_adjust, shields_to_adjust);
        System.out.println("Adjusted specific damage is: ");
        System.out.println(adjusted_damage);
        System.out.println("-----------");
        System.out.println();
        
        
        //Testing dicard methods
        System.out.println("Discarding some weapons...");
        for(int i = 0; i < 2; i++){
            System.out.println("#" + i + " Discarding weapon on numeric damage");
            damage_numeric.discardWeapon(weapon_test);
            
            System.out.println("#" + i + " Discarding weapon on specific damage");
            damage_specific.discardWeapon(weapon_test);
        }
        
        System.out.println();
        
        System.out.println("Discarding some shieldboosters...");
        for(int i = 0; i < 2; i++){
            System.out.println("#" + i + " Discarding shield on numeric damage");
            damage_numeric.discardShieldBooster();
            
            System.out.println("#" + i + " Discarding shield on specific damage");
            damage_specific.discardShieldBooster();
        }
        
        System.out.println();
        
        System.out.println("State of the numeric damage: ");
        System.out.println(damage_numeric);
        System.out.println("State of the copy of the numeric damage: ");
        System.out.println(damage_numeric_copy);
        
        System.out.println();
        
        System.out.println("State of the specific damage: ");
        System.out.println(damage_specific);
        System.out.println("State of the copy of the numeric damage: ");
        System.out.println(damage_specific_copy);
        System.out.println("-----------");
        System.out.println();
        
        System.out.println();
        
        // Testing EnemyStarShip
        // ********************************
        System.out.println("Testing EnemyStarShip");
        System.out.println("****************************");
        
        Damage damage_test = new Damage(2,3);
        Loot loot_test = new Loot(1,2,3,4,5);
        
        //Testing constructor
        EnemyStarShip enemy_test = new EnemyStarShip("Enemy Test", 1.5f, 3.14f, loot_test, damage_test);
        System.out.println("The testing EnemyStart is:");
        System.out.println(enemy_test);
        System.out.println();
        
        //Testing copy constructor
        EnemyStarShip enemy_copy = new EnemyStarShip(enemy_test);
        System.out.println("The copy of the enemy is: ");
        System.out.println(enemy_copy);
        System.out.println();
        
        //Testing the UI Version
        EnemyToUI enemy_UI = enemy_test.getUIversion();
        System.out.println("The UI version is: ");
        System.out.println(enemy_UI);
        System.out.println();
        
        //Testing some shots
        System.out.println("The enemy is going to receive some shots");
        for(int i = 0; i < 7; i++){
            ShotResult result = enemy_test.receiveShot(i);
            System.out.println("Receiving " + i + " power shot results in " + result);
        }
        
        System.out.println();
        
        // Testing SpaceStation
        // ********************************
        System.out.println("Testing SpaceStation");
        System.out.println("****************************");
        
        SuppliesPackage s = new SuppliesPackage(0.6f, 3.14f, 1.7f);
        SpaceStation space_test = new SpaceStation("Test Station", s);
        
        System.out.println("The SpaceStation is:");
        System.out.println(space_test);
        System.out.println("-----------");
        System.out.println();
        
        System.out.println("The speed of the SpaceShip is: " + space_test.getSpeed());
        System.out.println("-----------");
        System.out.println();
        
        //Testing validState
        System.out.println("With no pendingDamage, is the state valid?: " + space_test.validState());
        System.out.println("-----------");
        System.out.println();
        
        //Testing receive Hangar
        System.out.println("Testing receive Hangar");
        space_test.receiveHangar(hangar_test);
        System.out.println(space_test.getHangar());
        System.out.println("-----------");
        System.out.println();
        
        //Testing receiving Weapon and ShieldBoosters
        System.out.println("Adding some weapons and shieldboosters...");
        System.out.println("\nCleaning Hangar...");
        hangar_test = new Hangar(10);
        space_test.discardHangar();
        space_test.receiveHangar(hangar_test);
        
        space_test.receiveShieldBooster(shield_test);
        space_test.receiveWeapon(weapon_test);
        
        System.out.println(space_test.getHangar());
        System.out.println("-----------");
        System.out.println();
        
        //Testing mounting some Shields and Weapons
        System.out.println("Mounting some weapons and shieldboosters...");
        space_test.mountShieldBooster(0);
        space_test.mountWeapon(0);
        
        System.out.println("\nThe new Hangar:");
        System.out.println(space_test.getHangar());
        
        System.out.println("\nMounted Weapons and Shields:");
        System.out.println("\tWeapons:" + space_test.getWeapons());
        System.out.println("\tShields: " + space_test.getShieldBoosters());
        System.out.println("-----------");
        System.out.println();
        
        //Testing move
        System.out.println("Testing SpaceStation.move()");
        System.out.println("Fuel Units: " + space_test.getFuelUnits());
        System.out.println("Speed: " + space_test.getSpeed());
        space_test.move();
        System.out.println("Fuel units after movement: " + space_test.getFuelUnits());
        System.out.println("-----------");
        System.out.println();
        
        //Testing setPendingDamage
        System.out.println("Testing setPendingDamage");
        space_test.setPendingDamage(damage_test);
        System.out.println("\nNew damage:");
        System.out.println(space_test.getPendingDamage());
        
        System.out.println("Is the state Valid now? " + space_test.validState());
        System.out.println("-----------");
        System.out.println();
        
        //Testing discartes
        System.out.println("Restoring Hangar...");
        space_test.discardHangar();
        space_test.receiveHangar(hangar_test);
        
        space_test.receiveShieldBooster(shield_test);
        space_test.receiveWeapon(weapon_test);
        
        System.out.println(space_test.getHangar());
        
        System.out.println("\nDiscarting some shields and weapons...");
        space_test.discardShieldBoosterInHangar(0);
        space_test.discardWeaponInHangar(0);
        
        System.out.println();
        System.out.println(space_test.getHangar());
        System.out.println("-----------");
        System.out.println();
        
        // Testing GameUniverse
        // ********************************
        System.out.println("Testing GameUniverse");
        System.out.println("****************************");
        
        GameUniverse universe_test = new GameUniverse();
        System.out.println("New GameUniverse: ");
        System.out.println(universe_test);        
        System.out.println("We cant test anymore because we can't init a game");
        System.out.println("-----------");
        System.out.println();
        
    }
}