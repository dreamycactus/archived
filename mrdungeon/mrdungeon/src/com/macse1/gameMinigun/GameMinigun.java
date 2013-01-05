package com.macse1.gameMinigun;

import com.badlogic.gdx.Gdx;
import com.macse1.resources.Art;
import com.macse1.stateManagement.*;

public class GameMinigun extends GameState {

	//---------------------------VARIABLES GO HERE---------------------------
	public final int FLOOR = 128+4;
	public HeroMinigun hero_ = new HeroMinigun(-64, FLOOR - 32, this);
	public TrapMinigun trap_ = new TrapMinigun(SceneNode.GAME_WIDTH / 2 - 32, SceneNode.GAME_HEIGHT-64);
	public BulletsMinigun bullets_ = new BulletsMinigun(0, 0);
	
	public void init(){
		//---------------------------INITIALIZATION---------------------------
		Gdx.input.setInputProcessor(this);
		setupGraphics();
		active_ = true;
		
	}
	
	public void tick(float delta){ //---------------------------UPDATE FUNCTION---------------------------
		bullets_.boundingBox.x = trap_.boundingBox.x + 32 - 4;
		
		hero_.tick(delta);
		trap_.tick(delta);
		bullets_.tick(delta);
	}
	
	
	@Override
	public boolean keyDown(int keycode) {
		// TODO Auto-generated method stub
		return false;
	}

	@Override
	public boolean keyUp(int keycode) {
		// TODO Auto-generated method stub
		return false;
	}

	@Override
	public boolean keyTyped(char character) {
		// TODO Auto-generated method stub
		return false;
	}

	@Override
	public boolean touchDown(int x, int y, int pointer, int button) {
		// TODO Auto-generated method stub
		//if(!trap_.isFalling) trap_.isFalling = true;
		return false;
	}

	@Override
	public boolean touchUp(int x, int y, int pointer, int button) {
		// TODO Auto-generated method stub
		return false;
	}

	@Override
	public boolean touchDragged(int x, int y, int pointer) {
		// TODO Auto-generated method stub
		return false;
	}

	@Override
	public boolean touchMoved(int x, int y) {
		// TODO Auto-generated method stub
		return false;
	}

	@Override
	public boolean scrolled(int amount) {
		// TODO Auto-generated method stub
		return false;
	}

	@Override
	public void render(float delta) {
		// TODO Auto-generated method stub
		batch_.enableBlending();
		batch_.setProjectionMatrix(cam_.combined);
		batch_.begin();
		batch_.draw(Art.miniBG2, 0, 0);
		hero_.render(batch_);
		trap_.render(batch_);
		bullets_.render(batch_);
		batch_.end();
	}

}
