package com.macse1.states;

import com.macse1.dungeon.LevelData;
import com.macse1.resources.Art;
import com.macse1.stateManagement.GameState;
import com.macse1.utils.MyMath;

public class CreditsState extends GameState {
	
	public void tick(float delta) {
		
	}
	public void render(float delta) {
		batch_.disableBlending();
		batch_.begin();
			batch_.draw(Art.credits_bg, 0, 0);
		batch_.end();
		
	}
	public CreditsState() {
		
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
		enterTransition("TFadeC", "SMain");
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
