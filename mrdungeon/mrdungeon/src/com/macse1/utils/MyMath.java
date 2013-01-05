package com.macse1.utils;

public class MyMath {
	public static float clamp(float val, float min, float max) {
		if (val<min) { val = min; }
		else if (val>max) { val = max; }
		return val;
	}
	public static int clamp(int val, int min, int max) {
		if (val<min) { val = min; }
		else if (val>max) { val = max; }
		return val;
	}
	public static boolean rectangleIntersect(int pl, int pt, int pr, int pb, int rl, int rt, int rr, int rb) {
		return !(pr<rl || pl>rr || pt>rb || pb<rt);
	}
	public static boolean pointInRect(int px, int py, int rl, int rt, int rr, int rb) {
		return (px>rl && px<rr && py>rt && py<rb);
	}
	public static int ceilf(float f) {
		return (f - (float)(int)f > 0) ? (int) f+1 : (int) f;
	}
}
