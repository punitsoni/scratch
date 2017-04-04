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
    console.log("client connected");

    socket.on('get_sensors', function() {
        seed.getSensors(function(sensor) {
            socket.emit("sensor_info", sensor);
        });
    });

    socket.on('start', function(data) {
        console.log("start");
        seed.start(data.id, function(sample) {
            var key = 'sensor_sample_' + data.id;
            //console.log(`sending ${key} ${sample}`);
            socket.emit(key, sample);
        });
    });

    socket.on('stop', function(data) {
        console.log("start");
        seed.stop(data.id);
    });

    socket.on('disconnect', function() {
        console.log('client disconnected');
        seed.stop(0);
    });
});

/* start the server */
server.listen(8000, () => {
    console.log('API server listening on port 8000');
});
