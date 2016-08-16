const PORT = 3000;

var io = require('socket.io').listen(PORT);

io.sockets.on('connection', function(socket) {
    console.log("connection");
    socket.emit('news', { hello: 'world' });
});
