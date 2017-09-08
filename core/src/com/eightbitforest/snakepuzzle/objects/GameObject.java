package com.eightbitforest.snakepuzzle.objects;

import com.badlogic.gdx.graphics.Color;
import com.badlogic.gdx.graphics.g2d.Batch;
import com.badlogic.gdx.graphics.glutils.ShapeRenderer;
import com.badlogic.gdx.scenes.scene2d.Actor;
import com.eightbitforest.snakepuzzle.level.Level;
import com.eightbitforest.snakepuzzle.utils.Constants;

public abstract class GameObject extends Actor {
    protected ShapeRenderer renderer;
    private Level level;

    public GameObject(Level level) {
        renderer = new ShapeRenderer();
        this.level = level;
        setSize(Constants.SIZE, Constants.SIZE);
    }

    public GameObject(Level level, Color color) {
        this(level);
        setColor(color);
    }

    public GameObject(Level level, int x, int y) {
        this(level);
        setPosition(x, y);
    }

    public GameObject(Level level, int x, int y, Color color) {
        this(level);
        setPosition(x, y);
        setColor(color);
    }

    @Override
    public void draw(Batch batch, float parentAlpha) {
        batch.end();

        renderer.setProjectionMatrix(batch.getProjectionMatrix());
        renderer.setTransformMatrix(batch.getTransformMatrix());
        renderer.translate(
                getX() * Constants.SIZE + Constants.BORDER_SIZE,
                getY() * Constants.SIZE + Constants.BORDER_SIZE, 0);
        renderer.setColor(getColor());

        renderer.begin(ShapeRenderer.ShapeType.Filled);
        renderer.rect(0, 0,
                getWidth() - Constants.BORDER_SIZE * 2,
                getHeight() - Constants.BORDER_SIZE * 2);
        renderer.end();

        batch.begin();
    }

    public void onCollision(GameObject other) {

    }

    protected Level getLevel() {
        return level;
    }

    public boolean canCollide(GameObject other) {
        return false;
    }
}
