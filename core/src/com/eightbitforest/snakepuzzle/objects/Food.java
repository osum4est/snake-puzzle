package com.eightbitforest.snakepuzzle.objects;

import com.eightbitforest.snakepuzzle.level.Level;
import com.eightbitforest.snakepuzzle.utils.Colors;

public class Food extends GameObject {
    public Food(Level level, int x, int y) {
        super(level, x, y, Colors.FOOD);
    }

    @Override
    public void onCollision(GameObject other) {
        if (other instanceof SnakeHead) {
            SnakeHead snakeHead = (SnakeHead) other;
            snakeHead.grow(1);
            getLevel().removeObject(this);
        }
    }

    @Override
    public boolean canCollide(GameObject other) {
        return other instanceof SnakeHead;
    }
}
