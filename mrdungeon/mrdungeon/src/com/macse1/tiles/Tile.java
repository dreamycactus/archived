package com.macse1.tiles;

import java.util.ArrayList;

import com.badlogic.gdx.graphics.g2d.SpriteBatch;
import com.macse1.resources.Art;
import com.macse1.utils.Vec2i;

public class Tile {
	// Members
	public static final int EMPTY 		= 0xffffff;
	public static final int WALL 		= 0x000000;
	public static final int GOAL 		= 0xff0000;
	public static final int START 		= 0xff00ff;
	public static final int GUN 		= 0xff0100;
	public static final int SPIKE	 	= 0x00ff00;
	
	public static final int WIDTH = 42;
	
	protected Vec2i 	pos_ 		= Vec2i.Zero; // This is grid position. x and y are reversed
	protected boolean 	isSolid_ 	= false;
	protected int		type_;
	protected Tile		parent_		= null;
	public ArrayList<Vec2i> region = new ArrayList<Vec2i>();
	
	// Methods
	public Tile(int type) { type_ = type; }
	public Tile(int x, int y, int type) {
		pos_ = new Vec2i(x, y);
		type_ = type;
		region.add(new Vec2i(0,0)); // remove this later
	}

	
	// Getter & Setter
	public boolean isSolid() 		{ return isSolid_; }
	public void setSolid(boolean s) { isSolid_ = s; }
	public Vec2i getPos()			{ return pos_; }
	public void setPos(Vec2i p)		{ pos_ = new Vec2i(p); }
	public int getType()			{ return type_; }
	public void setParent(Tile p)	{ parent_ = p; }
	public Tile getParent()			{ return parent_; }
	public Vec2i getRegion(int i) 	{ return pos_.cpy().add(region.get(i)); }
	
}
