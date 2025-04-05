package tracks.singlePlayer.evaluacion.src_azorinmarticarmen;

import java.util.ArrayList;
import java.util.Collections;

import core.game.Observation;
import core.game.StateObservation;
import core.player.AbstractPlayer;
import ontology.Types;
import serialization.Vector2d;
import tools.ElapsedCpuTimer;

public class myAgent_Camel extends AbstractPlayer{
	Vector2d fescala;
	tools.Vector2d portal;
	boolean[][] casillasProhibidas;
	
	public myAgent_Camel(StateObservation stateObs, ElapsedCpuTimer elapsedTimer) {
		// stateObs es representacion del juego al inicio
		fescala = new Vector2d(stateObs.getWorldDimension().width / stateObs.getObservationGrid().length, 
				stateObs.getWorldDimension().height / stateObs.getObservationGrid()[0].length);
		ArrayList<Observation>[] posiciones = stateObs.getPortalsPositions(stateObs.getAvatarPosition());
		portal = posiciones[0].get(0).position;
		portal.x = Math.floor(portal.x / fescala.x);
		portal.y = Math.floor(portal.y / fescala.y);
		
		casillasProhibidas = new boolean[stateObs.getObservationGrid().length][stateObs.getObservationGrid()[0].length];
		ArrayList<Observation>[] immovable = stateObs.getImmovablePositions();
		for(int i = 0; i < immovable.length; i++) {
			for (int j = 0; j < immovable[i].size(); j++) {
				int x = (int) Math.floor(immovable[i].get(j).position.x / fescala.x );
				int y = (int) Math.floor(immovable[i].get(j).position.y / fescala.y );
				casillasProhibidas[x][y] = true;
			}
		}
	}
	
	@Override
	public Types.ACTIONS act(StateObservation stateObs, ElapsedCpuTimer elapsedTimer) {
		// stateObs es representacion del juego antes de llamar a act
		Vector2d avatar = new Vector2d(stateObs.getAvatarPosition().x / fescala.x, 
				stateObs.getAvatarPosition().y / fescala.y);
		Vector2d newPos_up = avatar, newPos_down = avatar, newPos_left = avatar, newPos_right = avatar;
		if (avatar.y -1 >= 0) { // si no se sale del tablero
			newPos_up = new Vector2d(avatar.x, avatar.y-1);
		} 
		if (avatar.y +1 <= stateObs.getObservationGrid()[0].length -1) {
			newPos_down = new Vector2d(avatar.x, avatar.y+1);
		}
		if (avatar.x -1 >= 0) {
			newPos_left = new Vector2d(avatar.x-1, avatar.y);
		}
		if (avatar.x +1 <= stateObs.getObservationGrid().length -1) {
			newPos_right = new Vector2d(avatar.x+1, avatar.y);
		}
		
		ArrayList<Integer> distances = new ArrayList<Integer>();
		distances.add((int) (Math.abs(newPos_up.x - portal.x) + Math.abs(newPos_up.y - portal.y)));
		distances.add((int) (Math.abs(newPos_down.x - portal.x) + Math.abs(newPos_down.y - portal.y)));
		distances.add((int) (Math.abs(newPos_left.x - portal.x) + Math.abs(newPos_left.y - portal.y)));
		distances.add((int) (Math.abs(newPos_right.x - portal.x) + Math.abs(newPos_right.y - portal.y)));
		
		int minIndex = distances.indexOf(Collections.min(distances));
		switch(minIndex) {
		case 0: return Types.ACTIONS.ACTION_UP;
		case 1: return Types.ACTIONS.ACTION_DOWN;
		case 2: return Types.ACTIONS.ACTION_LEFT;
		case 3: return Types.ACTIONS.ACTION_RIGHT;
		default: return Types.ACTIONS.ACTION_NIL;
		}
	}
}

