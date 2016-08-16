/* Simple HTTP server example using node.js */
var app = require('http').createServer(handler);
var url = require('url');
var fs = require('fs');
var io = require('socket.io').listen(app);
var os = require('os');
app.listen(3000, function() {
    console.log("Server started on port 3000");
    console.log("dir = " + __dirname);
});

// Http handler function
function handler (req, res) {
    // Using URL to parse the requested URL
    var path = url.parse(req.url).pathname;

    console.log("request for path " + path);

    // Managing the root route
    if (path == '/') {
        index = fs.readFile(__dirname+'/public/index.html',
            function(error,data) {

                if (error) {
                    res.writeHead(500);
                    return res.end("Error: unable to load index.html");
                }

                res.writeHead(200,{'Content-Type': 'text/html'});
                res.end(data);
            });
    // Managing the route for the javascript files
    } else if( /\.(js)$/.test(path) ) {
        index = fs.readFile(__dirname+'/public'+path,
            function(error,data) {

                if (error) {
                    res.writeHead(500);
                    return res.end("Error: unable to load " + path);
                }

                res.writeHead(200,{'Content-Type': 'text/plain'});
                res.end(data);
            });
    } else {
        res.writeHead(404);
        res.end("Error: 404 - File not found.");
    }

}

// Web Socket Connection
io.sockets.on('connection', function (socket) {

  // If we recieved a command from a client to start watering lets do so
  socket.on('ping', function(data) {
      console.log("ping");
      socket.emit("pong", os.cpus());
  });

  setInterval(function(){
      socket.emit('sysinfo', { totalMem: os.totalmem(),
           freeMem: os.freemem() });
  }, 1000);

});
