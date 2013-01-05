package com.macse1.gameBaseballBat;

import com.badlogic.gdx.Gdx;
import com.macse1.dungeon.Hero;
import com.macse1.resources.Art;
import com.macse1.resources.Sounds;
import com.macse1.stateManagement.*;
import com.macse1.states.DungeonState;

public class GameBaseballBat extends GameState {

	//---------------------------VARIABLES GO HERE---------------------------
	public final int FLOOR = 256;
	public HeroBaseballBat hero_ = new HeroBaseballBat(-32, FLOOR - 32, this);
	public TrapBaseballBat trap_ = new TrapBaseballBat(SceneNode.GAME_WIDTH * 3 / 4 - 32, FLOOR - 256 - 32);
	private float defaultCameraYPos;
	Hero h = new Hero();
	
	public void init(){
		//---------------------------INITIALIZATION---------------------------
		Gdx.input.setInputProcessor(this);
		setupGraphics();
		active_ = true;
		defaultCameraYPos = cam_.position.y;
		hero_.init();
		Sounds.s1.stop();
		Sounds.s2.play();
		Sounds.s3.stop();
		hero_.boundingBox.x = -32;
		trap_.boundingBox.y = FLOOR - 256 - 32;
		
	}
	public void setHero(Hero ho) {
		h.anger = ho.anger;
		h.life = ho.life;
	}
	
	public void tick(float delta){ //---------------------------UPDATE FUNCTION---------------------------
		hero_.tick(delta);
		trap_.tick(delta);
		if(trap_.hitGround)
		{
			cam_.position.y = defaultCameraYPos - 10;
			Gdx.input.vibrate(50);
		}
		
		if(cam_.position.y < defaultCameraYPos) cam_.position.y+=20*delta;
		
		cam_.update();
		
		if(hero_.pos.x > SceneNode.GAME_WIDTH) {
			DungeonState s = (DungeonState)(manager_.getGameState("SDungeon"));
			s.setHero(h);
			enterTransition("TFadeP", "SDungeon");
		}
		if (h.life<=0) { enterTransition("TFadeC", "SWin"); }
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
		batch_.draw(Art.miniBG1, 0, 0);
		hero_.render(batch_);
		trap_.render(batch_);
		batch_.end();
	}

}
