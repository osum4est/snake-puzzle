package com.eightbitforest.snakepuzzle.level;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.files.FileHandle;
import com.badlogic.gdx.scenes.scene2d.Stage;
import com.eightbitforest.snakepuzzle.objects.Box;
import com.eightbitforest.snakepuzzle.objects.Food;
import com.eightbitforest.snakepuzzle.objects.SnakeBody;
import com.eightbitforest.snakepuzzle.objects.Wall;
import com.eightbitforest.snakepuzzle.utils.Constants;

public class LevelLoader {
    public static Level LoadLevel(String filename, Stage stage) {
        FileHandle handle = Gdx.files.internal("levels/" + filename);
        String file = handle.readString();
        System.out.println("Loading " + filename + "...");

        Level level = new Level(Constants.LEVEL_WIDTH, Constants.LEVEL_HEIGHT, stage);

        String[] lines = file.split("\n");

        for (int y = 0; y < lines.length; y++) {
            for (int x = 0; x < lines[y].length(); x++) {
                char c = lines[y].charAt(x);
                addGameObject(level, c, x, lines.length - 1 - y);
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
