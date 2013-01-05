package com.macse1.states;

import com.badlogic.gdx.Gdx;
import com.macse1.dungeon.LevelData;
import com.macse1.resources.Art;
import com.macse1.resources.Sounds;
import com.macse1.stateManagement.GameState;
import com.macse1.utils.MyMath;

public class MainMenuState extends GameState {
	public void init() {
		Sounds.s1.stop();
		Sounds.s2.stop();
		Sounds.s3.play();
		setupGraphics();
		Gdx.input.setInputProcessor(this);
		active_ = true;
	}
	public void tick(float delta) {
		
	}
	public void render(float delta) {
		batch_.disableBlending();
		batch_.begin();
			batch_.draw(Art.main_menu_bg, 0, 0);
		batch_.end();
		
	}
	public MainMenuState() {
		
	}
	
	public boolean keyDown(int keycode) {
		
		return false;
	}

	
	public boolean keyUp(int keycode) {
		
		return false;
	}

	
	public boolean keyTyped(char character) {
		
		return false;
	}

	
	public boolean touchDown(int x, int y, int pointer, int button) {
		int width = 50, height = 50;
		int start_x = 215, start_y = 99;
		int pick_x = 256, pick_y = 126;
		int ox = 310, oy = 99;
		int rx = 358, ry = 126;
		int tx = 403, ty = 99;
		
		
		
		if (MyMath.pointInRect(x, y, start_x, start_y, start_x+width, start_y+height)) {
			DungeonState s = (DungeonState)(manager_.getGameState("SDungeon"));
			LevelData data = LevelData.Level()[0];
			
			s.setLevel(data);
			enterTransition("TFadeC", "SDungeon");
			
		}
		if (MyMath.pointInRect(x, y, pick_x, pick_y, pick_x+width, pick_y+height)) {
			enterTransition("TFadeC", "SLevelSelect");
		}
		else if (MyMath.pointInRect(x, y, ox, oy, ox+width, oy+height)) {
			enterTransition("TFadeC", "SInstruct");
		}
		else if (MyMath.pointInRect(x, y, rx, ry, rx+width, ry+height)) {
			enterTransition("TFadeC", "SInstruct");
		}
		else if (MyMath.pointInRect(x, y, tx, tx, tx+width, ty+height)) {
			enterTransition("TFadeC", "SMain");
		}
		return false;
	}

	
	public boolean touchUp(int x, int y, int pointer, int button) {
		
		return false;
	}

	
	public boolean touchDragged(int x, int y, int pointer) {
		
		return false;
	}

	
	public boolean touchMoved(int x, int y) {
		
		return false;
	}

	
	public boolean scrolled(int amount) {
		
		return false;
	}

	

	
}
