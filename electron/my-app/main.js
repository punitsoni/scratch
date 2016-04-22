'use strict';

var app = require('app');
var BrowserWindow = require('browser-window');

var mainWindow = null;

app.on('ready', function() {
    mainWindow = new BrowserWindow({
        height: 600,
        width: 800,
        resizable: false,
        maximizable: false,
    });
    mainWindow.loadURL('file://' + __dirname + '/index.html');
    mainWindow.setMenuBarVisibility(false);
});
