import React from 'react';
import ReactDOM from 'react-dom';
import App from './app.jsx';

ReactDOM.render(<App />, document.getElementById('app'));

import seed from './sensors.js';

seed.on_sensor_available = function(sensor) {
    console.log('sensor ' + sensor.name + 'available')
}
