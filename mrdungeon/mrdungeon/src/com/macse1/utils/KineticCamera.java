package com.macse1.utils;

import com.badlogic.gdx.math.Vector3;

public class KineticCamera {
	public Vector3 pos = new Vector3();
	public Vector3 vel = new Vector3(0, 0, 0);
	public float width, height;
	public float pan_vel	   = 1020.f;
	public float drift_vel	   = 2.f;
	public float max_vel	   = 900.f;
	public float threshold_vel = 0.0001f;
	public float friction	   = .1f;
	public float bounce_friction = 0.03f;
	
	public float bound_left 	= 0.f;
	public float bound_right	= 0.f;
	public float bound_top		= 0.f;
	public float bound_bottom 	= 0.f;
	
	public KineticCamera(float left, float bottom, float right, float top, float w, float h) {
		bound_left = left;
		bound_right = right;
		bound_top = top;
		bound_bottom = bottom;
		width = w;
		height = h;
	}
	public KineticCamera() {
	}
	public void tick(float delta) {
		float len = vel.len();
		
		//vel.mul((float)Math.pow(friction, delta/3.0));
		
		vel.x = MyMath.clamp(vel.x, -max_vel, max_vel);
		vel.y = MyMath.clamp(vel.y, -max_vel, max_vel);

		pos.add(vel.cpy().mul(delta));
		
		if (pos.x < bound_left) { 
			pos.x = bound_left;
			vel.x = -vel.x*bounce_friction;
		}
		else if (pos.x+width > bound_right) { 
			pos.x = bound_right-width;
			vel.x = -vel.x*bounce_friction;
		}
		if (pos.y < bound_bottom) { 
			pos.y = bound_bottom;
			vel.y = -vel.y*bounce_friction;
		}
		else if (pos.y+height > bound_top) { 
			pos.y = bound_top-height;
			vel.y = -vel.y*bounce_friction;
		}
		
		
		
	}
	
}
