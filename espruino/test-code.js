var led = Pin(2);
var WIFI_SSID = "Hydra";
var WIFI_PASS = "K5x48Vz3";

setInterval(function() {
  digitalWrite(led, false);
  setTimeout(function() {
    digitalWrite(led, true);
  }, 50);
}, 2000);

var wifi = require("Wifi");

function onInit() {
  console.log("HELLO from espruino");
  
  /* Connect to AP */
  wifi.connect(WIFI_SSID, { password:WIFI_PASS }, function(ap) {
    console.log("connected to ", WIFI_SSID);
    wifi.getIP(function(ip) {
      console.log("ip : ", ip);
    });
  });
  
}

onInit();