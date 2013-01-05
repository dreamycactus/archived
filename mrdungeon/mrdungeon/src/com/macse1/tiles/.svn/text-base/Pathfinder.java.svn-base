// Code based on work done by James Macgill
package com.macse1.tiles;

import java.util.ArrayList;
import java.util.Collections;

import com.macse1.tiles.Tile;
import com.macse1.utils.Vec2i;


public class Pathfinder {
	// Members
	static final int WIDTH  = 10;
	static final int HEIGHT = 10;
	
	protected static ArrayList<Node> open_list;
    protected static ArrayList<Node> closed_list;
    protected static float min_cost = 1.0f;
	
	// Methods
	public static ArrayList<Vec2i> FindPath(TileBoard map, Vec2i src, Vec2i dst, NodeEvaluator evaluator) {
		float min = Float.MAX_VALUE;
		float score;
		Node start_node = new Node(src, Tile.EMPTY);
		Node end_node = new Node(dst, Tile.GOAL);
		
		open_list   = new ArrayList<Node>();
		closed_list = new ArrayList<Node>();
		
		start_node.set_parent(null);
		open_list.add(start_node);
		Node best;
		Node current;
		
		while (!open_list.isEmpty()) {
			best = (Node)open_list.get(open_list.size()-1);
			for (int i=0; i<open_list.size(); ++i) {
				current = (Node)open_list.get(i);
				if (!closed_list.contains(current)) {
					score = current.get_current_cost();
					score += cb_dist(current.get_pos(), end_node.get_pos(), min_cost);
					if (score<min) {
						min = score;
						best = current;
					}
				}
			}
			current = best;
			open_list.remove(current);
			closed_list.add(current);
			Node adjacent[] = map.FindAdjacentTiles(current.get_pos());
			for (int i=0; i<4; ++i) {
				if (adjacent[i]!=null) {
					if (evaluator!=null) { evaluator.adjustNodeCost(adjacent[i]); } // Allows different ratings for tiles
					if (adjacent[i].equals(end_node)) {
						adjacent[i].set_parent(current);
						end_node = adjacent[i];
						return BuildPath(start_node, end_node);
					}
					else { adjacent[i].set_parent(current); }
					
					if (adjacent[i].get_type()!=Tile.WALL) {
						if (current.get_current_cost() + adjacent[i].node_cost < adjacent[i].get_current_cost()) {
							adjacent[i].set_current_cost(current.get_current_cost());
							adjacent[i].set_parent(current);
						}
						if (!open_list.contains(adjacent[i]) && !closed_list.contains(adjacent[i])) {
							open_list.add(adjacent[i]);
						}
					}
				}
			}
		}
		System.out.println("NOPATH");
		return null;
	}
	protected static ArrayList<Vec2i> BuildPath(Node src, Node dst) {
		System.out.println("BUIDINGPATH");
		ArrayList<Vec2i> path = new ArrayList<Vec2i>();
		Node temp = dst;
		path.add(dst.get_pos());
		while (true) {
			System.out.println(temp.get_pos());
			temp = temp.get_parent();
			path.add(temp.get_pos());
			if (temp==src) break;
		}
		Collections.reverse(path);
		return path;
		
	}
	protected static float cb_dist(Vec2i a,Vec2i b, float low){
        return low * (Math.abs(a.x-b.x) + Math.abs(a.y-b.y) - 1);
    }
	
		
}

