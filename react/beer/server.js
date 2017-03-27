var http = require("http");
var url = require('url');
var fs = require('fs');
var io = require('socket.io');

var server = http.createServer(function(request, response){
    var path = url.parse(request.url).pathname;

    switch(path){
        case '/':
            fs.readFile(__dirname + '/index.html', function(error, data){
                if (error){
                    response.writeHead(404);
                    response.write("opps index.html doesn't exist - 404");
                    response.end();
                }
                else{
                    response.writeHead(200, {"Content-Type": "text/html"});
                    response.write(data, "utf8");
                    response.end();
                }
            });
            break;
        default:
            response.writeHead(404);
            response.write("Ooops - 404");
            response.end();
            break;
    }
});

server.listen(8000);

var listener = io.listen(server);

listener.sockets.on('connection', function(socket){
    //send data to client
    setInterval(function(){
        socket.emit('date', {'date': new Date()});
    }, 1000);
});

console.log('server listening on port 8000');