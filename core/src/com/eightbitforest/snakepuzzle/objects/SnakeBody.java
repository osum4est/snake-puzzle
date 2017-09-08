package com.eightbitforest.snakepuzzle.objects;

import com.eightbitforest.snakepuzzle.level.Level;
import com.eightbitforest.snakepuzzle.utils.Colors;

public class SnakeBody extends GameObject {
    public SnakeBody(Level level, int x, int y) {
        super(level, x, y, Colors.SNAKE_BODY);
    }

    @Override
    public boolean canCollide(GameObject other) {
        return other instanceof SnakeBody || other instanceof SnakeHead;
    }
}
