package com.macse1;

import com.badlogic.gdx.ApplicationListener;
import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.graphics.GL10;
import com.badlogic.gdx.graphics.OrthographicCamera;
import com.macse1.dungeon.LevelData;
import com.macse1.gameBaseballBat.GameBaseballBat;
import com.macse1.gameMinigun.GameMinigun;
import com.macse1.resources.Art;
import com.macse1.resources.Sounds;
import com.macse1.stateManagement.GameState;
import com.macse1.stateManagement.StateManager;
import com.macse1.states.DungeonState;
import com.macse1.states.InstructionState;
import com.macse1.states.LevelSelectMenuState;
import com.macse1.states.LoseState;
import com.macse1.states.MainMenuState;
import com.macse1.states.SlidingFadeTransition;
import com.macse1.states.MiniGame1State;
import com.macse1.states.SlidingFadeTransitionC;
import com.macse1.states.SlidingFadeTransitionP;
import com.macse1.states.WinState;
import com.macse1.tiles.Node;
import com.macse1.tiles.Pathfinder;
import com.macse1.tiles.TileBoard;
import com.macse1.utils.Vec2i;

public class Game implements ApplicationListener {
	//Methods
	
	
	private StateManager state_manager_;
	
	public void create() {
		Art.load();
		Sounds.load();
		state_manager_ = new StateManager();
		state_manager_.registerGameState("SDungeon", new DungeonState());
		state_manager_.registerGameState("SMain", new MainMenuState());
		state_manager_.registerGameState("SBaseballBat", new GameBaseballBat());
		state_manager_.registerGameState("SMinigun", new GameMinigun());
		state_manager_.registerGameState("SLevelSelect", new LevelSelectMenuState());
		state_manager_.registerGameState("SInstruct", new InstructionState());
		state_manager_.registerGameState("SWin", new WinState());
		state_manager_.registerGameState("SLose", new LoseState());
		
		
		state_manager_.registerTransitionState("TFade", new SlidingFadeTransition());
		state_manager_.registerTransitionState("TFadeC", new SlidingFadeTransitionC());
		state_manager_.registerTransitionState("TFadeP", new SlidingFadeTransitionP());
		
		
		state_manager_.pushState("SMain");
		
	}

	
	public void resume() {
		// TODO Auto-generated method stub
		
	}

	static final float FPS = 0.06f; // Misnomer. Actually more like spf... 
	float delta = 0.f;
	
	public void render() {
		Gdx.gl.glClear(GL10.GL_COLOR_BUFFER_BIT);
		//System.out.print(Gdx.graphics.getFramesPerSecond()+"\n");
		delta = Math.min(Gdx.graphics.getDeltaTime(), FPS);
		
		state_manager_.tick(delta);
		state_manager_.render(delta);
	}

	
	public void resize(int width, int height) {
		// TODO Auto-generated method stub
		
	}

	
	public void pause() {
		// TODO Auto-generated method stub
		
	}

	
	public void dispose() {
		// TODO Auto-generated method stub
		
	}

}
