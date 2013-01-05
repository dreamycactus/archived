package com.macse1.states;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.Input;
import com.badlogic.gdx.InputProcessor;
import com.badlogic.gdx.graphics.GL10;
import com.badlogic.gdx.graphics.g2d.SpriteBatch;
import com.badlogic.gdx.graphics.g2d.TextureRegion;
import com.badlogic.gdx.scenes.scene2d.actions.FadeIn;
import com.badlogic.gdx.math.Vector3;
import com.macse1.dungeon.Draggable;
import com.macse1.dungeon.DungeonInterface;
import com.macse1.dungeon.Hero;
import com.macse1.dungeon.LevelData;
import com.macse1.resources.Art;
import com.macse1.resources.Sounds;
import com.macse1.stateManagement.GameState;
import com.macse1.stateManagement.SceneNode;
import com.macse1.stateManagement.StateManager;
import com.macse1.tiles.Tile;
import com.macse1.tiles.TileBoard;
import com.macse1.utils.KineticCamera;
import com.macse1.utils.MyMath;
import com.macse1.utils.Vec2i;


public class DungeonState extends GameState {
	// Members
	private float delay			= 0.f;
	TileBoard map_;
	LevelData level;
	Hero hero_;
	DungeonInterface layer;
	Substate state;
	
	
	KineticCamera panner;
	
	Vector3 cam_old = new Vector3();
	
	Vector3 drag_pos = new Vector3();
	
	protected class DesignSubstate implements Substate {
		boolean panning = false, dragging = false;
		Vector3 cam_old_pos, cam_new_pos;
		Draggable dragged_tile;
		public boolean[][] map_diff;
		public final int pan_min = 17, stiff_pan_rate = 100;
		
		protected DesignSubstate() {
			cam_old_pos = new Vector3();
			cam_new_pos = new Vector3();
			map_diff = new boolean[map_.get_width()][map_.get_width()];
			for (int i=0; i<map_diff.length; ++i) {
				for (int j=0; j<map_diff[i].length; ++j) {
					map_diff[i][j] = false;
				}
			}
			panner.bound_top -= Art.interface_frame.getRegionHeight();
		}
		
		public void init() {
			
			
		}
		public void handleInput(float delta) {
			// Input 
			Vector3 pointer_pos = new Vector3(Gdx.input.getX(), Gdx.input.getY(), 0);
			cam_.unproject(pointer_pos);
			Vec2i pointed_tile = new Vec2i((int)pointer_pos.x/Tile.WIDTH, (int)pointer_pos.y/Tile.WIDTH);
			
			if (Gdx.input.isTouched()) {
				Vector3 delta_pos;
				if (layer.touchedButton()==1) { //speicfy confirm btton and execute new state
					if (map_.verifyLevel()) {
						map_.cacheMap();
						state = new ExecuteSubstate();
						return;
					}
					else {
						layer.printError(DungeonInterface.BLOCKING);
					}
				}
				else if (!dragging && !panning && map_.withinBounds(pointed_tile) && map_diff[pointed_tile.x][pointed_tile.y]) {
					// Removing an existing tile
					dragged_tile = new Draggable(map_.get(pointed_tile), map_);
					map_.removeAt(pointed_tile);
					Sounds.pick_tile.play();
					map_diff[pointed_tile.x][pointed_tile.y] = false;
					dragging = true;
	
				}
				else if (Gdx.input.getY()<GAME_HEIGHT+Art.interface_frame.getRegionHeight() && !dragging) {
					// Panning state
					if (!panning) { 
						cam_old_pos.x = Gdx.input.getX();
						cam_old_pos.y = Gdx.input.getY();
						panner.vel.mul(0.f);
						panning = true;
					}
					if (!dragging && panning) {
						cam_new_pos.x = Gdx.input.getX();
						cam_new_pos.y = Gdx.input.getY();
						delta_pos = cam_new_pos.cpy().sub(cam_old_pos);
						panner.vel.sub(delta_pos.mul(2));
						panner.pos.add(panner.vel.cpy().mul(delta));
						cam_old_pos = cam_new_pos.cpy();
						
						panning = true;
					}
				}
				else if (!panning) { // SPAWN NEW TILE
					Vector3 drag_pos = new Vector3(Gdx.input.getX(), Gdx.input.getY(), 0);
					if (!dragging) {
						int but = layer.touchedButton();
						switch (but) {
							case Tile.WALL:
								dragged_tile = new Draggable(new Tile(0, 0, Tile.WALL), map_);
								Sounds.pick_tile.play();
								--level.num_walls;
								break;
							case Tile.SPIKE:
								dragged_tile = new Draggable(new Tile(0, 0, Tile.SPIKE), map_);
								Sounds.pick_tile.play();
								--level.num_spikes;
								break;
							case Tile.GUN:
								dragged_tile = new Draggable(new Tile(0, 0, Tile.GUN), map_);
								Sounds.pick_tile.play();
								--level.num_turrets;
								break;
							case -1:
								break;
						}
						
					}
					if (dragged_tile!=null) {
						dragging = true;
						cam_.unproject(drag_pos);
						
						dragged_tile.pos = drag_pos.cpy();
						
						// Pan camera while dragging
						if (Gdx.input.getX()<pan_min) panner.pos.x -= delta*stiff_pan_rate;
						else if (Gdx.input.getX()>GAME_WIDTH-pan_min) panner.pos.x += delta*stiff_pan_rate;
						if (Gdx.input.getY()<pan_min) panner.pos.y -= delta*stiff_pan_rate;
						else if (Gdx.input.getY()>GAME_HEIGHT-pan_min) panner.pos.y += delta*stiff_pan_rate;
					}
				}
		}
		else {
			if (dragging && dragged_tile.canDrop()) {
				if (map_.withinBounds(dragged_tile.getTilePos())) {
					dragged_tile.tile.setPos(dragged_tile.getTilePos());
					map_.replace(dragged_tile.tile);
					map_diff[dragged_tile.getTilePos().x][dragged_tile.getTilePos().y] = true;
					Sounds.drop_tile.play();
				}
			}
			panning = dragging = false;
			dragged_tile = null;
		}
	}
		
