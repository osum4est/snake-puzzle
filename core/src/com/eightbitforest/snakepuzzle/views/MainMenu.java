package com.eightbitforest.snakepuzzle.views;

import com.badlogic.gdx.Game;
import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.Screen;
import com.badlogic.gdx.scenes.scene2d.InputEvent;
import com.badlogic.gdx.scenes.scene2d.Stage;
import com.badlogic.gdx.scenes.scene2d.ui.Button;
import com.badlogic.gdx.scenes.scene2d.ui.Skin;
import com.badlogic.gdx.scenes.scene2d.ui.TextButton;
import com.badlogic.gdx.scenes.scene2d.ui.TextField;
import com.badlogic.gdx.scenes.scene2d.utils.ClickListener;
import com.eightbitforest.snakepuzzle.level.Level;
import com.eightbitforest.snakepuzzle.level.LevelLoader;
import com.eightbitforest.snakepuzzle.utils.ICallback;

public class MainMenu implements Screen {

    private Game game;
    private Stage stage;
    private Skin skin;

    public MainMenu(Game game, Stage stage) {
        this.game = game;
        this.stage = stage;
        skin = new Skin(Gdx.files.internal("skins/flat-earth/skin/flat-earth-ui.json"));
    }

    @Override
    public void show() {

        Button playTestLevel = new TextButton("Test Level", skin);
        playTestLevel.setX(Gdx.graphics.getWidth() / 2 - playTestLevel.getWidth() / 2);
        playTestLevel.setY(Gdx.graphics.getHeight() / 2 - playTestLevel.getHeight() / 2 + 75);
        playTestLevel.addListener(new ClickListener() {
            @Override
            public void clicked(InputEvent event, float x, float y) {
                stage.clear();
                game.setScreen(new MainGame(game, stage, LevelLoader.loadLocalLevel("001.lvl", stage)));
            }
        });

        final TextField remoteLevelTextField = new TextField("easy001", skin);
        remoteLevelTextField.setX(Gdx.graphics.getWidth() / 2 - remoteLevelTextField.getWidth() / 2);
        remoteLevelTextField.setY(Gdx.graphics.getHeight() / 2 - remoteLevelTextField.getHeight() / 2 - 25);

        Button playRemoteLevel = new TextButton("Remote Level", skin);
        playRemoteLevel.setX(Gdx.graphics.getWidth() / 2 - playRemoteLevel.getWidth() / 2);
        playRemoteLevel.setY(Gdx.graphics.getHeight() / 2 - playRemoteLevel.getHeight() / 2 - 75);
        playRemoteLevel.addListener(new ClickListener() {
            @Override
            public void clicked(InputEvent event, float x, float y) {
                stage.clear();
                LevelLoader.loadRemoteLevel(remoteLevelTextField.getText(), stage,
                        new ICallback<Level>() {
                            @Override
                            public void callback(Level level) {
                                game.setScreen(new MainGame(game, stage, level));
                            }
                        });
            }
        });

        stage.addActor(playTestLevel);
        stage.addActor(playRemoteLevel);
        stage.addActor(remoteLevelTextField);
    }

    @Override
    public void render(float delta) {
        stage.act();
        stage.draw();
    }

    @Override
    public void resize(int width, int height) {

    }

    @Override
    public void pause() {

    }

    @Override
    public void resume() {

    }

    @Override
    public void hide() {

    }

    @Override
    public void dispose() {

    }
}
