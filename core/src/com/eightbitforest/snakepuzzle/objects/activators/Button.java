package com.eightbitforest.snakepuzzle.objects.activators;

import com.badlogic.gdx.graphics.Color;
import com.eightbitforest.snakepuzzle.level.Level;
import com.eightbitforest.snakepuzzle.objects.GameObject;
import com.eightbitforest.snakepuzzle.utils.Z;

public class Button extends GameObject implements IActivator {
    public Button(Level level, int x, int y) {
        super(level, x, y, Color.RED);
    }

    @Override
    public boolean isActivated() {
        return getLevel().getObjectsAt((int) getX(), (int) getY()).size() > 1;
    }

    @Override
    public boolean canCollide(GameObject other) {
        return true;
    }

    @Override
    public int getZ() {
        return Z.BUTTON;
    }
}
