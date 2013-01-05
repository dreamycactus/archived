package com.macse1.tiles;

import java.util.ArrayList;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.audio.Sound;
import com.badlogic.gdx.graphics.GL10;
import com.badlogic.gdx.graphics.OrthographicCamera;
import com.badlogic.gdx.graphics.Pixmap;
import com.badlogic.gdx.graphics.g2d.SpriteBatch;
import com.badlogic.gdx.graphics.g2d.SpriteCache;
import com.badlogic.gdx.graphics.g2d.TextureRegion;
import com.badlogic.gdx.math.Vector3;
import com.macse1.dungeon.Hero;
import com.macse1.gameBaseballBat.GameBaseballBat;
import com.macse1.resources.Art;
import com.macse1.resources.Sounds;
import com.macse1.stateManagement.SceneNode;
import com.macse1.states.DungeonState;
import com.macse1.utils.MyMath;
import com.macse1.utils.Vec2i;

public class TileBoard {
	// Members
	public 	  Tile[][] map_;
	protected int draw_x_, draw_y_;
	protected int width_, height_;
	protected SpriteCache cache_;
	protected int[][] cache_id_;
	int cache_x, cache_y;
	
	protected final int MINI_WIDTH = 4;
	protected DungeonState level;
	
	protected int mini_cache_id_;
	public ArrayList<Vec2i> goals = new ArrayList<Vec2i>();
	public Vec2i start;
	
