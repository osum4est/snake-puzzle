package com.eightbitforest.snakepuzzle.objects;

import com.badlogic.gdx.utils.JsonValue;
import com.eightbitforest.snakepuzzle.level.Level;
import com.eightbitforest.snakepuzzle.objects.activators.IActivator;
import com.eightbitforest.snakepuzzle.utils.Colors;
import com.eightbitforest.snakepuzzle.utils.Constants;

import java.util.ArrayList;

public class Door extends GameObject {
    private boolean isOpen = false;
    private ArrayList<IActivator> activators;

    public Door(Level level, int x, int y) {
        super(level, x, y);
        activators = new ArrayList<IActivator>();
    }

    public void open() {
        isOpen = true;
        setColor(Colors.DOOR_OPEN);
    }

    public void close() {
        isOpen = false;
        setColor(Colors.DOOR_CLOSED);
    }

    @Override
    public void onUpdate() {
        open();
        for (IActivator activator : activators) {
            if (!activator.isActivated())
                close();
        }
    }

    @Override
    public boolean canCollide(GameObject other) {
        return (other instanceof SnakeHead && isOpen);
    }

    @Override
    public void setProperties(JsonValue json) {
        if (json.has("activators")) {
            JsonValue activatorsJson = json.get("activators");
            for (JsonValue activatorJson : activatorsJson) {
                GameObject activatorObject = getLevel().getObjectAt(
                        activatorJson.getInt("x") - 1,
                        Constants.LEVEL_HEIGHT - activatorJson.getInt("y"));
                if (activatorObject instanceof IActivator) {
                    activators.add((IActivator) activatorObject);
                } else {
                    System.out.println("Activator is not instance of IActivator!");
                }
            }
        }

        super.setProperties(json);
    }
}
