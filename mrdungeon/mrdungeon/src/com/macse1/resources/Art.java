// Code based on Metagun's Art class
package com.macse1.resources;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.graphics.Pixmap;
import com.badlogic.gdx.graphics.Texture;
import com.badlogic.gdx.graphics.g2d.TextureRegion;
import com.macse1.tiles.Tile;

public class Art {
	public static TextureRegion[] hero_f;
	public static TextureRegion[] hero_b;
	public static TextureRegion[] hero_l;
	public static TextureRegion[] hero_r;
	
	public static TextureRegion main_menu_bg;
	public static TextureRegion level_bg;
	public static TextureRegion instructions;
	public static TextureRegion credits_bg;
	public static TextureRegion win;
	public static TextureRegion lose;
	
	public static TextureRegion blocking;
	public static TextureRegion place;
	
	
	public static TextureRegion black;
	public static TextureRegion tilegoal;
	public static TextureRegion[] tiles;
	public static TextureRegion interface_frame;
	public static TextureRegion[] interface_button;
	
	//NATHAN'S SPRITES
	public static TextureRegion playerMinigame[][];
	public static TextureRegion trapBaseballBat;
	public static TextureRegion trapMinigun;
	public static TextureRegion minigunBullets;
	public static TextureRegion miniBG1;
	public static TextureRegion miniBG2;
	
	public static Pixmap[] tilemap = new Pixmap[10];
	
	public static void load () {
		hero_f		= split_h("sprites/sprite_dungeon.png", 0, 42*4, 42, 42, 4, false);
		hero_b		= split_h("sprites/sprite_dungeon.png", 0, 42*2, 42, 42, 4, false);
		hero_l		= split_h("sprites/sprite_dungeon.png", 0, 42*3, 42, 42, 4, false);
		hero_r		= split_h("sprites/sprite_dungeon.png", 0, 42*3, 42, 42, 4, true);
		
		tiles		= split_h("sprites/sprite_dungeon.png", 0, 0, Tile.WIDTH, Tile.WIDTH, 11, false);
		interface_frame = load("sprites/interface.png", 480, 42);
		interface_button = split_h("sprites/interface.png", 0, 64, 32, 32, 4, false);
		
		main_menu_bg = load("sprites/menu_sprite.png", 0, 0, 480, 320);
		level_bg	= load("sprites/menu_sprite.png", 480, 0, 480, 320);
		instructions = load("sprites/menu_sprite.png", 0, 320, 480, 320);
		credits_bg = load("sprites/menu_sprite.png", 0, 480, 320, 320);
		win   = load("sprites/menu_sprite.png", 0, 640, 480 ,320);
		lose   = load("sprites/menu_sprite.png", 480, 0, 640, 320);
		
		blocking = load("sprites/menu_sprite.png", 0, 480*2, 400, -100);
		place = load("sprites/menu_sprite.png", 0, 480*2+32, 400, 32);
		
		//NATHAN'S SPRITES
		playerMinigame = split("sprites/playerMinigame.png", 32, 32);
		trapBaseballBat = load("sprites/baseballBat.png", 128, 512);
		trapMinigun = load("sprites/miniGun.png", 64, 64);
		minigunBullets = load("sprites/miniGunBullets.png", 8, 512);
		miniBG1 = load("sprites/miniBG1.png", 480, 320);
		miniBG2 = load("sprites/miniBG2.png", 480, 320);
		
		tilemap[0]		= new Pixmap(Gdx.files.internal("level/0.png"));
		tilemap[1]		= new Pixmap(Gdx.files.internal("level/1.png"));
		tilemap[2]		= new Pixmap(Gdx.files.internal("level/2.png"));
		tilemap[3]		= new Pixmap(Gdx.files.internal("level/3.png"));
		tilemap[4]		= new Pixmap(Gdx.files.internal("level/4.png"));
		tilemap[5]		= new Pixmap(Gdx.files.internal("level/5.png"));
		tilemap[6]		= new Pixmap(Gdx.files.internal("level/6.png"));
		tilemap[7]		= new Pixmap(Gdx.files.internal("level/7.png"));
		tilemap[8]		= new Pixmap(Gdx.files.internal("level/8.png"));
		tilemap[9]		= new Pixmap(Gdx.files.internal("level/9.png"));
		
		
	}
	private static TextureRegion[] split_h (String name, int x, int y, int width, int height, int count, boolean flipX) {
		Texture texture = new Texture(Gdx.files.internal(name));
		TextureRegion[] res = new TextureRegion[count];
		for (int i = 0; i < count; ++i) {
				res[i] = new TextureRegion(texture, x+i*width, y, width, height);
				res[i].flip(flipX, true);
		}
		return res;
	}
	private static TextureRegion[][] split (String name, int width, int height) {
		return split(name, width, height, true);
	}

	private static TextureRegion[][] split (String name, int width, int height, boolean flipX) {
		Texture texture = new Texture(Gdx.files.internal(name));
		int xSlices = texture.getWidth() / width;
		int ySlices = texture.getHeight() / height;
		TextureRegion[][] res = new TextureRegion[xSlices][ySlices];
		for (int x = 0; x < xSlices; x++) {
			for (int y = 0; y < ySlices; y++) {
				res[x][y] = new TextureRegion(texture, x * width, y * height, width, height);
				res[x][y].flip(false, true);
			}
		}
		return res;
	}


	public static TextureRegion load (String name, int width, int height) {
		Texture texture = new Texture(Gdx.files.internal(name));
		TextureRegion region = new TextureRegion(texture, 0, 0, width, height);
		region.flip(false, true);
		return region;
	}
	public static TextureRegion load (String name, int x, int y, int width, int height) {
		Texture texture = new Texture(Gdx.files.internal(name));
		TextureRegion region = new TextureRegion(texture, x, y, width, height);
		region.flip(false, true);
		return region;
	}
	public void dispose() {
	}
}