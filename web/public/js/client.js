var socket = io.connect('http://punitsoni.zapto.org:3000');

socket.on('pong', function (data) {
    console.log("pong haha");
});

socket.on('sysinfo', function (data) {
    var text = "total memory = " + data.totalMem + "<br>"
    text +=  "free memory = " + data.freeMem + "<br>"
    $('#sysinfo').html(text);
});

$(document).ready(function() {
    $("#hello").click(function(){
        socket.emit('ping', { duration: 2 });
    });
});
