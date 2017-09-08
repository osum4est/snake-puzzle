/**
 * Created by osum4est on 4/21/17.
 */

function Level(file, levelData) {
    this.SIZE = 20;
    this.filename = file;

    this.codebox = $(".CodeMirror")[0].CodeMirror;
    this.codebox.on("change", this.onEditorChanged.bind(this));
    this.codebox.on("cursorActivity", this.onSelectionChanged.bind(this));

    this.canvas = $("#level_canvas").get(0);
    this.ctx = this.canvas.getContext('2d');
    this.textarea = $("#level_textarea");

    this.savebutton = $("#button-save");

    this.canvas.style.background = Colors.BACKGROUND;
    $("#level_canvas").off();
    this.canvas.addEventListener('mousemove', this.mouseMove.bind(this), false);
    this.canvas.addEventListener('touchmove', function(evt) {
        if (evt.touches.length == 1) {
            this.mouseMove(evt);
            evt.preventDefault();
        }
    }.bind(this), false);
    this.canvas.addEventListener('mouseout', this.mouseOut.bind(this), false);
    this.canvas.addEventListener('mousedown', this.mouseDown.bind(this), false);
    this.canvas.addEventListener('touchstart', function(evt) {
        if (evt.touches.length == 1) {
            this.mouseDown(evt);
        }
    }.bind(this), false);
    this.canvas.addEventListener('mouseup', this.mouseUp.bind(this), false);

    this.levelheight = 24;
    this.levelwidth = 16;

    this.leveltext = "";
    this.levelprops = "";

    for (c = 0; c < levelData.length; c++) {
        if (levelData[c] === '\n') {
            if (levelData[c + 1] === '{' || levelData[c + 1] === '\n') {
                this.leveltext = levelData.substring(0, c);
                this.levelprops = levelData.substring(c + 1, levelData.length);
                break;
            }
        }
    }

    this.stripNewLinesFromTexts();
    this.refreshEditor();
    this.refreshLevel();

    this.setSaved();
}

Level.prototype.onSelectionChanged = function(editor) {
    if (!Level.editingProps()) {
        this.propSelectionX = undefined;
        this.propSelectionY = undefined;
        this.refreshLevel();
        return;
    }

    try {
        pos = editor.getCursor();
        var line = editor.getLine(pos["line"]);
        var propjson = JSON.parse(line);
        this.propSelectionX = this.SIZE * (propjson["x"]);
        this.propSelectionY = this.SIZE * (propjson["y"]);
    }
    catch (e) {
        this.propSelectionX = undefined;
        this.propSelectionY = undefined;
    }
    this.refreshLevel();
};

Level.prototype.onEditorChanged = function(editor, change) {
    if (Level.editingProps() && this.levelprops !== editor.getValue()) {
        this.levelprops = editor.getValue();
        this.onSelectionChanged(editor);
    }
    else if (!Level.editingProps() && this.leveltext !== editor.getValue()) {
        this.leveltext = editor.getValue();
    }
    else {
        return;
    }

    this.setEdited();
    this.refreshLevel();
};

Level.prototype.drawSquare = function(color, x, y) {
    this.ctx.fillStyle = color;
    this.ctx.fillRect(x, y, this.SIZE, this.SIZE);

    if (this.propSelectionX !== undefined && this.propSelectionY !== undefined &&
            this.propSelectionX === x && this.propSelectionY === y) {
        var thick = 2;
        var inverseColor = "rgb(";
        var nums = color.match(/\d+/g);
        for (var i = 0; i < nums.length; i++) {
            inverseColor += (255 - nums[i]).toString();
            if (i < 2) {
                inverseColor += ", ";
            }
        }
        inverseColor += ")";
        this.ctx.strokeStyle= inverseColor;
        this.ctx.setLineDash([]);
        this.ctx.lineWidth = thick;
        this.ctx.strokeRect(x + thick, y + thick, this.SIZE - (thick * 2), this.SIZE - (thick * 2));
    }
};

Level.prototype.refreshEditor = function() {
    if (Level.editingProps()) {
        this.codebox.setValue(this.levelprops);
    }
    else {
        this.codebox.setValue(this.leveltext);
    }
};

Level.prototype.clearCanvas = function() {
    this.ctx.clearRect(0, 0, this.canvas.width, this.canvas.height);
};

Level.prototype.placeObject = function(x, y, object) {
    var lineX = 0;
    var lineY = 0;
    for (var c = 0; c < this.leveltext.length; c++) {
        if (this.leveltext[c] === '\n') {
            lineY++;
            lineX = 0;
        }
        else {
            if (lineY + 1 === y && lineX + 1 === x) {
                this.leveltext = this.leveltext.replaceAt(c, object);
                this.refreshEditor();
                this.refreshLevel();
                this.setEdited();
                return;
            }
            lineX++;
        }
    }
};

