package com.macse1.gameMinigun;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.graphics.g2d.Animation;
import com.badlogic.gdx.graphics.g2d.SpriteBatch;
import com.badlogic.gdx.math.Rectangle;
import com.badlogic.gdx.math.Vector2;
import com.macse1.resources.Art; //Sprite handler
//import com.macse1.stateManagement.SceneNode;
import java.util.Random;

public class BulletsMinigun {
	
	//---------------------------VARIABLES GO HERE---------------------------
	public GameMinigun level; //level passed in
	
	public Vector2 pos = new Vector2(-1000, -1000); //Hero's coordinates
	public Vector2 vel = new Vector2(0, 0); //Hero's velocity
	public Vector2 acc = new Vector2(0, 0); //Hero's acceleration
	public Rectangle boundingBox = new Rectangle(); //Hero's hitbox
	public float floor;
	public final float XMAX = 100;
	public final float XMAXDASH = XMAX*4;
	public int AILevel = 0;
	public Random AIrandomizer = new Random();
	public float timer;
	public final float TIMERLIMIT = 999999999;
	public final int POINT1 = 64*2;
	public final int POINT2 = 64*4;
	public int direction = 1;
	
	//AI conditions
	public boolean jumpRepeatedly = false; //Hero never stops jumping
	public boolean isDashing = false; //AI's upper move limit is removed
	public boolean isCrushed = false; //hero is crushed
	public boolean isPanicking = false; //Hero immediately runs under trap at closest opportunity
	public boolean inAir = false; //Hero is in air
	public boolean clearToPass = true; //Hero is able to run under
	public boolean stopShort1 = false; //AI stops just in front of spikes for a random period of time
	public boolean runOnce = false;
	public int directionDecisionCounter = 0;
	public boolean refresh1 = false;
	public boolean refresh2 = true;
	
	//AI timers
	
	public int dangerLevel = 0; //trust level of the hero
	
	//animation shenanigans
	public float stateTime = 0;
	//TextureRegion[] animFrames = new TextureRegion(Art.playerMinigame).split(32, 32)[0];
	Animation walkRight = new Animation(0.1f,Art.playerMinigame[0][0], Art.playerMinigame[0][1]);
	
	public BulletsMinigun(int X, int Y) {
		pos.x = X;
		pos.y = Y;
		
		//bounding box initialization
		boundingBox.x = pos.x;
		boundingBox.y = pos.y;
		boundingBox.width = 8;
		boundingBox.height = 512;
	}
	
	public void tick(float delta) {
		stateTime = stateTime + Gdx.graphics.getDeltaTime();
		//---------------------------MOVEMENT CODE--------------------------
		tryMove(delta);
		
	}
	public void render(SpriteBatch batch) {
		//---------------------------RENDER CODE---------------------------
		batch.draw(Art.minigunBullets, pos.x, pos.y);
	}
	
	private void tryMove(float delta)
	{		
		pos.x = boundingBox.x;
		pos.y = boundingBox.y;
	}
}
