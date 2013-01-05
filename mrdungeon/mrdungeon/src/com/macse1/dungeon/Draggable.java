package com.macse1.dungeon;

import java.util.ArrayList;

import com.badlogic.gdx.graphics.g2d.SpriteBatch;
import com.badlogic.gdx.graphics.g2d.TextureRegion;
import com.badlogic.gdx.math.Vector3;
import com.macse1.resources.Art;
import com.macse1.tiles.Pathfinder;
import com.macse1.tiles.Tile;
import com.macse1.tiles.TileBoard;
import com.macse1.utils.Vec2i;

public class Draggable {
		// Members
		public Vector3 pos = new Vector3();
		public static Vector3 off = new Vector3(-Tile.WIDTH/2, -Tile.WIDTH/2, 0);
		public int width=32, height=32;
		public Tile tile;
		protected TextureRegion texture;
		protected TileBoard map;
		
		public Draggable(Tile t, TileBoard m) {
			tile = t;
			map = m;
		}
		public void render(SpriteBatch batch) {
			TextureRegion tex;
			if (canDrop()) {
				tex = Art.tiles[9];
			}
			else { 
				tex = Art.tiles[10];
				ArrayList<Vec2i> conflict_regions = getConflictRegions();
				if (conflict_regions!=null) {
					for (int i=0; i<conflict_regions.size(); ++i) {
						batch.draw(tex, conflict_regions.get(i).x*Tile.WIDTH, conflict_regions.get(i).y*Tile.WIDTH);
					}
				}
			}
			
			for (int i=0; i<tile.region.size(); ++i) {
				Vec2i v = map.roundToTile(new Vec2i((int)pos.x, (int)pos.y)).add(tile.region.get(i));
				batch.draw(tex, v.x*Tile.WIDTH, v.y*Tile.WIDTH);
			}
			
			map.renderTile(batch, tile, (pos.x+off.x), (pos.y+off.y));
		}
		public boolean canDrop() {
			Vec2i tile_pos = new Vec2i((int)(pos.x/Tile.WIDTH), (int)(pos.y/Tile.WIDTH));
			tile.setPos(tile_pos);
			if (!map.withinBounds(tile_pos) || !map.isTileFree(tile_pos)) {
				return false;
			}
			Vec2i node;
			for (int i=0; i<tile.region.size(); ++i) {
				node = tile.getRegion(i);
				if (!map.isTileParentless(node) || !map.isTileFree(node)) { return false; }
				
			}

			return true;
		}
		public ArrayList<Vec2i> getConflictRegions() {
			Vec2i node;
			ArrayList<Vec2i> conflict = new ArrayList<Vec2i>();
			for (int i=0; i<tile.region.size(); ++i) {
				node = tile.getRegion(i);
				if (!map.isTileParentless(node)) {
					conflict = map.getConflictRegions(node);
					if (conflict.size()!=0) { return conflict; }
				}
			}
			return null;
		}
		public Vec2i getTilePos() {
			return map.roundToTile(new Vec2i((int)pos.x, (int)pos.y));
		}
		public void drop(TileBoard map) {
			
		}
	}