		public void tick(float delta) {
			handleInput(delta);
			panner.tick(delta);
			cam_.position.set(panner.pos);
			cam_.update();
			
		}
		
		public void render(float delta) {
			for (int i=0; i<map_diff.length; ++i) {
				for (int j=0; j<map_diff[i].length; ++j) {
					if (map_diff[i][j]) map_.renderTile(batch_, i, j);
				}
			}
			if (dragged_tile!=null) {
				dragged_tile.render(batch_);
			}
			layer.render(delta, batch_);
			
		}
	}
	
	protected class ExecuteSubstate implements Substate {
		boolean inited = false;
		public ExecuteSubstate() {
			hero_ = new Hero();
			hero_.pathfindGoal(map_);
			hero_.life = level.hp;
			panner.bound_top += Art.interface_frame.getRegionHeight();
			inited = true;
		}
		public void init() {
			
		}

		Vector3 lerp_target = new Vector3();
		public void tick(float delta) {
			hero_.tick(delta);
			cam_.position.lerp(lerp_target.set(hero_.getDrawPos().x, hero_.getDrawPos().y, 0), 1.5f * delta);
			map_.checkHero(hero_);
			if (hero_.data.life<=0) {
				enterTransition("TFadeC", "SGameover");
			}
			
		}

		
		public void render(float delta) {
			if (!inited) return;
			hero_.render(batch_, delta);
		}
		
	}
	// Methods
	public DungeonState() {
		super();
	}
	public void setHero(Hero h) {
		hero_.life = h.life;
		hero_.anger = h.anger;
	}
	public void setLevel(LevelData data) {
		level = data;
		setupGraphics();
		
		map_ = new TileBoard(data.pixmap, this);
		panner = new KineticCamera(cam_.position.x, cam_.position.y, 
								   cam_.position.x+map_.get_width()*Tile.WIDTH, cam_.position.y+map_.get_height()*Tile.WIDTH,
								   GAME_WIDTH, GAME_HEIGHT);
		layer = new DungeonInterface(this, level);
		Gdx.input.setInputProcessor(this);
		active_ = true;
		panner.pos = cam_.position;
//		state = new ExecuteSubstate();
		state = new DesignSubstate();
	}
	public void init() {
		setupGraphics();
		Sounds.s1.play();
		Sounds.s2.stop();
		Sounds.s3.stop();
	}
	
	public void tick(float delta) {
		
		state.tick(delta);
		cam_.update();
		
	}
	public void render(float delta) {
		
		batch_.setProjectionMatrix(cam_.combined);
		
		map_.render(delta, cam_, panner.vel);
		
		batch_.begin();

		state.render(delta);
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
//		enterTransition("TFade", "SMiniGame1");
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
