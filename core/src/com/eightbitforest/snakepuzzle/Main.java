package com.eightbitforest.snakepuzzle;

import com.badlogic.gdx.Game;
import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.graphics.GL20;
import com.eightbitforest.snakepuzzle.utils.Colors;
import com.eightbitforest.snakepuzzle.views.MainGame;

public class Main extends Game {

	@Override
    public void create() {
        setScreen(new MainGame());
    }

	@Override
    public void render() {
        Gdx.gl.glClearColor(
                Colors.BACKGROUND.r,
                Colors.BACKGROUND.g,
                Colors.BACKGROUND.b,
                Colors.BACKGROUND.a);
        Gdx.gl.glClear(GL20.GL_COLOR_BUFFER_BIT | GL20.GL_DEPTH_BUFFER_BIT);
        super.render();
    }

    @Override
    public void dispose() {
        super.dispose();
    }
}
