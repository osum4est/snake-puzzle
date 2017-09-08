package com.eightbitforest.snakepuzzle.objects;

import com.badlogic.gdx.scenes.scene2d.Touchable;
import com.eightbitforest.snakepuzzle.level.Level;
import com.eightbitforest.snakepuzzle.utils.Colors;
import com.eightbitforest.snakepuzzle.utils.Constants;

import java.util.ArrayList;

public class SnakeHead extends GameObject {
    private ArrayList<SnakeBody> body;

    public SnakeHead(Level level) {
        super(level, Colors.SNAKE_HEAD);
        body = new ArrayList<SnakeBody>();
        setTouchable(Touchable.enabled);
    }

    public void addBodyPart(SnakeBody part, int index) {
        while (body.size() < index + 1) {
            body.add(null);
        }
        body.set(index, part);
    }

    public float getWorldCenterX() {
        return getX() * Constants.SIZE + Constants.SIZE / 2;
    }

    public float getWorldCenterY() {
        return getY() * Constants.SIZE + Constants.SIZE / 2;
    }

    public ArrayList<SnakeBody> getBody() {
        return body;
    }

    public void grow(int amount) {
        for (int i = 0; i < amount; i++) {
            SnakeBody last = body.get(body.size() - 1);
            SnakeBody newBody = new SnakeBody(getLevel(), (int) last.getX(), (int) last.getY());
            getLevel().addObject(newBody);
            body.add(newBody);
        }
    }

    @Override
    public boolean canCollide(GameObject other) {
        return other instanceof Box || other instanceof Food;
    }
}