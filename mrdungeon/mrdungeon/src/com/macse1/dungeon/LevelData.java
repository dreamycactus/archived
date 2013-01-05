package com.macse1.dungeon;

import com.badlogic.gdx.graphics.Pixmap;
import com.macse1.resources.Art;

public class LevelData {
	public LevelData(int s, int g, int w, int h, Pixmap p) {
		num_spikes = s;
		num_turrets = g;
		num_walls = w;
		hp = h;
		pixmap = p;
	}
	public LevelData() {};
	public static LevelData[] Level() {
		LevelData level[] = new LevelData[10];
		level[0] = new LevelData(0, 0, 0, 1, Art.tilemap[0]);
		level[1] = new LevelData(0, 0, 8, 4, Art.tilemap[1]);
		level[2] = new LevelData(3, 0, 4, 3, Art.tilemap[2]);
		level[3] = new LevelData(0, 0, 17, 4, Art.tilemap[3]);
		level[4] = new LevelData(4, 0, 6, 30, Art.tilemap[4]);
		level[5] = new LevelData(80, 0, 10, 8, Art.tilemap[5]);
		level[6] = new LevelData(20, 0, 12, 20, Art.tilemap[6]);
		level[7] = new LevelData(40, 0, 13, 36, Art.tilemap[7]);
		level[8] = new LevelData(10, 0, 4, 10, Art.tilemap[8]);
		level[9] = new LevelData(7, 0, 5, 7, Art.tilemap[9]);
		
		return level;
	}
	public int num_spikes = 2, num_turrets = 0, num_walls = 3;
	public int hp;
	public Pixmap pixmap;
}
