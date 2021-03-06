package com.macse1.stateManagement;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.InputProcessor;
import com.badlogic.gdx.graphics.g2d.TextureRegion;

public abstract class GameState extends SceneNode implements InputProcessor {
	
	public GameState() {
		super();
	}
	public void init() {
		setupGraphics();
		Gdx.input.setInputProcessor(this);
		active_ = true;
	}
	public void draw (TextureRegion region, int x, int y) {
		int width = region.getRegionWidth();
		if (width < 0) width = -width;
		batch_.draw(region, x, y, width, region.getRegionHeight());
	}
	public abstract void render(float delta);

}
