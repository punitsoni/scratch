var SerialPortModule = require('serialport');
var SerialPort = SerialPortModule.SerialPort;


SerialPortModule.list(function(err, ports) {
    ports.forEach(function(port) {
      console.log(port.comName);
      console.log(port.manufacturer);
  });
});

var serialPort = new SerialPort('COM73');
serialPort.on('data', function(data) {
  console.log('data received: ' + data);
});

serialPort.on('open', function () {
  console.log('open');
  serialPort.write('ls\n', function(err, results) {
    console.log('err ' + err);
    console.log('results ' + results);
  });
});
