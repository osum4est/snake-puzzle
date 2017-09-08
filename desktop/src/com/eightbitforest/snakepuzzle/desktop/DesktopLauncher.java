package com.eightbitforest.snakepuzzle.desktop;

import com.badlogic.gdx.backends.lwjgl3.Lwjgl3Application;
import com.badlogic.gdx.backends.lwjgl3.Lwjgl3ApplicationConfiguration;
import com.eightbitforest.snakepuzzle.Main;

public class DesktopLauncher {
    public static void main(String[] args) {
        Lwjgl3ApplicationConfiguration cfg = new Lwjgl3ApplicationConfiguration();
        cfg.setTitle("Snake Puzzle");
        cfg.setWindowedMode(320, 480);

        new Lwjgl3Application(new Main(), cfg);
    }
}