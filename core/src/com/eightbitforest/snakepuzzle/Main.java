package com.eightbitforest.snakepuzzle;

import com.badlogic.gdx.Game;
import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.graphics.GL20;
import com.badlogic.gdx.scenes.scene2d.Stage;
import com.badlogic.gdx.utils.viewport.ExtendViewport;
import com.eightbitforest.snakepuzzle.utils.Colors;
import com.eightbitforest.snakepuzzle.views.MainMenu;

public class Main extends Game {
    private Stage stage;

	@Override
    public void create() {
        System.out.println("Welcome to snake puzzle");
        stage = new Stage(new ExtendViewport(320, 480));
        Gdx.input.setInputProcessor(stage);

        setScreen(new MainMenu(this, stage));
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
