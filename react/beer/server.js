import seed from "./seed"
const express = require('express');
const http = require('http');
const socketio = require('socket.io');

var app = express();
var server = http.createServer(app);
//var io = socketio(server, {'path': '/socket.io'});
var io = socketio(server);

app.get('/', function(request, response) {
    response.send("Hello, there!");
});

io.on('connection', function(socket) {
    //send data to client
    setInterval(function(){
        socket.emit('date', {'date': new Date()});
    }, 1000);

    seed.getSensors(function(name) {
        socket.emit('sensor', {'name': name});
    });
});

/* start the server */
server.listen(8000, () => {
    console.log('server listening on port 8000');
});
