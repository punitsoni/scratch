
var sensors = [
    {
        id: 0,
        name: "ACCEL_001",
        datatype: "accel",
    },
    {
        id: 1,
        name: "GYRO_001",
        datatype: "gyro",
    },
    {
        id: 2,
        name: "MAG_001",
        datatype: "mag",
    },
];

var timer;

var seed = {
    getSensors : (handler) => {
        for(var i=0; i<sensors.length; i++) {
            handler(sensors[i]);
        }
    },

    start: function(id, on_sample) {
        timer = setInterval(function(){
            var sample = {
                id: id,
                data: [
                    10 * Math.random(),
                    10 * Math.random(),
                    10 * Math.random()
                ]
            };
            on_sample(sample);
        }, 1000);
    },

    stop: function(id) {
        clearInterval(timer);
    }
};

export default seed;