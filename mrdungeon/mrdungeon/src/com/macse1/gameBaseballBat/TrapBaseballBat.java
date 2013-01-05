package com.macse1.gameBaseballBat;

import com.badlogic.gdx.math.Rectangle;
import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.graphics.Camera;
import com.badlogic.gdx.graphics.g2d.SpriteBatch;
import com.badlogic.gdx.math.Vector2;
import com.macse1.resources.Art; //Sprite handler
import com.macse1.stateManagement.SceneNode;
import com.macse1.resources.Sounds;

public class TrapBaseballBat {
	
	//---------------------------VARIABLES GO HERE---------------------------
	public boolean isFalling = false;
	public boolean acceptInput = true;
	public float coolDown = 0;
	public int ceiling = 0;
	public Vector2 pos = new Vector2(-1000, -1000); //Trap's coordinates
	public Vector2 vel = new Vector2(0, 0); //Trap's velocity
	public Vector2 acc = new Vector2(0, 0); //Trap's acceleration
	public Rectangle boundingBox = new Rectangle(); //Trap hitbox
	public boolean hitPlayer = false;
	public boolean hitGround = false;
	public boolean safeDistance = true;
	
	public TrapBaseballBat(int X, int Y) {
		//initial position
		pos.x = X;
		pos.y = Y;
		
		ceiling = Y; //defines the ceiling
		
		//bounding box initialization
		boundingBox.x = pos.x;
		boundingBox.y = pos.y;
		boundingBox.width = 128;
		boundingBox.height = 32;
	}
	
	public void tick(float delta) {
		//---------------------------MOVEMENT CODE--------------------------
		if(isFalling && vel.y < 500)
		{
			//vel.y = vel.y + 2000*delta;
			vel.y = 400;
		}
		else if (boundingBox.y < ceiling)
		{
			vel.y = 0;
			if (!acceptInput && !Gdx.input.isTouched()) acceptInput = true; //Trap is ready to fall again
		}
		boundingBox.y = boundingBox.y + vel.y*delta;
		if(coolDown > 0)
		{
			coolDown = coolDown - 100*delta;
			//System.out.print(coolDown + "\n");
			if(coolDown <= 0) vel.y = -100;
		}
		
		if(Gdx.input.isTouched() && !isFalling && vel.y == 0 && acceptInput) //Function triggers the trap falling
		{
			isFalling = true;
			acceptInput = false;
		}
		
		boundingBox.y = boundingBox.y + vel.y*delta;
		if(hitGround)
			{
			hitGround = false;
			Sounds.footLand.play();
			}
		tryMove(delta);
	}
	public void render(SpriteBatch batch) {
		//---------------------------RENDER CODE---------------------------
		batch.draw(Art.trapBaseballBat, pos.x, pos.y);
	}
	
	private void tryMove (float delta) { //Movement function, details whether or not the object can move or not

		if(boundingBox.y > 256 - 128 && isFalling)
		{
			safeDistance = false;
			isFalling = false;
			vel.y = 0;
			if (!hitPlayer) coolDown = 75;
			else
			{
				coolDown = 40;
				hitPlayer = false;
			}
			boundingBox.y = 256 - 128;
			hitGround = true;
		}
		if(boundingBox.y < 256 - 128 - 32 && !safeDistance)
		{
			safeDistance = true;
		}
		pos.y = boundingBox.y - 256 - 128;
	}
}
	