package com.eightbitforest.snakepuzzle.level;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.files.FileHandle;
import com.badlogic.gdx.scenes.scene2d.Stage;
import com.badlogic.gdx.utils.JsonReader;
import com.badlogic.gdx.utils.JsonValue;
import com.eightbitforest.snakepuzzle.network.HttpClient;
import com.eightbitforest.snakepuzzle.objects.*;
import com.eightbitforest.snakepuzzle.utils.Constants;
import com.eightbitforest.snakepuzzle.utils.ICallback;

import java.util.ArrayList;

public class LevelLoader {
    public static Level loadLocalLevel(String filename, Stage stage) {
        FileHandle handle = Gdx.files.internal("levels/" + filename);
        String file = handle.readString();
        return loadFromString(file, stage);
    }

    public static void loadRemoteLevel(String filename, final Stage stage, final ICallback<Level> callback) {
        HttpClient.getLevel(filename + ".lvl", new ICallback<String>() {
            @Override
            public void callback(String levelString) {
                callback.callback(loadFromString(levelString, stage));
            }
        });
    }


    private static Level loadFromString(String levelString, Stage stage) {
        Level level = new Level(Constants.LEVEL_WIDTH, Constants.LEVEL_HEIGHT, stage);

        String[] lines = levelString.split("\n");
        ArrayList<String> levelLines = new ArrayList<String>();
        ArrayList<String> propLines = new ArrayList<String>();

        for (int y = 0; y < lines.length; y++) {
            if (!lines[y].isEmpty()) {
                if (lines[y].contains("{")) {
                    propLines.add(lines[y]);
                } else {
                    levelLines.add(lines[y]);
                }
            }
        }

        for (int y = 0; y < levelLines.size(); y++) {
            for (int x = 0; x < levelLines.get(y).length(); x++) {
                char c = levelLines.get(y).charAt(x);
                addGameObject(level, c, x, levelLines.size() - 1 - y);
            }
        }

        for (int i = 0; i < propLines.size(); i++) {
            JsonValue json = new JsonReader().parse(propLines.get(i));
            if (json.has("x") && json.has("y")) {
                ArrayList<GameObject> objects = level.getObjectsAt(
                        json.getInt("x") - 1,
                        levelLines.size() - json.getInt("y"));
                if (objects.size() == 1) {
                    objects.get(0).setProperties(json);
                } else {
                    System.out.println("No object at property position");
                }
            } else {
                System.out.println("Level property missing x and y");
            }
        }

        return level;
    }

    private static void addGameObject(Level level, char c, int x, int y) {
        switch (c) {
            case 'X':
                level.addObject(new Wall(level, x, y));
                break;
            case 'B':
                level.addObject(new Box(level, x, y));
                break;
            case 'F':
                level.addObject(new Food(level, x, y));
                break;
            case 'S':
                level.setSnakePosition(x, y);
                break;
            default:
                if (Character.isDigit(c)) {
                    SnakeBody part = new SnakeBody(level, x, y);
                    level.getSnakeHead().addBodyPart(part, Character.getNumericValue(c));
                    level.addObject(part);
                }
                break;
        }
    }
}
