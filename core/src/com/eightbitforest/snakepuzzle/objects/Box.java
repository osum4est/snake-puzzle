package com.eightbitforest.snakepuzzle.objects;

import com.eightbitforest.snakepuzzle.level.Level;
import com.eightbitforest.snakepuzzle.utils.Colors;
import com.eightbitforest.snakepuzzle.utils.Direction;

public class Box extends GameObject {
    public Box(Level level, int x, int y) {
        super(level, x, y, Colors.BOX);
    }

    @Override
    public void onCollision(GameObject other) {
        if (other instanceof SnakeHead) {
            Direction direction = Direction.getFromPoints((int) (other.getX()), (int) (other.getY()), (int) (getX()), (int) (getY()));
            getLevel().translateObject(this, direction);
        }
    }

    @Override
    public boolean canCollide(GameObject other) {
        if (other instanceof SnakeHead) {
            Direction direction = Direction.getFromPoints((int) (other.getX()), (int) (other.getY()), (int) (getX()), (int) (getY()));
            return getLevel().canTranslateObject(this, direction);
        }
        return false;
    }
}
