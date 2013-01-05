package com.macse1.states;

import com.macse1.dungeon.LevelData;
import com.macse1.resources.Art;
import com.macse1.stateManagement.GameState;
import com.macse1.utils.MyMath;

public class LevelSelectMenuState extends GameState {

	public void tick(float delta) {
		
	}
	public void render(float delta) {
		batch_.disableBlending();
		batch_.begin();
			batch_.draw(Art.level_bg, 0, 0);
		batch_.end();
		
	}
	public boolean keyDown(int keycode) {
		
		return false;
	}

	
	public boolean keyUp(int keycode) {
		
		return false;
	}

	
	public boolean keyTyped(char character) {
		
		return false;
	}

	
	public boolean touchDown(int x, int y, int pointer, int button) {
		int width = 40, height = 30;
		int[] posx = new int[15];
		int[] posy = new int[15];
		
		posx[0] = 190;
		posx[1] = 190;
		posx[2] = 190;
		posx[3] = 236;
		posx[4] = 236;
		posx[5] = 236;
		posx[6] = 280;
		posx[7] = 280;
		posx[8] = 280;
		posx[9] = 328;
		posx[10] = 328;
		posx[11] = 328;
		posx[12] = 327;
		posx[13] = 327;
		posx[14] = 327;
		
		posy[0] = 42;
		posy[1] = 96;
		posy[2] = 150;
		posy[3] = 69;
		posy[4] = 123;
		posy[5] = 177;
		posy[6] = 42;
		posy[7] = 96;
		posy[8] = 150;
		posy[9] = 69;
		posy[10] = 123;
		posy[11] = 177;
		posy[12] = 42;
		posy[13] = 96;
		posy[14] = 150;
	
		
		DungeonState s = (DungeonState)(manager_.getGameState("SDungeon"));
		LevelData data;
		
		for (int i=0; i<15; ++i) {
			if (MyMath.pointInRect(x, y, posx[i], posy[i], posx[i]+width, posy[i]+height)) {
				data = LevelData.Level()[i];
				s.setLevel(data);
				enterTransition("TFadeC", "SDungeon");
				System.out.print(i+"\n");
			}
		}
		
		
		return false;
	}

	
	public boolean touchUp(int x, int y, int pointer, int button) {
		
		return false;
	}

	
	public boolean touchDragged(int x, int y, int pointer) {
		
		return false;
	}

	
	public boolean touchMoved(int x, int y) {
		
		return false;
	}

	
	public boolean scrolled(int amount) {
		
		return false;
	}


}
