/* Simple HTTP server example using node.js */

var http = require('http');

//Lets define a port we want to listen to
const PORT=8080; 

//Create a server
var server = http.createServer(function (request, response) {
    console.log("request received for URL " + request.url);
    response.end('Requested URL is ' + request.url);
});

//Lets start our server
server.listen(PORT, function(){
    //Callback triggered when server is successfully listening. Hurray!
    console.log("Server listening on: http://localhost:%s", PORT);
});