	// Methods
	public TileBoard(Pixmap pixmap, DungeonState l){
		width_ 	= pixmap.getWidth();
		height_ = pixmap.getHeight();
		map_ 	= new Tile[width_][height_];
		cache_ = new SpriteCache(width_*height_, false);
		level = l;
		
		for (int x=0; x<width_; ++x) {
			for (int y=0; y<height_; ++y) {
				int col = pixmap.getPixel(x, height_-y-1) >>> 8;
				switch (col) {
					case Tile.EMPTY:
						map_[x][y] = new Tile(x, y, Tile.EMPTY);
						break;
					case Tile.SPIKE:
						map_[x][y] = new Tile(x, y, Tile.SPIKE);
						replace(map_[x][y]);
						break;
					case Tile.WALL:
						map_[x][y] = new Tile(x, y, Tile.WALL);
						break;
					case Tile.START:
						map_[x][y] = new Tile(x, y, Tile.START);
						start = new Vec2i(x, y);
						break;
					case Tile.GOAL:
						map_[x][y] = new Tile(x, y, Tile.GOAL);
						goals.add(new Vec2i(x, y));
						replace(map_[x][y]);
						break;
				}
			}
		}
		//cache_id_ = new int[width_*Tile.WIDTH/SceneNode.GAME_WIDTH + 1][height_*Tile.WIDTH/SceneNode.GAME_HEIGHT + 1];
		cache_x = (int)Math.ceil((float)(width_*Tile.WIDTH) / (float)SceneNode.GAME_WIDTH);
		cache_y = (int)Math.ceil((float)(height_*Tile.WIDTH) / (float)SceneNode.GAME_HEIGHT);

		cache_id_ = new int[cache_x][cache_y];
		cacheMap();
		
		
	}
	public void cacheMap() {
		cache_.clear();
		int tiles_per_screen_x = (int)Math.ceil((float)SceneNode.GAME_WIDTH  / (float)Tile.WIDTH);
		int	tiles_per_screen_y = (int)Math.ceil((float)SceneNode.GAME_HEIGHT / (float)Tile.WIDTH);
		
		for (int cx=0; cx<cache_id_.length; ++cx) {
			for (int cy=0; cy<cache_id_[cx].length; ++cy) {
				cache_.beginCache();
				for (int x=cx*tiles_per_screen_x; x<(cx+1)*tiles_per_screen_x; ++x) {
					for (int y=cy*tiles_per_screen_y; y<(cy+1)*tiles_per_screen_y; ++y) {
						if (x>width_-1) 	{ continue; }
						if (y>height_-1) 	{ continue; }
						switch(map_[x][y].type_) {
							case Tile.EMPTY:
								cache_.add(Art.tiles[0], (float)x*Tile.WIDTH, (float)y*Tile.WIDTH, (float)Tile.WIDTH, (float)Tile.WIDTH);
								break;
							case Tile.SPIKE:
								cache_.add(Art.tiles[2], (float)x*Tile.WIDTH, (float)y*Tile.WIDTH, (float)Tile.WIDTH, (float)Tile.WIDTH);
								break;
							case Tile.START:
								cache_.add(Art.tiles[4], (float)x*Tile.WIDTH, (float)y*Tile.WIDTH, (float)Tile.WIDTH, (float)Tile.WIDTH);
								break;
							case Tile.WALL:
								cache_.add(Art.tiles[6], (float)x*Tile.WIDTH, (float)y*Tile.WIDTH, (float)Tile.WIDTH, (float)Tile.WIDTH);
								break;
							case Tile.GOAL:
								cache_.add(Art.tiles[8], (float)x*Tile.WIDTH, (float)y*Tile.WIDTH, (float)Tile.WIDTH, (float)Tile.WIDTH);
								break;
						}
					}
				}
				cache_id_[cx][cy] = cache_.endCache();
				
			}
		}
	}
	public void checkHero(Hero hero) {
		Tile trigger = get(hero.pos).parent_;
		
		if (trigger == null) { return; }
		else {
			switch(trigger.type_) {
				case Tile.SPIKE:
					GameBaseballBat s = (GameBaseballBat)(level.manager_.getGameState("SBaseballBat"));
					s.setHero(hero);
					level.enterTransition("TFade", "SBaseballBat");
					hero.pos = hero.path.get(++hero.path_index);
					Sounds.trap_trigger.play();
					break;
				case Tile.GUN:
					level.enterTransition("TFade", "SMinigun");
					break;
				case Tile.GOAL:
					level.enterTransition("TFade", "SLose");
					break;
			}
		}
	}
	public Node[] FindAdjacentTiles(Vec2i node) {		
		Node adjacent_nodes[] = new Node[4];
		Vec2i m;
		
		m = new Vec2i(node.x-1, node.y); 		// Left
		if (withinBounds(m)) 	{ adjacent_nodes[0] = new Node(m, map_[m.x][m.y].getType()); }
		else					{ adjacent_nodes[0] = null;	}

		m = new Vec2i(node.x+1, node.y);							// Right
		if (withinBounds(m)) 	{ adjacent_nodes[1] = new Node(m, map_[m.x][m.y].getType()); }
		else					{ adjacent_nodes[1] = null;	}
		
		m = new Vec2i(node.x, node.y-1);				// Up
		if (withinBounds(m)) 	{ adjacent_nodes[2] = new Node(m, map_[m.x][m.y].getType()); }
		else					{ adjacent_nodes[2] = null;	}
		
		m = new Vec2i(node.x, node.y+1);							// Down
		if (withinBounds(m)) 	{ adjacent_nodes[3] = new Node(m, map_[m.x][m.y].getType()); }
		else					{ adjacent_nodes[3] = null;	}
		
		return adjacent_nodes;
				
	}
	public boolean withinBounds(Vec2i node) {
		return (node.x >= 0 && node.x < width_ && node.y >= 0 && node.y < height_);
	}
	public boolean isTileParentless(Vec2i v) {
		if (!withinBounds(v)) return true;
		return (get(v).parent_==null);
	}
	public ArrayList<Vec2i> getConflictRegions(Vec2i v) {
		if (!withinBounds(v)) { return null; }
		if (get(v).parent_!=null) {
			Tile conflict_tile = get(v).parent_;
			ArrayList<Vec2i> conflicting_regions = new ArrayList<Vec2i>();;
			for (int i=0; i<conflict_tile.region.size(); ++i) {
				conflicting_regions.add(conflict_tile.getRegion(i));
			}
			return conflicting_regions;
		}
		return null;
	}
	public boolean verifyLevel() {
		for (int i=0; i<goals.size(); ++i) {
			if (Pathfinder.FindPath(this, start, goals.get(i), null)==null) {
				return false;
			}
		}
		return true;
	}
	public boolean isTileFree(Vec2i v) {
		if (!withinBounds(v)) return true;
		return (get(v).type_ == Tile.EMPTY);
	}
	public void replace(Tile tile) {
		Vec2i pos;
		
		map_[tile.pos_.x][tile.pos_.y] = tile;
		for (int i=0; i<tile.region.size(); ++i) {
			pos = tile.getRegion(i);
			if (withinBounds(pos)) {
				map_[pos.x][pos.y].parent_ = tile;
			}
		}
	}
	public void removeAt(Vec2i v) {
		
		for (int i=0; i<map_[v.x][v.y].region.size(); ++i) {
			Vec2i rv = map_[v.x][v.y].getRegion(i);
			if (!withinBounds(rv)) { continue; }
			map_[rv.x][rv.y].parent_ = null; 
		}
		map_[v.x][v.y] = new Tile(v.x, v.y, Tile.EMPTY);
		
	}
	final int correct = 100;
	public void render(float delta, OrthographicCamera cam, Vector3 vel) {
		cache_.setProjectionMatrix(cam.combined);
		Gdx.gl.glDisable(GL10.GL_BLEND);
		
		Vector3 pos = cam.position.cpy();
		pos.x -= SceneNode.GAME_WIDTH/2.f+correct;
		pos.y -= SceneNode.GAME_HEIGHT/2.f+correct;

		Vector3 temp_cam = cam.position.cpy();
		cache_.begin();
		int p = 0;
		for (int x=0; x<cache_id_.length; ++x) {
			for (int y=0; y<cache_id_[x].length; ++y) {
				if (MyMath.rectangleIntersect((int)pos.x, (int)pos.y, (int)pos.x+SceneNode.GAME_WIDTH+2*correct, (int)pos.y+SceneNode.GAME_HEIGHT+2*correct,
										x*SceneNode.GAME_WIDTH, y*SceneNode.GAME_HEIGHT, (x+1)*SceneNode.GAME_WIDTH, (y+1)*SceneNode.GAME_HEIGHT )) {
					cache_.draw(cache_id_[x][y]);
				}
				
			}
		}
		cache_.end();
		
	}
	public void renderTile(SpriteBatch batch, Tile tile, float x, float y) {
		TextureRegion tex;
		
		switch(tile.type_) {
			case Tile.EMPTY:
				tex = Art.tiles[0];
				break;
			case Tile.WALL:
				tex = Art.tiles[6];
				break;
			case Tile.SPIKE:
				tex = Art.tiles[2];
				break;
			case Tile.GOAL:
				tex = Art.tiles[8];
				break;
			case Tile.START:
				tex = Art.tiles[4];
				break;
			case Tile.GUN:
				tex = Art.tiles[4];
				break;
			default:
				tex = Art.tiles[4];
				break;
		}
		batch.draw(tex, x, y);
	}
	public void renderTile(SpriteBatch batch, int x, int y) {
		renderTile(batch, map_[x][y], x*Tile.WIDTH, y*Tile.WIDTH);
	}
	public void renderMinimap(OrthographicCamera cam) {
		cam.position.x -= 50;
		cam.position.y -= 50;
		cam.update();
		cache_.setProjectionMatrix(cam.combined);
		cache_.begin();
		cache_.draw(mini_cache_id_);
		cache_.end();
		cam.position.x += 50;
		cam.position.y += 50;
		cam.update();
	}
	public Tile get(int r, int c) 		{ return map_[r][c]; }
	public Tile get(Vec2i m) 			{ return map_[m.x][m.y]; }
	public Vec2i roundToTile(Vec2i v)	{ return new Vec2i((int)(v.x/Tile.WIDTH), (int)(v.y/Tile.WIDTH)); }
	public int get_width() 				{ return width_; }
	public int get_height() 			{ return height_; }
	
	public void dispose () {
		cache_.dispose();
	}
		
}
