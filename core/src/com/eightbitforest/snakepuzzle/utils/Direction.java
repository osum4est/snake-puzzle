package com.eightbitforest.snakepuzzle.utils;

import com.badlogic.gdx.math.Vector2;

public enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT;

    public static Direction getFromPoints(int x1, int y1, int x2, int y2) {
        int xDiff = x1 - x2;
        int yDiff = y1 - y2;

        if (Math.abs(xDiff) > Math.abs(yDiff)) {
            return xDiff > 0 ? LEFT : RIGHT;
        } else {
            return yDiff > 0 ? DOWN : UP;
        }
    }

    public Vector2 getVector() {
        switch (this) {
            case UP:
                return new Vector2(0, 1);
            case DOWN:
                return new Vector2(0, -1);
            case LEFT:
                return new Vector2(-1, 0);
            case RIGHT:
                return new Vector2(1, 0);
        }
        return null;
    }
}
