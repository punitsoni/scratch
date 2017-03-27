var http = require("http");
var url = require('url');
var fs = require('fs');
var io = require('socket.io');
var server = http.createServer();

server.listen(8000);

var listener = io.listen(server);

import seed from "./seed"


listener.sockets.on('connection', function(socket){
    //send data to client
    setInterval(function(){
        socket.emit('date', {'date': new Date()});
    }, 1000);

    seed.getSensors(function(name) {
        socket.emit('sensor', {'name': name});
    });
});

console.log('server listening on port 8000');
