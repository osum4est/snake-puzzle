/**
 * Created by osum4est on 4/21/17.
 */

function Colors() {

}


Colors.BLUE                 = "rgb(102, 217, 239)";
Colors.GREEN                = "rgb(166, 226, 46 )";
Colors.MAGENTA              = "rgb(249, 38 , 114)";
Colors.ORANGE               = "rgb(253, 151, 31 )";
Colors.WHITE                = "rgb(248, 248, 242)";
Colors.BLACK                = "rgb(39 , 40 , 34 )";
Colors.YELLOW               = "rgb(230, 219, 116)";

Colors.SNAKE_HEAD           = Colors.BLUE;
Colors.SNAKE_BODY_DEFAULT   = Colors.GREEN;
Colors.FOOD_DEFAULT         = Colors.MAGENTA;
Colors.BOX                  = Colors.ORANGE;
Colors.WALL                 = Colors.WHITE;
Colors.BACKGROUND           = Colors.BLACK;
Colors.EXIT                 = Colors.YELLOW;


Colors.objects = {
    " ": undefined,
    "X": Colors.WALL,
    "S": Colors.SNAKE_HEAD,
    "B": Colors.BOX,
    "F": Colors.FOOD_DEFAULT,
    "E": Colors.EXIT
};

Colors.numObjects = function() {
    return Object.keys(Colors.objects).length;
};

Colors.objectAt = function(i) {
    return Object.keys(Colors.objects)[i];
};

Colors.getColorForObject = function(object) {
    if ($.isNumeric(object)) {
        return Colors.SNAKE_BODY_DEFAULT
    }
    else {
        if (Colors.objects[object] === undefined)
            return "#FF0000";
        else
            return Colors.objects[object];
    }
};
