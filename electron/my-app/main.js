'use strict';

var app = require('app');
var BrowserWindow = require('browser-window');

var win = null;

app.on('ready', function() {
    win = new BrowserWindow({
        height: 600,
        width: 800,
        resizable: false,
        maximizable: false,
        show: false,
    });

    win.on('closed', function() {
      win = null;
    });

    win.loadURL('file://' + __dirname + '/index.html');
    //win.loadURL('http://google.com');
    win.setMenuBarVisibility(false);
    win.show();
});

// Quit when all windows are closed.
app.on('window-all-closed', function() {
    app.quit();
});
