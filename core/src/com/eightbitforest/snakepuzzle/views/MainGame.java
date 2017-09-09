package com.eightbitforest.snakepuzzle.views;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.Screen;
import com.badlogic.gdx.scenes.scene2d.InputEvent;
import com.badlogic.gdx.scenes.scene2d.InputListener;
import com.badlogic.gdx.scenes.scene2d.Stage;
import com.badlogic.gdx.utils.viewport.ExtendViewport;
import com.eightbitforest.snakepuzzle.level.Level;
import com.eightbitforest.snakepuzzle.level.LevelLoader;
import com.eightbitforest.snakepuzzle.utils.Constants;
import com.eightbitforest.snakepuzzle.utils.Direction;

public class MainGame implements Screen {

    private Stage stage;
    private Level level;

    @Override
    public void show() {
        stage = new Stage(new ExtendViewport(320, 480));
        level = LevelLoader.LoadLevel("001.lvl", stage);

        Gdx.input.setInputProcessor(stage);
        stage.addListener(new InputListener() {
            boolean moving = false;

            @Override
            public boolean touchDown(InputEvent event, float x, float y, int pointer, int button) {
                if (Math.abs(level.getSnakeHead().getWorldCenterX() - x) < 20 ||
                        Math.abs(level.getSnakeHead().getWorldCenterY() - y) < 20) {
                    moving = true;
                    return true;
                }

                return false;
            }

            @Override
            public void touchDragged(InputEvent event, float x, float y, int pointer) {
                if (moving) {
                    float xDiff = level.getSnakeHead().getWorldCenterX() - x;
                    float yDiff = level.getSnakeHead().getWorldCenterY() - y;

                    if (Math.abs(xDiff) > Constants.SIZE / 2 || Math.abs(yDiff) > Constants.SIZE / 2) {
                        Direction d;
                        if (Math.abs(xDiff) > Math.abs(yDiff)) {
                            d = xDiff > 0 ? Direction.LEFT : Direction.RIGHT;
                        } else {
                            d = yDiff > 0 ? Direction.DOWN : Direction.UP;
                        }
                        level.moveSnake(d);
                    }
                }
            }

            @Override
            public void touchUp(InputEvent event, float x, float y, int pointer, int button) {
                moving = false;
            }
        });
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
        stage.dispose();
    }
}
