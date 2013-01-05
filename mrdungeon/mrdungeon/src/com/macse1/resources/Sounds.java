package com.macse1.resources;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.audio.Music;
import com.badlogic.gdx.audio.Sound;

public class Sounds {
	
	public static Sound footLand;
	public static Sound heroJump;
	public static Sound heroJet;
	public static Sound heroHurt;
	
	public static Sound trap_trigger;
	public static Sound drop_tile;
	public static Sound pick_tile;
	public static Sound goal;
	
	public static Music s3;
	public static Music s2;
	public static Music s1;

	
	public static void load () {
		footLand = load("sounds/GCAfootComeDown.wav");
		heroJet = load("sounds/GCAexplosion.wav");
		heroJump = load("sounds/GCAjump.wav");
		heroHurt = load("sounds/GCAexplosion2.wav");
		
		trap_trigger = load("sounds/GCAtrapTrigger.wav");
		pick_tile = load("sounds/GCApickUpTile.wav");
		goal = load("sounds/GCAtreasure.wav");
		drop_tile = load("sounds/GCAdrop2.wav");
		
		s3 = loadm("sounds/s3.mp3");
		s2 = loadm("sounds/s2.mp3");
		s1 = loadm("sounds/s1.mp3");
		
		s3.setLooping(true);
		s2.setLooping(true);
		s1.setLooping(true);
	}

	private static com.badlogic.gdx.audio.Music loadm (String name) {
		return Gdx.audio.newMusic(Gdx.files.internal(name));
		
	}
	private static com.badlogic.gdx.audio.Sound load (String name) {
		return Gdx.audio.newSound(Gdx.files.internal(name));
		
	}
	
	
}
