package com.macse1.states;

import com.badlogic.gdx.InputProcessor;
import com.macse1.resources.Art;
import com.macse1.stateManagement.GameState;
import com.macse1.stateManagement.StateManager;

public class MiniGame1State extends GameState {
	// Members
	
	// Methods
	public MiniGame1State() {
		super();
	}
	public void tick(float delta) {
		
	}
	public void render(float delta) {
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
		enterTransition("TFade", "SDungeon");
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

