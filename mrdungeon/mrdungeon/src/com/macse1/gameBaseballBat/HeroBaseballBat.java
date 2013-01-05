package com.macse1.gameBaseballBat;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.graphics.g2d.Animation;
import com.badlogic.gdx.graphics.g2d.SpriteBatch;
import com.badlogic.gdx.math.Rectangle;
import com.badlogic.gdx.math.Vector2;
import com.macse1.resources.Art; //Sprite handler
import com.macse1.resources.Sounds;
import com.macse1.stateManagement.SceneNode;
import java.util.Random;

public class HeroBaseballBat {
	
	//---------------------------VARIABLES GO HERE---------------------------
	public GameBaseballBat level; //level passed in
	
	public Vector2 pos = new Vector2(-1000, -1000); //Hero's coordinates
	public Vector2 vel = new Vector2(0, 0); //Hero's velocity
	public Vector2 acc = new Vector2(0, 0); //Hero's acceleration
	public Rectangle boundingBox = new Rectangle(); //Hero's hitbox
	public float floor;
	public final float XMAX = 250;
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
	public boolean startedDashing = false;
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
	Animation idleRight = new Animation(0.1f,Art.playerMinigame[0][0]);
	Animation walkRight = new Animation(0.1f,Art.playerMinigame[0][0], Art.playerMinigame[1][0], Art.playerMinigame[2][0], Art.playerMinigame[3][0]);
	Animation jumpRight = new Animation(0.1f,Art.playerMinigame[1][1], Art.playerMinigame[2][1]);
	Animation runRight = new Animation(0.1f,Art.playerMinigame[1][2], Art.playerMinigame[2][2]);
	Animation hurtRight = new Animation(0.1f, Art.playerMinigame[2][3]);
	
	public HeroBaseballBat(int X, int Y, GameBaseballBat importedLevel) {
		level = importedLevel;
		pos.x = X;
		pos.y = Y;
		
		//bounding box initialization
		boundingBox.x = pos.x;
		boundingBox.y = pos.y;
		boundingBox.width = 32;
		boundingBox.height = 32;
		floor = boundingBox.y + boundingBox.height;
		
		//movement initialization
		acc.x = 400f;
		acc.y = 2000f; //gravity
		vel.x = 200f;
		
	}
	public void init() {
		dangerLevel = level.h.anger;
		initAI();
	}
	
