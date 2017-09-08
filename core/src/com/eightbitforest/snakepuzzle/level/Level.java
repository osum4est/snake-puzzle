package com.eightbitforest.snakepuzzle.level;

import com.badlogic.gdx.math.Vector2;
import com.badlogic.gdx.scenes.scene2d.Stage;
import com.eightbitforest.snakepuzzle.objects.GameObject;
import com.eightbitforest.snakepuzzle.objects.SnakeBody;
import com.eightbitforest.snakepuzzle.objects.SnakeHead;
import com.eightbitforest.snakepuzzle.utils.Direction;

import java.util.ArrayList;
import java.util.Iterator;


public class Level implements Iterable<ArrayList<ArrayList<GameObject>>> {
    private ArrayList<ArrayList<ArrayList<GameObject>>> level;
    private SnakeHead snakeHead;
    private Stage stage;

    public Level(int width, int height, Stage stage) {
        level = new ArrayList<ArrayList<ArrayList<GameObject>>>();
        this.stage = stage;

        for (int x = 0; x < width; x++) {
            level.add(new ArrayList<ArrayList<GameObject>>());
            for (int y = 0; y < height; y++) {
                level.get(x).add(new ArrayList<GameObject>());
            }
        }

        snakeHead = new SnakeHead(this);
        addObject(snakeHead);
    }

    public void setSnakePosition(int x, int y) {
        moveObject(snakeHead, x, y);
    }

    public SnakeHead getSnakeHead() {
        return snakeHead;
    }

    public void addObject(GameObject object) {
        level.get((int) object.getX()).get((int) object.getY()).add(object);
        stage.addActor(object);
    }

    public void moveObject(GameObject object, int newX, int newY, boolean ignoreCollisions) {
        if (!ignoreCollisions && !canMoveObject(object, newX, newY))
            return;

        ArrayList<GameObject> objects = new ArrayList<GameObject>(level.get(newX).get(newY));
        for (GameObject o : objects) {
            o.onCollision(object);
            object.onCollision(o);
        }
        level.get((int) object.getX()).get((int) object.getY()).remove(object);
        level.get(newX).get(newY).add(object);
        object.setPosition(newX, newY);
    }

    public void moveObject(GameObject object, int newX, int newY) {
        moveObject(object, newX, newY, false);
    }

    public boolean canMoveObject(GameObject object, int newX, int newY) {
        ArrayList<GameObject> objects = new ArrayList<GameObject>(level.get(newX).get(newY));
        for (GameObject o : objects)
            if (!o.canCollide(object) || !object.canCollide(o))
                return false;

        return true;
    }

    public void translateObject(GameObject object, Vector2 direction) {
        moveObject(object, (int) (object.getX() + direction.x), (int) (object.getY() + direction.y));
    }

    public void translateObject(GameObject object, Direction direction) {
        translateObject(object, direction.getVector());
    }

    public boolean canTranslateObject(GameObject object, Vector2 direction) {
        return canMoveObject(object, (int) (object.getX() + direction.x), (int) (object.getY() + direction.y));
    }

    public boolean canTranslateObject(GameObject object, Direction direction) {
        return canTranslateObject(object, direction.getVector());
    }

    @Override
    public Iterator<ArrayList<ArrayList<GameObject>>> iterator() {
        return level.iterator();
    }

    public void moveSnake(Direction up) {
        Vector2 direction = up.getVector();
        if (!canTranslateObject(snakeHead, direction))
            return;

        ArrayList<SnakeBody> body = snakeHead.getBody();
        for (int i = body.size() - 1; i > 0; i--) {
            moveObject(body.get(i), (int) (body.get(i - 1).getX()), (int) (body.get(i - 1).getY()), true);
        }
        moveObject(body.get(0), (int) (snakeHead.getX()), (int) (snakeHead.getY()), true);
        translateObject(snakeHead, direction);
    }

    public ArrayList<GameObject> getObjectsAt(int x, int y) {
        return level.get(x).get(y);
    }

    public boolean isObjectAt(int x, int y) {
        return getObjectsAt(x, y).size() > 0;
    }

    public void removeObject(GameObject object) {
        level.get((int) object.getX()).get((int) object.getY()).remove(object);
        object.remove();
    }
}
