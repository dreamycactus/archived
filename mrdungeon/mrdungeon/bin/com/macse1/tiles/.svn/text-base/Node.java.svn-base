package com.macse1.tiles;

import com.macse1.tiles.Tile;
import com.macse1.utils.Vec2i;

public class Node {
	// Members
	public static final int START = 0, FINISH = 1, WALL = 2;
	public float node_cost = 1.f;
	
	private				Node parent_ = null;
	private				Vec2i pos_;
	private 			int type_ = Tile.EMPTY;
	private transient 	float current_cost_ = node_cost;
	
	// Methods
	public Node() { Init(); }
	public Node(int x, int y, int type) {
		Init();
		pos_ = new Vec2i(x, y);
		type_ = type;
	}
	public Node(Vec2i pos, int type) { 
		Init();
		pos_  = new Vec2i(pos);
		type_ = type;
	}
	public Node(Node o) {
		if (o.parent_!=null) {
			parent_ 		= o.parent_;
		}
		pos_ 			= o.pos_;
		type_ 			= o.type_;
		current_cost_ 	= o.current_cost_;
		node_cost		= o.node_cost;
	}
	private void Init() { 
		pos_ 	= new Vec2i();
	}
	
	public boolean equals(Object o) {
		// Considered equal if they occupy same space
		Node ob = (Node)o;
		return pos_.equals(ob.pos_);
	}
	public void set_current_cost(float cost) {
			current_cost_ += cost;
	}
	
	// Getters
	public Vec2i 	get_pos() 					{ return pos_; }
	public int 		get_type() 					{ return type_; }
	public float 	get_current_cost()		 	{ return current_cost_; }
	public Node  	get_parent() 				{ return parent_; }
	
	// Setters
	public void set_pos(Vec2i p) 	{ pos_ = new Vec2i(p); }
	public void set_parent(Node pa) { parent_ = pa; }
	
}
