
document.getElementById("button").onclick = onButtonClick;

var lampState = false;

var ws;

if ("WebSocket" in window)
{
    var ws = new WebSocket("ws://10.0.1.73");

    ws.onopen = function()
    {
      // Web Socket is connected, send data using send()
      ws.send("HELLO");
      console.log("Message sent...");
    };

    ws.onmessage = function (evt)
    {
      var received_msg = evt.data;
      console.log("Message received: " + received_msg);
      if (received_msg == "S_ON") {
        document.getElementById("button").style = "color: #a7e7a7";
        lampState = true;
      } else if (received_msg == "S_OFF") {
        document.getElementById("button").style = "color: #a7a7a7";
        lampState = false;
      }
    };

    ws.onclose = function()
    {
      // websocket is closed.
      console.log("Connection is closed.");
    };
} else {
    alert("WebSocket is not supported by your Browser!");
}

function onButtonClick() {
    if (lampState == true) {
        ws.send("C_OFF");
    } else {
        ws.send("C_ON");
    }
}
