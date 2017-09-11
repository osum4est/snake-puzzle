package com.eightbitforest.snakepuzzle.objects;

import com.eightbitforest.snakepuzzle.level.Level;
import com.eightbitforest.snakepuzzle.utils.Colors;
import com.eightbitforest.snakepuzzle.utils.Z;

public class SnakeBody extends GameObject {
    public SnakeBody(Level level, int x, int y) {
        super(level, x, y, Colors.SNAKE_BODY);
    }

    @Override
    public boolean canCollide(GameObject other) {
        return other instanceof SnakeBody;// || other instanceof SnakeHead;
    }

    @Override
    public int getZ() {
        return Z.SNAKE;
    }
}
