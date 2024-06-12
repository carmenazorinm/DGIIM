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
public class GameUniverse {
    private static final int WIN=10;
    private int currentStationIndex;
    private int turns;  
    private ArrayList<SpaceStation> spaceStations;
    private SpaceStation currentStation;
    private Dice dice;
    private GameStateController gameState;
    private EnemyStarShip currentEnemy;
    private boolean haveSpaceCity;
    
    //Constructor
    public GameUniverse(){
        turns=0; //Se inicializa el contador de turnos a 0
        dice=new Dice();  //Se crea el dado
        spaceStations = new ArrayList<>();
        gameState = new GameStateController();
        currentStationIndex = -1;
        currentStation = null;
        currentEnemy = null;
        spaceStations = new ArrayList<>();
        haveSpaceCity = false;
    }
    
    private void makeStationEfficient(){
        boolean random_bool = dice.extraEfficiency();
        if(!random_bool) currentStation=new PowerEfficientSpaceStation(currentStation);
        else currentStation=new BetaPowerEfficientSpaceStation(currentStation);
    }
    
    private void createSpaceCity(){
        if(!haveSpaceCity){
            currentStation=new SpaceCity(currentStation,spaceStations);
            haveSpaceCity=true;
        }
    }
    
    public CombatResult combat (){
        GameState state=gameState.getState();
        if  ((state== GameState.BEFORECOMBAT) || (state== GameState.INIT)) {
            return combat(currentStation, currentEnemy);
        }else{	
            return CombatResult.NOCOMBAT; 
        }
    }
    
    public CombatResult combat(SpaceStation station, EnemyStarShip enemy ){
        GameState state=gameState.getState();
        GameCharacter ch=dice.firstShot();
        boolean enemyWins; 
        CombatResult combatResult;

        if (ch==GameCharacter.ENEMYSTARSHIP){
                float fire=enemy.fire();
                ShotResult result=station.receiveShot(fire);

                if (result==ShotResult.RESIST){
                        fire=station.fire();
                        result=enemy.receiveShot(fire);
                        enemyWins=(result==ShotResult.RESIST);
                }else
                        enemyWins=true;
                          
        }
        else {
                float fire=station.fire();
                ShotResult result=enemy.receiveShot(fire);
                enemyWins=(result==ShotResult.RESIST);
        }

        if (enemyWins){
                float s=station.getSpeed();
                boolean moves=dice.spaceStationMoves(s);

                if(!moves){
                        Damage damage=enemy.getDamage();
                        station.setPendingDamage(damage);
                        combatResult=CombatResult.ENEMYWINS;
                }else{
                        station.move();
                        combatResult=CombatResult.STATIONESCAPES;
                }

        }else{
                Loot aLoot=enemy.getLoot();
                Transformation trans = station.setLoot(aLoot);
                
                if(trans == Transformation.SPACECITY)
                    createSpaceCity();
                else
                    if(trans == Transformation.GETEFFICIENT)
                        makeStationEfficient();
                
                combatResult=CombatResult.STATIONWINS;

        }

        gameState.next(turns, spaceStations.size());
        return combatResult;	

    }
    
    public void discardHangar(){
        if (gameState.getState()==GameState.INIT || gameState.getState()==GameState.AFTERCOMBAT)
            currentStation.discardHangar();
    }
    
    public void discardShieldBooster(int i){
        if (gameState.getState()==GameState.INIT || gameState.getState()==GameState.AFTERCOMBAT)
            currentStation.discardShieldBooster(i);
    }
    
    public void discardShieldBoosterInHangar(int i){
        if (gameState.getState()==GameState.INIT || gameState.getState()==GameState.AFTERCOMBAT)
            currentStation.discardShieldBoosterInHangar(i);
    }
    
    public void discardWeapon(int i){
        if (gameState.getState()==GameState.INIT || gameState.getState()==GameState.AFTERCOMBAT)
            currentStation.discardWeapon(i);
    }
    
    public void discardWeaponInHangar(int i){
        if (gameState.getState()==GameState.INIT || gameState.getState()==GameState.AFTERCOMBAT)
            currentStation.discardWeaponInHangar(i);
    }
    
    public GameState getState(){
        return gameState.getState();
    }
    
    public GameUniverseToUI getUIversion(){
        return new GameUniverseToUI(currentStation, currentEnemy);
    }
    
    public boolean haveAWinner(){
        return (currentStation.getNMedals()>= WIN);
    }
    
    public void init(ArrayList<String> names){
        GameState state=gameState.getState();
        if (state==GameState.CANNOTPLAY){
            CardDealer dealer=CardDealer.getInstance();
            Iterator<String> it = names.iterator();
            
            while (it.hasNext()){
                SuppliesPackage supplies=new SuppliesPackage(dealer.nextSuppliesPackage());
                SpaceStation station=new SpaceStation(it.next(), supplies);
                spaceStations.add(station);

                int nh=dice.initWithNHangars();
                int nw=dice.initWithNWeapons();
                int ns=dice.initWithNShields();

                Loot lo=new Loot(0, nw, ns, nh, 0);
                station.setLoot(lo);
            }

            int nPlayers=names.size();			
            currentStationIndex=dice.whoStarts(nPlayers);
            currentStation=spaceStations.get(currentStationIndex);
            currentEnemy=dealer.nextEnemy();
            gameState.next(turns, spaceStations.size());
        }
    }
    
    public void mountShieldBooster(int i){
        if (gameState.getState()==GameState.INIT || gameState.getState()==GameState.AFTERCOMBAT)
            currentStation.mountShieldBooster(i);
    }
    
    public void mountWeapon(int i){
        if (gameState.getState()==GameState.INIT || gameState.getState()==GameState.AFTERCOMBAT)
            currentStation.mountWeapon(i);
    }
    
    public boolean nextTurn(){
        GameState state=gameState.getState();
        if (state==GameState.AFTERCOMBAT){
            boolean stationState=currentStation.validState();
            
            if(stationState){
                currentStationIndex=(currentStationIndex+1)%spaceStations.size();
                turns+=1;
                
                currentStation=spaceStations.get(currentStationIndex);
                currentStation.cleanUpMountedItems();
                CardDealer dealer=CardDealer.getInstance();
                currentEnemy=dealer.nextEnemy();
                gameState.next(turns, spaceStations.size());
                return true;         
            }else{
                return false;
            }
        }else{
            return false;
        }
    }
    
    
}
