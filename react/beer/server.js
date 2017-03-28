import seed from "./seed"
import express from "express"
import http from "http"
import socket_io from "socket.io"

var app = express();
var server = http.createServer(app);
var io = socket_io(server);

app.get('/', function(request, response) {
    response.send("Hello, there!");
});

io.on('connection', function(socket) {
    /* send Date to client every second */
    setInterval(function() {
        socket.emit('date', {'date': new Date()});
    }, 1000);

    seed.getSensors(function(sensor) {
        socket.emit("sensor", sensor);
    });

    socket.on('start', function(data) {
       seed.start(data.id, function(sample) {
           socket.emit('sample', sample);
       });
    });

    socket.on('stop', function(data) {
        seed.stop(data.id);
    })
});

/* start the server */
server.listen(8000, () => {
    console.log('API server listening on port 8000');
});
