package com.macse1.dungeon;

import java.util.ArrayList;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.graphics.OrthographicCamera;
import com.badlogic.gdx.graphics.g2d.SpriteBatch;
import com.badlogic.gdx.math.Rectangle;
import com.badlogic.gdx.math.Vector3;
import com.macse1.resources.Art;
import com.macse1.stateManagement.SceneNode;
import com.macse1.states.DungeonState;
import com.macse1.tiles.Tile;
import com.macse1.tiles.TileBoard;
import com.macse1.utils.MyMath;

public class DungeonInterface {
	// Members 
	DungeonState state_;
	LevelData level;
	public static final int BIG_X = 30, OFF_X = 50, OFF_Y = 8;
	public static final int BLOCKING = 0, OCCUPIED = 1;
	ArrayList<Vector3> buttons = new ArrayList<Vector3>();
	float state_time = 0.f;
	
	boolean blocking = false;
	
	public DungeonInterface(DungeonState state, LevelData data) {
		state_ = state;
		level = data;
	}
	public void render(float delta, SpriteBatch batch) {
		OrthographicCamera cam = state_.cam_;
		Vector3 pos = new Vector3(cam.position.x-SceneNode.GAME_WIDTH/2, cam.position.y+SceneNode.GAME_HEIGHT/2+Art.interface_frame.getRegionHeight(), 0);

		batch.draw(Art.interface_frame, pos.x, pos.y);
		pos.x += BIG_X;
		if (level.num_walls>0) {
			batch.draw(Art.interface_button[0], pos.x, pos.y+OFF_Y);
		}
		if (level.num_spikes>0) {
			batch.draw(Art.interface_button[1], pos.x+OFF_X, pos.y+OFF_Y);
		}
		if (level.num_turrets>0) {
			batch.draw(Art.interface_button[2], pos.x+OFF_X*2, pos.y+OFF_Y);
		}
		//batch.draw(Art.interface_button[3], pos.x+OFF_X*3, pos.y+OFF_Y);
		
		
		
		
	}
	public int touchedButton() {
		int x = Gdx.input.getX();
		int y = Gdx.input.getY();
		OrthographicCamera cam = state_.cam_;
		Vector3 pos = new Vector3(BIG_X, SceneNode.GAME_HEIGHT+Art.interface_button[0].getRegionHeight()-20, 0);
		int art_x = Art.interface_button[0].getRegionWidth();
		int art_y = Art.interface_button[0].getRegionHeight();
		
		if (     MyMath.pointInRect(x, y, (int)pos.x, (int)pos.y, (int)pos.x+art_x, (int)pos.y-art_y) && level.num_walls>0) {
			return Tile.WALL;
		}
		else if (MyMath.pointInRect(x, y, (int)pos.x+OFF_X, (int)pos.y, (int)pos.x+OFF_X+art_x, (int)pos.y-art_y) && level.num_spikes>0) {
			return Tile.SPIKE;
		}
		else if (MyMath.pointInRect(x, y, (int)pos.x+OFF_X*2, (int)pos.y, (int)pos.x+OFF_X*2+art_x, (int)pos.y-art_y) && level.num_turrets>0) {
			return Tile.GUN;
		}
		else if (MyMath.pointInRect(x, y, (int)339, (int)286, (int)339+114, (int)286+50)) {
			return 1;
		}
		return -1;
		
	}
	public void printError(int error) {
		switch (error) {
			case BLOCKING:
			blocking = true;
			break;
		}
		
	}
}
