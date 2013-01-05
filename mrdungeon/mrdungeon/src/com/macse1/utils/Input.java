package com.macse1.utils;

import com.badlogic.gdx.Application.ApplicationType;
import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.InputProcessor;

public class Input implements InputProcessor {

	public boolean[] buttons 		= new boolean[64];
	public boolean[] old_buttons 	= new boolean[64];
	
	public void tick() {
		for (int i=0; i<buttons.length; ++i) {
			old_buttons[i] = buttons[i];
			if (Gdx.app.getType() == ApplicationType.Android) {
				if (!Gdx.input.isTouched(i)) continue;
			}
		}
	}
	
	public boolean keyDown(int keycode) {
		// TODO Auto-generated method stub
		return false;
	}

	
	public boolean keyUp(int keycode) {
		// TODO Auto-generated method stub
		return false;
	}

	
	public boolean keyTyped(char character) {
		// TODO Auto-generated method stub
		return false;
	}

	
	public boolean touchDown(int x, int y, int pointer, int button) {
		return false;
	}

	
	public boolean touchUp(int x, int y, int pointer, int button) {
		// TODO Auto-generated method stub
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