	public void tick(float delta) {
		
		
		stateTime = stateTime + Gdx.graphics.getDeltaTime();
		//---------------------------MOVEMENT CODE--------------------------
		//pos.x = pos.x + 100*delta;
		if (isDashing && !startedDashing && Math.abs(vel.x) > XMAX)
		{
			startedDashing = true;
			Sounds.heroJet.play(0.75f);
		}
		else if ((!isDashing && startedDashing) || (Math.abs(vel.x) <= XMAX && startedDashing))
		{
			startedDashing = false;
		}
		
		if(timer > 0 && timer < TIMERLIMIT) timer = timer - 100*delta;
		
		if(boundingBox.x > SceneNode.GAME_WIDTH) //TODO: debug statement; remove this later
		{
			isDashing = false;
			directionDecisionCounter = 0;
			initAI();
			boundingBox.x = 0;
			acc.x = 400f;
			isPanicking = false;
			refresh1 = false;
			refresh2 = true;
			direction = 1;
		}
		//if(Gdx.input.isTouched() && vel.y == 0) vel.y = -500;
		
		vel.y = vel.y + acc.y*delta;
		vel.x = vel.x + acc.x*delta;
		if(!isDashing)
		{
			if(vel.x > XMAX) vel.x = XMAX;
			if(vel.x < -XMAX) vel.x = -XMAX;
		}
		else if(isDashing)
		{
			if(vel.x > XMAXDASH) vel.x = XMAXDASH;
			if(vel.x < -XMAXDASH) vel.x = -XMAXDASH;
		}
		
		//---------------------------MOVEMENT AI CODE---------------------------
		//operates with a "danger level"
		//higher danger level unlocks different types of AI
		//high levels can utilize more than one type of AI at random
		//lower numbers signify player "confidence", ie confidence of 0 allows player to run straight through
		
		if(isPanicking && level.trap_.boundingBox.y + 128 < boundingBox.y)
		{
			acc.x = 50000;
		}
		
		if (level.trap_.hitGround && !underTrap())
		{
			panic();
		}
		
		if(boundingBox.x > POINT2 && direction == 1 && refresh2)
		{
			refresh1 = true;
			refresh2 = false;
			stopPoint1();
		}
		else if(boundingBox.x < POINT1 && direction == 0 && refresh1)
		{
			refresh1 = false;
			refresh2 = true;
			stopPoint1();
		}
		else if(boundingBox.x < 1 && direction == 0)
		{
			direction = 1;
			isDashing = true;
			vel.x = XMAXDASH;
		}
		if(timer <= 0)
		{
			if(!stopShort1 && !runOnce && directionDecisionCounter <= 0)
			{
				vel.x = XMAX;
			}
			else if(direction == 0 && directionDecisionCounter > 0)
			{
				if(AIrandomizer.nextInt(3) == 0)
				{
					vel.x = -XMAX;
				}
				else if(AIrandomizer.nextInt(3) == 1)
				{
					isDashing = true;
					vel.x = -XMAX*3;
				}
				else if(AIrandomizer.nextInt(3) == 2)
				{
					vel.x = -XMAX*3;
					jump(400);
				}
				else vel.x = XMAX;
				directionDecisionCounter--;
			}
			else if(direction == 1 && directionDecisionCounter > 0)
			{
				if(AIrandomizer.nextInt(3) == 0)
				{
					vel.x = XMAX;
				}
				else if(AIrandomizer.nextInt(3) == 1)
				{
					isDashing = true;
					vel.x = XMAX*2;
				}
				else if(AIrandomizer.nextInt(3) == 2)
				{
					vel.x = XMAX*2;
					jump(400);
				}
				else vel.x = XMAX;
				direction = 1;
				directionDecisionCounter--;
			}
			timer = TIMERLIMIT;
		}
		
		if(!inAir && (jumpRepeatedly)) jump(500);
		//Gdx.app.log(Integer.toString(dangerLevel), null);
		//Gdx.app.log(Integer.toString(direction), Integer.toString(directionDecisionCounter));
		tryMove(delta);
		
	}
	public void render(SpriteBatch batch) {
		//---------------------------RENDER CODE---------------------------
		if(inAir) batch.draw(jumpRight.getKeyFrame(stateTime, true), pos.x, pos.y);
		else if(isCrushed) batch.draw(hurtRight.getKeyFrame(stateTime, true), pos.x, pos.y);
		else if(vel.x == 0) batch.draw(idleRight.getKeyFrame(stateTime, true), pos.x, pos.y);
		else if(vel.x != 0 && !isDashing) batch.draw(walkRight.getKeyFrame(stateTime, true), pos.x, pos.y);
		else if(vel.x != 0 && isDashing) batch.draw(runRight.getKeyFrame(stateTime, true), pos.x, pos.y);
		//else if(vel.x != 0 && !inAir && !isDashing) batch.draw(walkRight.getKeyFrame(stateTime, true), pos.x, pos.y);
		//else if(vel.x != 0 && !inAir && isDashing) batch.draw(runRight.getKeyFrame(stateTime, true), pos.x, pos.y); 
	}
	
