package com.macse1.dungeon;

import java.util.ArrayList;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.graphics.g2d.Animation;
import com.badlogic.gdx.graphics.g2d.SpriteBatch;
import com.badlogic.gdx.graphics.g2d.TextureRegion;
import com.badlogic.gdx.math.Vector3;
import com.macse1.HeroData;
import com.macse1.resources.Art;
import com.macse1.tiles.Node;
import com.macse1.tiles.NodeEvaluator;
import com.macse1.tiles.Pathfinder;
import com.macse1.tiles.Tile;
import com.macse1.tiles.TileBoard;
import com.macse1.utils.Vec2i;

public class Hero implements NodeEvaluator {
	protected ArrayList<Vec2i> goals;
	public Vec2i pos = new Vec2i(0, 0);
	public int life;
	public int anger;
	
	public final int WALKING = 0, TURNING = 1;
	public int move_state = TURNING;
	public float move_percent = 0.f;
	
	public int UP = 0, RIGHT = 1, DOWN = 2, LEFT = 3;
	public Vec2i direction = new Vec2i(1, 0);
	
	public ArrayList<Vec2i> path;
	
	public int path_index = 0;
	protected int quickmod = 5000;
	protected int step = 0;
	
	public HeroData data= new HeroData();
	
	Animation forward;
	Animation backward;
	Animation left;
	Animation right;
	float state_time = 0.f;
	
	public Hero() {
		forward = new Animation(0.3f, Art.hero_f[0], Art.hero_f[1], Art.hero_f[2], Art.hero_f[3]);
		backward = new Animation(0.3f, Art.hero_b[0], Art.hero_b[1], Art.hero_b[2], Art.hero_b[3]);
		left = new Animation(0.3f, Art.hero_l[0], Art.hero_l[1], Art.hero_l[2], Art.hero_l[3]);
		right = new Animation(0.3f, Art.hero_r[0], Art.hero_r[1], Art.hero_r[2], Art.hero_r[3]);
	}
//	protected void insert(ArrayList<Vec2i> path, ArrayList<Vec2i>[] list) {
//		for (int i=0; i<list.size(); ++i) {
//			if (list.get(i)==null) {
//				list.add(i, path);
//			}
//			else if (list.get(i).size()>path.size()) {
//				ArrayList<Vec2i> temp = (ArrayList<Vec2i>)list.get(i).clone();
//				list.add(i, path);
//				int j = i;
//				while (j<list.size() && list.get(j)!=null) { ++j; }
//				for (; j>i; --j) {
//					list.add(list.get(j-1));
//				}
//				list.add(i+1, temp);
//			}
//		}
//	}
	public boolean pathfindGoal(TileBoard map) {
		ArrayList<Vec2i>[] paths = (ArrayList<Vec2i>[])new ArrayList[map.goals.size()];
//		for (int i=0; i<map.goals.size();++i) { paths = null; }
//		for (int i=0; i<map.goals.size();++i) {
//			
//			insert(Pathfinder.FindPath(map, map.start, map.goals.get(i), null), paths);
//		}
//		for (int i=0; i<paths.length; ++i) {
//			if (paths[i]!=null) {
//				path.addAll(paths[i]);
//			}
//		}\
		path = new ArrayList<Vec2i>();
		for (int i=0; i<map.goals.size();++i) {
			path.addAll(Pathfinder.FindPath(map, map.start, map.goals.get(i), null));
		}
		pos = map.start;
		//path = (Pathfinder.FindPath(map, map.start, map.goals.get(0), null));
		return true;
	}
	public void tick(float delta) {
		if (move_state==WALKING) {
			move_percent += delta;
			if (move_percent > 1.f) {
				move_percent = 0.f;
				pos = path.get(path_index);
				move_state = TURNING;
			}
		}
		else if (move_state==TURNING) {
			if (!(++path_index>path.size()-1)) {
				direction = path.get(path_index).cpy().sub(pos);
				move_state = WALKING;
			}
		}
		state_time += Gdx.graphics.getDeltaTime();
	}
	public void render(SpriteBatch batch, float delta) {
		TextureRegion tex = right.getKeyFrame(state_time, true);
		if (direction.x > 0) { tex = right.getKeyFrame(state_time, true); }
		else if (direction.x < 0) { tex = left.getKeyFrame(state_time, true); }
		else if (direction.y > 0) { tex = backward.getKeyFrame(state_time, true); }
		else if (direction.y < 0) { tex = forward.getKeyFrame(state_time, true); }
		batch.draw(tex, (pos.x+direction.x*move_percent)*Tile.WIDTH,
								  (pos.y+direction.y*move_percent)*Tile.WIDTH);
	}
	public float adjustNodeCost(Node node) {
		switch (node.get_type()) {
			case Tile.EMPTY:
				node.node_cost = 1.f;
				return node.node_cost;
			case Tile.SPIKE:
				node.node_cost = 5.f;
				return node.node_cost;
		}
		return 0;
	}
	public Vector3 getDrawPos() {
		return new Vector3((pos.x+direction.x*move_percent)*Tile.WIDTH, (pos.y+direction.y*move_percent)*Tile.WIDTH, 0);
	}
	
}
