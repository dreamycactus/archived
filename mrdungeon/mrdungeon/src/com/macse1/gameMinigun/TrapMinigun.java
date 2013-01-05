package com.macse1.gameMinigun;

import com.badlogic.gdx.math.Rectangle;
import com.badlogic.gdx.Gdx;
//import com.badlogic.gdx.graphics.Camera;
import com.badlogic.gdx.graphics.g2d.SpriteBatch;
import com.badlogic.gdx.math.Vector2;
import com.macse1.resources.Art; //Sprite handler
//import com.macse1.stateManagement.SceneNode;
import com.macse1.stateManagement.SceneNode;

public class TrapMinigun {
	
	//---------------------------VARIABLES GO HERE---------------------------
	public boolean acceptInput = true;
	public float coolDown = 0;
	public int ceiling = 0;
	public Vector2 pos = new Vector2(-1000, -1000); //Trap's coordinates
	public Vector2 vel = new Vector2(0, 0); //Trap's velocity
	public Vector2 acc = new Vector2(0, 0); //Trap's acceleration
	public final float XMAXACC = 600;
	public final float XMAXVEL = 600;
	public final float XDAMP = 3000;
	public Rectangle boundingBox = new Rectangle(); //Trap hitbox
	public boolean hitPlayer = false;
	public boolean hitGround = false;
	public boolean safeDistance = true;
	public float xLocTouched = 0;
	
	public TrapMinigun(int X, int Y) {
		//initial position
		pos.x = X;
		pos.y = Y;
		
		xLocTouched = X;
		ceiling = Y; //defines the ceiling
		
		//bounding box initialization
		boundingBox.x = pos.x;
		boundingBox.y = pos.y;
		boundingBox.width = 64;
		boundingBox.height = 64;
	}
	
	public void tick(float delta) {
		//---------------------------MOVEMENT CODE--------------------------
		if(Gdx.input.isTouched()) xLocTouched = Gdx.input.getX();
		
		tryMove(delta);
	}
	public void render(SpriteBatch batch) {
		//---------------------------RENDER CODE---------------------------
		batch.draw(Art.trapMinigun, pos.x, pos.y);
	}
	
	private void tryMove (float delta) { //Movement function, details whether or not the object can move or not
		
		if (acc.x <= 0 && vel.x > 0) vel.x = vel.x - XDAMP*delta;
		else if (acc.x >= 0 && vel.x < 0) vel.x = vel.x + XDAMP*delta;
		else if (acc.x != 0) vel.x = vel.x + acc.x*delta;
		
		if(boundingBox.x + 32 > xLocTouched + 8) vel.x = (xLocTouched - (boundingBox.x + 32))*2;
		else if(boundingBox.x + 32 < xLocTouched - 8) vel.x = (xLocTouched - (boundingBox.x + 32))*2;
		else acc.x = 0;
		
		if(vel.x > XMAXVEL) vel.x = XMAXVEL;
		if(vel.x < -XMAXVEL) vel.x = -XMAXVEL;
		
		boundingBox.x = boundingBox.x + vel.x*delta;

		if(boundingBox.x < 0)
		{
			boundingBox.x = 0;
			vel.x = 0;
		}
		if(boundingBox.x > SceneNode.GAME_WIDTH - boundingBox.width)
		{
			boundingBox.x = SceneNode.GAME_WIDTH - boundingBox.width;
			vel.x = 0;
		}
		
		
		pos.x = boundingBox.x;
	}
}
	