
var sensors = [
    "accel",
    "gyro",
    "mag"
]

var seed = {
    getSensors : (handler) => {
        for(var i=0; i<sensors.length; i++) {
            handler(sensors[i]);
        }
    }
}

export default seed;