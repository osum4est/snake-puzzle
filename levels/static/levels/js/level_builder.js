/**
 * Created by osum4est on 4/21/17.
 */

$(document).ready(function() {
    var cm = CodeMirror.fromTextArea($("#level_textarea").get(0), {
        matchBrackets: true,
        mode: {name: "javascript", json: true },
        lineNumbers: true,
        theme: "monokai"
    });
    cm.setSize("100%", "100%");

    $('body').on('contextmenu', '#level_canvas', function(e){ return false; });
    $("#level_canvas").get(0).onselectstart = function() { return false; };



    get_file("001.lvl");
});

function levelClick() {
    $("#tab-props").removeClass("active");
    $("#tab-level").addClass("active");
    if (level !== undefined && level !== null && !Level.editingProps()) {
        level.refreshEditor();
    }
}

function propsClick() {
    $("#tab-props").addClass("active");
    $("#tab-level").removeClass("active");
    if (level !== undefined && level !== null && Level.editingProps()) {
        level.refreshEditor();
    }
}

function saveClick() {
    level.saveLevel();
}

function newClick() {
    if (level !== undefined && !level.isSaved()) {
        BootstrapDialog.confirm("All unsaved changes will be lost. Are you sure you want to continue?", function (result) {
            if (result) {
                newFileDialog();
            }
        });
    }
    else {
        newFileDialog();
    }
}

function newFileDialog() {
    fileDialog("New File", "Enter file name:", "Create", function(text) {
        create_file(text);
    })
}

function fileDialog(title, inputprompt, buttontext, onclick) {
    BootstrapDialog.show({
        title: title,
        message: $(
        '<label for="file-input">' + inputprompt + '</label>' +
        '<div class="input-group">' +
            '<input type="text" id="file-input" class="form-control" placeholder="filename" aria-describedby="basic-addon1">' +
            '<span class="input-group-addon" id="basic-addon1">.lvl</span>' +
        '</div>'),
        size: BootstrapDialog.SIZE_SMALL,
        buttons: [{
            label: buttontext,
            cssClass: 'btn-primary',
            hotkey: 13,
            action: function(dialogRef) {
                var text = $("#file-input").val();
                if (text !== undefined && text !== "") {
                    onclick(text);
                    dialogRef.close();
                }
            }
        }]
    });
}

function renameClick() {
    fileDialog("Rename File", "Enter new file name:", "Rename", function(text) {
        renameFile(level.filename, text);
        level.filename = text + ".lvl";
    });
}

function duplicateClick() {
    if (!level.isSaved()) {
        BootstrapDialog.confirm("All unsaved changes will be lost. Are you sure you want to continue?", function (result) {
            if (result) {
                duplicateDialog();
            }
        });
    }
    else {
        duplicateDialog();
    }
}

function duplicateDialog() {
    fileDialog("Duplicate File", "Enter new duplicate's name:", "Duplicate", function(text) {
        duplicateFile(level.filename, text);
    });
}

function unloadLevel() {
    level.codebox.setValue("");
    level.clearCanvas();
    level.setSaved();
    delete level;
    level = undefined;
    $("#file-picker").html("Files" + '<span class="caret"></span>');
}

function deleteClick() {
    BootstrapDialog.confirm("Are you sure you want to delete " + level.filename + "? This cannot be undone!", function (result) {
       if (result) {
           deleteFile(level.filename);
       }
    });
}

function level_saved_success() {
    level.setSaved();
}

function load_level(file, data) {
    level = new Level(file, data);
}

function refreshFilesList(filesList) {
    if (filesList !== undefined) {
        $("#files-dropdown").empty();
        for (var i = 0; i < filesList.length; i++) {
            $("#files-dropdown").append(
                "<li><a onclick=get_file('" + filesList[i] + "') href='#'>" + filesList[i] + "</a></li>"
            )
        }
    }
}

function error(message) {
    BootstrapDialog.show({
        type: BootstrapDialog.TYPE_DANGER,
        title: "Error",
        message: message,
        size: BootstrapDialog.SIZE_SMALL,
        buttons: [{
            label: 'OK :(',
            action: function(dialogRef) {
                dialogRef.close();
            }
        }]
    });
}

var level;
