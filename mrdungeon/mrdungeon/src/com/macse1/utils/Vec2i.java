package com.macse1.utils;

public class Vec2i {
	public int x, y;
	
	public static final Vec2i Zero = new Vec2i(0, 0);
	public Vec2i() {
		x = 0;
		y = 0;
	}
	public Vec2i(int x0, int y0) {
		x = x0;
		y = y0;
	}
	public Vec2i(Vec2i o) {
		this.x = o.x;
		this.y = o.y;
	}
	public boolean equals(Object o) {
		Vec2i ob = (Vec2i)o;
		return (ob.x == x && ob.y == y);
	}
	public Vec2i cpy() {
		return new Vec2i(x, y);
	}
	public Vec2i mul(float s) {
		this.x *= s;
		this.y *= s;
		return this;
	}
	public Vec2i add(Vec2i v) {
		this.x += v.x;
		this.y += v.y;
		return this;
	}
	public Vec2i sub(Vec2i v) {
		this.x -= v.x;
		this.y -= v.y;
		return this;
	}
	public String toString() {
		return x + ", " + y + "\n";
	}
}
