var HOST = 'localhost';
var DEVICE_PORT = 5000;
var SERVER_PORT = 8001;

var express = require('express');
var app = express();
var server = require('http').createServer(app);
var io = require('socket.io')(server);

var dev_connected = false;
var client_connected = false;

var client_socket;

var device_socket;

app.use(express.static('public'));
app.get('/', function(req, res, next) {
    res.sendFile(__dirname + '/index.html');
});

function connect_device() {

    if (dev_connected) {
      return;
    }

    var net = require('net');
    device_socket = new net.Socket();

    device_socket.setEncoding('utf-8');

    device_socket.connect(DEVICE_PORT, HOST, function() {
        console.log('device connected at: ' + HOST + ':' + DEVICE_PORT);
    });

    device_socket.on('error', function() {
        console.log("could not connect to device.");
        dev_connected = false;
        device_socket.destroy();
    });

    device_socket.on('data', function(data) {
        var samples = data.split('\n');
        for (i = 0; i < samples.length - 1; i++) {
            console.log(JSON.parse(samples[i]));
            if (client_connected) {
              client_socket.emit('sample', samples[i]);
            }
        }
    });

    device_socket.on('end', function() {});

    device_socket.on('close', function() {
        console.log('Connection to device closed.');
        device_socket.destroy();
        dev_connected = false;
    });
    dev_connected = true;
}

//connect_device();

server.listen(SERVER_PORT);
console.log('Server listening at port ' + SERVER_PORT);

io.on('connection', function(socket) {
    if (client_connected) {
      console.log("only one client allowed.")
      return;
    }
    console.log('Client connected...');

    connect_device();

    socket.on('disconnect', function() {
        console.log('client disconnected');
        client_connected = false;
        if (dev_connected) {
          device_socket.destroy();
        }
    });
    client_socket = socket;
    client_connected = true;
});

process.on('SIGINT', function() {
    console.log("\nSIGINT received");
    if (client_socket) {
        client_socket.disconnect(true);
    }
    if (dev_connected) {
      device_socket.destroy();
    }
    process.exit();
});
