package com.eightbitforest.snakepuzzle.objects;

import com.badlogic.gdx.graphics.g2d.Batch;
import com.badlogic.gdx.graphics.glutils.ShapeRenderer;
import com.eightbitforest.snakepuzzle.level.Level;
import com.eightbitforest.snakepuzzle.utils.Colors;
import com.eightbitforest.snakepuzzle.utils.Constants;

public class Wall extends GameObject {
    public Wall(Level level, int x, int y) {
        super(level, x, y, Colors.WALL);
    }

    @Override
    public void draw(Batch batch, float parentAlpha) {
        batch.end();

        renderer.setProjectionMatrix(batch.getProjectionMatrix());
        renderer.setTransformMatrix(batch.getTransformMatrix());
        renderer.translate(
                getX() * Constants.SIZE,
                getY() * Constants.SIZE, 0);
        renderer.setColor(getColor());

        renderer.begin(ShapeRenderer.ShapeType.Filled);
        renderer.rect(0, 0,
                getWidth(),
                getHeight());
        renderer.end();

        batch.begin();
    }
}