Level.prototype.mouseDown = function(evt) {
    console.log("mousedown");
    var intersection = this.getIntersection(evt);
    if (intersection['isObjectPicker']) {
        this.selectedObject = intersection['objectPickerIndex'];
        this.refreshLevel();
    }
    else if (intersection['isIntersection'] && evt['button'] === 2) {
        this.placingObjects = true;
        this.placeObject(intersection['gridX'] / this.SIZE, intersection['gridY'] / this.SIZE, Colors.objectAt(0));
    }
    else if (intersection['isIntersection'] && this.selectedObject !== undefined) {
        this.placingObjects = true;
        this.placeObject(intersection['gridX'] / this.SIZE, intersection['gridY'] / this.SIZE, Colors.objectAt(this.selectedObject));
    }

    // evt.preventDefault();
};

Level.prototype.mouseUp = function(evt) {
    this.placingObjects = false;
    // evt.preventDefault();
};

Level.prototype.mouseOut = function(evt) {
    this.hoverX = undefined;
    this.hoverY = undefined;
    this.refreshLevel();
    // evt.preventDefault();
};

Level.prototype.getIntersection = function(mouseEvt) {
    var rect = this.canvas.getBoundingClientRect();
    var x;
    var y;
    if (mouseEvt.touches !== undefined) {
        if (mouseEvt.touches.length === 1) {
            var touch = mouseEvt.touches[0];
            x = touch.pageX - touch.target.offsetLeft;
            y = touch.pageY - touch.target.offsetTop;
        }
        else {
            mouseEvt.default();
            return {};
        }
    }
    else {
        x = mouseEvt.clientX - rect.left;
        y = mouseEvt.clientY - rect.top;
    }

    var intersection = {};
    intersection['mouseX'] = x;
    intersection['mouseY'] = y;
    intersection['isIntersection'] = false;

    if (x > this.SIZE && y > this.SIZE && y < (this.levelheight + 1) * this.SIZE) {
        var tempX = Math.floor(x / this.SIZE);
        var tempY = Math.floor(y / this.SIZE);
        intersection['isIntersection'] = true;
        intersection['gridX'] = tempX * this.SIZE;
        intersection['gridY'] = tempY * this.SIZE;
        intersection['isObjectPicker'] = false;
    }
    else {
        for (var i = 1; i < Colors.numObjects() + 1; i++) {
            if (x > i / (Colors.numObjects() + 1) * this.canvas.width - this.SIZE / 2 &&
                x < i / (Colors.numObjects() + 1) * this.canvas.width - this.SIZE / 2 + this.SIZE &&
                y > this.levelheight * this.SIZE + this.SIZE * 1.5 &&
                y < this.levelheight * this.SIZE + this.SIZE * 1.5 + this.SIZE) {
                intersection['isIntersection'] = true;
                intersection['gridX'] = Math.floor(i / (Colors.numObjects() + 1) * this.canvas.width - this.SIZE / 2);
                intersection['gridY'] = Math.floor(this.levelheight * this.SIZE + this.SIZE * 1.5);
                intersection['isObjectPicker'] = true;
                intersection['objectPickerIndex'] = i - 1;
            }
        }
    }

    return intersection;
};

Level.prototype.mouseMove = function(evt) {
    var intersection = this.getIntersection(evt);
    if (intersection['isIntersection']) {
        var newSquare = this.updateHover(intersection['gridX'], intersection['gridY']);
        if (this.placingObjects && newSquare) {
            if (evt['button'] === 2) {
                this.placeObject(intersection['gridX'] / this.SIZE, intersection['gridY'] / this.SIZE, Colors.objectAt(0));
            }
            else {
                this.placeObject(intersection['gridX'] / this.SIZE, intersection['gridY'] / this.SIZE, Colors.objectAt(this.selectedObject));
            }
        }
    }
    else {
        this.updateHover();
    }
    // evt.preventDefault();
};

Level.prototype.updateHover = function(x, y) {
    if (x === undefined && y === undefined && this.hoverX !== undefined && this.hoverY !== undefined) {
        this.hoverX = undefined;
        this.hoverY = undefined;
        this.refreshLevel();

        return true;
    }
    else if ((x !== undefined && y !== undefined) && (this.hoverX === undefined || this.hoverY === undefined ||
        x !== this.hoverX || y !== this.hoverY)) {
        this.hoverX = x;
        this.hoverY = y;

        this.refreshLevel();
        this.ctx.globalAlpha = .6;
        this.drawSquare("rgb(75, 75, 75)", this.hoverX, this.hoverY);
        this.ctx.globalAlpha = 1;

        return true;
    }

    return false;
};