	private void tryMove(float delta)
	{		
		boundingBox.x = boundingBox.x + vel.x*delta;
		boundingBox.y = boundingBox.y + vel.y*delta;
		
		if (boundingBox.y + boundingBox.height > floor) //floor collision
		{ 
			if (vel.y > 0) boundingBox.y = floor - boundingBox.height;
			vel.y = 0;
			if(inAir) land();
		}
		
		//trap collision
		if(level.trap_.boundingBox.y + 128 > boundingBox.y && !isCrushed)
		{
			if(underTrap2() && !isCrushed) //hit
			{
				vel.y = 1000;
				isCrushed = true;
				level.trap_.hitPlayer = true;
				acc.x = 0;
				vel.x = 0;
				hurt(5);
			}
			else if (underTrap() && !isCrushed) //miss
			{
				if(vel.x > 0) boundingBox.x = level.trap_.boundingBox.x - boundingBox.width;
				vel.x = 0;
			}
		}
		
		if(isCrushed && level.trap_.boundingBox.y + level.trap_.boundingBox.height + 128 < boundingBox.y)
		{
			isCrushed = false;
			acc.x = 100f;
			vel.x = 100f;
			jumpRepeatedly = false;
			isDashing = false;
			isPanicking = false;
		}
		
		pos.x = boundingBox.x;
		pos.y = boundingBox.y;
	}
	
	public boolean underTrap() //used to tell if player is positioned under the trap
	{
		if(boundingBox.x + boundingBox.width > level.trap_.boundingBox.x && boundingBox.x < level.trap_.boundingBox.x + level.trap_.boundingBox.width - 8)
			return true;
		else return false;
	}
	
	public boolean underTrap2() //used to tell if player is positioned under the trap
	{
		if(boundingBox.x + boundingBox.width > level.trap_.boundingBox.x + 8 && boundingBox.x < level.trap_.boundingBox.x + level.trap_.boundingBox.width - 4)
			return true;
		else return false;
	}
	
	public void hurt(float damage)
	{
		//hurt function
		Sounds.heroHurt.play();
		level.h.life--;
		level.h.anger++;
		dangerLevel++;
		jumpRepeatedly = false;
	}
	
	public void panic() //function if trap comes down too early
	{
		jumpRepeatedly = false;
		isPanicking = true;
		isDashing = true;
		vel.x = 0;
		jump(500);
		acc.x = 0;
	}
	
	public void jump(float strength) //jump function
	{
		vel.y = -strength;
		inAir = true;
		Sounds.heroJump.play();
	}
	
	public void land() //land function
	{
		inAir = false;
	}
	
	public void initAI() //sets initial conditions for AI
	{
		if(dangerLevel == 0) AILevel = 0;
		if(dangerLevel == 1) AILevel = 1;
		if(dangerLevel == 2) AILevel = AIrandomizer.nextInt(2) + 1;
		if(dangerLevel == 3) AILevel = 3;
		if(dangerLevel == 4) AILevel = AIrandomizer.nextInt(3) + 2;
		if(dangerLevel == 5) AILevel = AIrandomizer.nextInt(3) + 3;
		if(dangerLevel == 6) AILevel = AIrandomizer.nextInt(5) + 2;
		if(dangerLevel >= 7) AILevel = AIrandomizer.nextInt(7) + 1;
		
		switch(AILevel){
		case(0): //normal
			isDashing = false;
		break;
		case(1): //faster run
			isDashing=true;
			vel.x = XMAX*2;
			acc.x = 0;
		break;
		case(2): //stopping short once
			stopShort1 = true;
		break;
		case(3): //jumping repeatedly
			isDashing = false;
			inAir = true;
			jumpRepeatedly = true;
		break;
		case(4): //jumping repeatedly
			isDashing = false;
			inAir = true;
			jumpRepeatedly = true;
			stopShort1 = true;
		break;
		case(5): //runs/walks back and forth
			directionDecisionCounter = 2;
		break;
		case(6): //runs/walks back and forth
			directionDecisionCounter = AIrandomizer.nextInt(3) + 3;
		break;
		}
	}
	
	public void stopPoint1()
	{
		if(directionDecisionCounter > 0)
		{
			vel.x = 0;
			acc.x = 0;
			if(!refresh2)
			{
				direction = 0;
				timer = 25 + AIrandomizer.nextInt(100);
			}
			else if(!refresh1)
			{
				direction = 1;
				timer = 25 + AIrandomizer.nextInt(100);
			}
		}
		if(stopShort1)
		{
			vel.x = 0;
			acc.x = 0;
			stopShort1 = false;
			timer = 75 + AIrandomizer.nextInt(dangerLevel*50);
			runOnce = false;
		}
	}	
}
