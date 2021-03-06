package com.macse1.stateManagement;

import java.util.HashMap;
import java.util.Stack;
import java.util.concurrent.ConcurrentSkipListMap;

import com.badlogic.gdx.graphics.FPSLogger;

public class StateManager {
	// Members
	protected Stack<SceneNode> states_ = new Stack<SceneNode>();
	protected HashMap<String, GameState> state_database_ = new HashMap<String, GameState>();
	protected HashMap<String, TransitionState> transition_database_ = new HashMap<String, TransitionState>();
	FPSLogger fps = new FPSLogger();
	
	// Methods
	public StateManager() {
		
	}
	public void init() {
		
	}
	
	// Database stuff
	public void registerGameState(String state_name, GameState state) {
		state.setName(state_name);
		state.setManager(this);
		state_database_.put(state_name, state);
	}
	public void registerTransitionState(String state_name, TransitionState state) {
		state.setName(state_name);
		state.setManager(this);
		transition_database_.put(state_name, state);
	}
	public SceneNode getGameState(String state_name) {
		return state_database_.get(state_name);
	}
	public SceneNode getTransitionState(String state_name) {
		return transition_database_.get(state_name);
	}
	
	// State management
	public void enterTransition(String trans_name, String new_state_name) {
		TransitionState transition 	= transition_database_.get(trans_name);
		GameState 		new_state	= state_database_.get(new_state_name);
		
		if (new_state!=null && !states_.isEmpty()) {
			transition.setTransition(states_.peek(), new_state);
			
			states_.push(transition);
			states_.peek().init();
		}
		
	}
	public void changeState(String state_name) {
		SceneNode state = state_database_.get(state_name);
		
		if (state!=null) {
			changeState(state);
		}
	}
	public void changeState(SceneNode state) {
		if (!states_.isEmpty()) {
			states_.peek().exit();
			states_.pop();
		}
		states_.push(state);
		states_.peek().init();
	}
	public void pushState(String state_name) {
		SceneNode state = state_database_.get(state_name);
		
		if (state!=null) {
			pushState(state);
		}
	}
	public void pushState(SceneNode state) {
		states_.push(state);
		states_.peek().init();
	}
	public void popState() {
		if (!states_.isEmpty()) {
			states_.peek().exit();
			states_.pop();
			if (!states_.isEmpty()) { states_.peek().resume(); }
		}
	}
	public void popSecond() {
		SceneNode s = states_.peek();
		states_.pop();
		states_.pop();
		states_.push(s);
	}
	
	// Update stuff
	public void tick(float delta) {
		if (!states_.isEmpty()) { states_.peek().tick(delta); }
	}
	public void render(float delta) {
		if (!states_.isEmpty()) { states_.peek().render(delta); }
		//fps.log();
	}
}