Level.prototype.refreshLevel = function() {
    console.log("Refreshing level");

    this.clearCanvas();

    // Objects
    var y = 0;
    var x = 0;
    for (var c = 0; c < this.leveltext.length; c++) {
        char = this.leveltext[c];
        if (char === '\n') {
            y++;
            x = 0;
        }
        else {
            if (char !== ' ') {
                this.drawSquare(Colors.getColorForObject(this.leveltext[c]), this.SIZE + x * this.SIZE, this.SIZE + y * this.SIZE);
            }
            x++;
        }
    }

    // Line numbers
    this.ctx.font = "12px monospace";
    this.ctx.textAlign = "right";
    for (var i = 1; i < this.levelheight + 1; i++) {
        this.ctx.fillText(i.toString(), this.SIZE - 5, (i + .7) * this.SIZE);
    }
    this.ctx.textAlign = "center";
    for (var i = 1; i < this.levelwidth + 1; i++) {
        this.ctx.fillText(i.toString(), (i + .5) * this.SIZE, this.SIZE - 6);
    }

    this.drawGrid();
    this.drawObjectPicker();
};

Level.prototype.drawObjectPicker = function() {
    this.ctx.strokeStyle = Colors.WHITE;
    if (this.selectedObject !== undefined) {
        this.ctx.lineWidth = 6;
        this.ctx.setLineDash([]);
        this.ctx.strokeRect((this.selectedObject + 1) / (Colors.numObjects() + 1) * this.canvas.width - this.SIZE / 2,
            this.levelheight * this.SIZE + this.SIZE * 1.5,
            this.SIZE, this.SIZE);
    }

    this.ctx.lineWidth = 1;
    this.ctx.setLineDash([2, 2]);
    this.ctx.strokeRect(
        Math.floor(1 / (Colors.numObjects() + 1) * this.canvas.width - this.SIZE / 2) + .5,
        Math.floor(this.levelheight * this.SIZE + this.SIZE * 1.5) + .5,
        this.SIZE, this.SIZE);

    for (var i = 1; i < Colors.numObjects(); i++) {
        this.drawSquare(
            Colors.getColorForObject(Colors.objectAt(i)),
            (i + 1) / (Colors.numObjects() + 1) * this.canvas.width - this.SIZE / 2,
            this.levelheight * this.SIZE + this.SIZE * 1.5
        )
    }
};

Level.prototype.drawGrid = function() {
    this.ctx.strokeStyle = "#555";
    this.ctx.lineWidth = 1;
    this.ctx.setLineDash([2, 3]);
    for (var y = 1; y < this.levelheight + 1; y++) {
        this.ctx.beginPath();
        this.ctx.moveTo(0, y * this.SIZE  + .5);
        this.ctx.lineTo((this.levelwidth + 1) * this.SIZE, y * this.SIZE + .5);
        this.ctx.stroke();
    }
    for (var x = 1; x < this.levelwidth + 1; x++) {
        this.ctx.beginPath();
        this.ctx.moveTo(x * this.SIZE + .5, 0);
        this.ctx.lineTo(x * this.SIZE + .5, (this.levelheight + 1) * this.SIZE);
        this.ctx.stroke();
    }
};

Level.editingProps = function() {
    return $("#tab-props").hasClass("active")
};

Level.prototype.setEdited = function() {
    this.resetSaveButton();
    this.savebutton.addClass("btn-primary");
    this.savebutton.text("Save");
};

Level.prototype.setSaved = function() {
    this.resetSaveButton();
    this.savebutton.addClass("btn-success");
    this.savebutton.text("Saved!");
};

Level.prototype.saveLevel = function() {
    this.stripNewLinesFromTexts();
    this.refreshEditor();

    var json = {};
    json["filename"] = this.filename;
    json["data"] = this.leveltext + "\n\n" + this.levelprops;

    save_file(json);
};

Level.prototype.isSaved = function() {
    return this.savebutton.hasClass("btn-success");
};

Level.prototype.resetSaveButton = function() {
    this.savebutton.removeClass("btn-primary");
    this.savebutton.removeClass("btn-success");
};

Level.prototype.stripNewLinesFromTexts = function() {
    while (this.leveltext.endsWith('\n'))
        this.leveltext = this.leveltext.substring(0, this.leveltext.length - 1);

    while (this.levelprops.startsWith('\n'))
        this.levelprops = this.levelprops.substring(1, this.levelprops.length);
};