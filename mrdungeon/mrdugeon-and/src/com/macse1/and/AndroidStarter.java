package com.macse1.and;

import com.badlogic.gdx.backends.android.AndroidApplication;
import com.macse1.Game;

import android.app.Activity;
import android.os.Bundle;

public class AndroidStarter extends AndroidApplication {
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        initialize(new Game(), false);
    }
}