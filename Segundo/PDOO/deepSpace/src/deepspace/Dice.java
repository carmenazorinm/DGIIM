/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package deepspace;

import java.util.Random;

/**
 * @brief responsabilidad de tomar todas las decisiones que dependen del azar en el juego
 * @author mariacribi
 */
public class Dice {
    private final float NHANGARSPROB;
    private final float NSHIELDSPROB;
    private final float NWEAPONSPROB;
    private final float FIRSTSHOTPROB;
    private final float EXTRAEFFICIENCYPROB;
    private Random generator; 
    
    //Constructor con visibilidad de paquete
    Dice (){
        NHANGARSPROB=0.25f;
        NSHIELDSPROB=0.25f;
        NWEAPONSPROB=0.33f;
        FIRSTSHOTPROB=0.5f;
        EXTRAEFFICIENCYPROB=0.8f;
        generator=new Random();
    }
    
    public boolean extraEfficiency(){
        double nrandom=generator.nextDouble();
        return nrandom < EXTRAEFFICIENCYPROB;
    }
    
    int initWithNHangars (){
        //número de hangares que recibirá una estación espacial al ser creada
        double nrandom=generator.nextDouble(); 
        if (nrandom<NHANGARSPROB){
            return 0; 
        }else
            return 1;
    }
    
    int initWithNWeapons (){   
        //número de armas que recibirá una estación espacial al ser creada
        double nrandom=generator.nextDouble();
        if (nrandom<NWEAPONSPROB){
                return 1;
        }
        else{
            if (nrandom<2*NWEAPONSPROB)
                return 2;
            else 
                return 3;
        }
        
    }
    
    int initWithNShields (){
        // número de potenciadores de escudo que recibirá una estación espacial al ser creada
        double nrandom=generator.nextDouble();
        if (nrandom<NSHIELDSPROB){
            return 0; 
        }else 
            return 1;
    }
    
    int whoStarts(int nPlayers){ 
        //genera un número aleatorio del intervalo [0,nPlayers-1]
        //determina el jugador (su índice) que iniciará la partida
        return generator.nextInt(nPlayers);  //aleatorio entre [0,nPlayers-1]
    }
    
    GameCharacter firstShot (){
        double nrandom=generator.nextDouble();
        if (nrandom<FIRSTSHOTPROB){
            return GameCharacter.SPACESTATION;
        }else{
            return GameCharacter.ENEMYSTARSHIP;
        }
    }
    
    boolean spaceStationMoves (float speed){    //Asumimos que speed c [0,1]
        float nrandom=generator.nextFloat(); 
        return (nrandom<speed);
    }
    
    @Override
    public String toString(){
        String s = "Dice";
        return s;
    }

}
