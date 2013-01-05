package com.macse1.stateManagement;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.graphics.GL10;
import com.badlogic.gdx.graphics.Pixmap;
import com.badlogic.gdx.graphics.Texture;
import com.badlogic.gdx.graphics.g2d.TextureRegion;
import com.macse1.utils.Input;

public abstract class TransitionState extends SceneNode {
	protected SceneNode old_state_, new_state_;
	
	public TransitionState() {
		super();
	}
	
	// Don't use transitions as states.... :(
	public void setTransition(SceneNode stateo, SceneNode staten) {
		old_state_ = stateo;
		new_state_ = staten;
		

	}
	public void init() {
		setupGraphics();
		new_state_.init();
	}

	public abstract void render(float delta);

	public void exit() {
		batch_.dispose();
	}
}
