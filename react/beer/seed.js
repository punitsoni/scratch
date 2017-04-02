
var sensors = [
    {
        id: 0,
        name: "ACCEL_001",
        type: "accel",
    },
    {
        id: 1,
        name: "GYRO_001",
        type: "gyro",
    },
    {
        id: 2,
        name: "MAG_001",
        type: "mag",
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
        console.log("seed start");
        timer = setInterval(function(){
            var sample = {
                id: id,

                data: [
                    10 * Math.random(),
                    10 * Math.random(),
                    10 * Math.random()
                ]
            };
            console.log("sample generated");
            on_sample(sample);
        }, 100);
    },

    stop: function(id) {
        console.log("seed stop");
        clearInterval(timer);
    }
};

export default seed;