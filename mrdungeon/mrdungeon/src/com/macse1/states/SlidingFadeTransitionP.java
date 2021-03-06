package com.macse1.states;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.graphics.Color;
import com.badlogic.gdx.graphics.GL10;
import com.badlogic.gdx.graphics.Mesh;
import com.badlogic.gdx.graphics.OrthographicCamera;
import com.badlogic.gdx.graphics.Pixmap;
import com.badlogic.gdx.graphics.Texture;
import com.badlogic.gdx.graphics.VertexAttribute;
import com.badlogic.gdx.graphics.VertexAttributes.Usage;
import com.badlogic.gdx.graphics.g2d.Sprite;
import com.badlogic.gdx.graphics.g2d.TextureRegion;
import com.badlogic.gdx.math.Vector3;
import com.macse1.resources.Art;
import com.macse1.stateManagement.TransitionState;

public class SlidingFadeTransitionP extends TransitionState {
	// Members
	private Sprite blackie_;
    private float alpha_;
    private final double STEP_TRANS = -0.3f;
    private final float SLIDE_K = 500.8f;
    private float STEP_ALPHA;
    
	private boolean old_state_done_;
	private boolean new_state_done_;
	private double	transition_percent_;
	private float 	screen_offset_;
	
	private Vector3 origin_;
	
	public void init() {
		setupGraphics();
		Gdx.input.setInputProcessor(null);
		new_state_.init();
		Texture temp 		= new Texture(512, 512, Pixmap.Format.RGB565);
		blackie_ 			= new Sprite(temp);
		alpha_ 				= 0.f;
		old_state_done_ 	= false;
		new_state_done_ 	= true;
		transition_percent_ = 1.f;
		origin_				= old_state_.getCamera().position.cpy();
		screen_offset_ 		= origin_.x;
		STEP_ALPHA			= 0.7f;
	}
	public void tick(float delta) {
		OrthographicCamera cam = old_state_.getCamera();
		
		if (!old_state_done_) {
    			if (cam.position.x > origin_.x+GAME_WIDTH || transition_percent_ <= 0.) {
    				old_state_done_		= true;
    				cam 				= new_state_.getCamera();
    				cam.position.x 		-= GAME_WIDTH;
    				origin_ 			= cam.position.cpy();
    				screen_offset_ 		= origin_.x;
    				System.out.print(transition_percent_);
    				transition_percent_ = 1.f;
    				STEP_ALPHA 			*= -1.f;
    				new_state_done_		= false;
    				manager_.popSecond();
    			}
  		}
		else if (!new_state_done_){
			cam = new_state_.getCamera();
  			if (cam.position.x > origin_.x+GAME_WIDTH) {
  				cam.position.x = origin_.x-GAME_WIDTH;
  				new_state_done_ = true;
  				manager_.popState();
  				new_state_.init();
  			}
		}
		
  		
		if (!old_state_done_ || !new_state_done_) {
			screen_offset_ += Math.pow(transition_percent_, 2.0)*SLIDE_K*delta;
	  		cam.position.set(screen_offset_, origin_.y, origin_.z);
	  		cam.update();
	  		
			alpha_ 				+= STEP_ALPHA*delta;
			transition_percent_ += STEP_TRANS*delta;
			
			if (transition_percent_<0.) { transition_percent_ = 0.; }
			if (alpha_<0.f)		 { alpha_ = 0.f; }
			else if (alpha_>1.f) { alpha_ = 1.f; }
		}
	}
	
	
	public void render(float delta) {
		if (!old_state_done_) {
			old_state_.render(delta);
		}
		else {
			new_state_.render(delta);
		}
		
		
		batch_.begin();
			blackie_.draw(batch_, alpha_);
		batch_.end();
		
	}
	

}
