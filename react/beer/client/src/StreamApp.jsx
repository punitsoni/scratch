import React, {Component} from 'react';
import SensorCard from './SensorCard';
import io from 'socket.io-client';

class StreamApp extends Component {

    constructor(props) {
        super(props);
        this.onSensorInfo = this.onSensorInfo.bind(this);
        this.onServerDisconnected = this.onServerDisconnected.bind(this);

        this.state = {
            sensors: [],
        };
    }

    componentDidMount() {
        this.socket = io('http://localhost:8000');
        this.socket.on('error', (error) => {
            console.log('socket.io: ', error.toString());
        });
        this.socket.on('connect_error', (error) => {
            console.log('Failed to connect: ', error.toString());
        });
        this.socket.on('sensor_info', this.onSensorInfo);
        this.socket.on('disconnected', this.onServerDisconnected);
        this.socket.emit('get_sensors');
    }

    componentWillUnmount() {
        //this.socket.removeListener('sensor_info', this.onSensorInfo);
        //this.socket.removeListener('disconnected', this.onServerDisconnected);
        this.socket.disconnect();
        console.log("unmounted");
    }

    onServerDisconnected() {
        console.log('server disconnected');
        this.setState({sensors: []});
    }

    onSensorInfo(sensor_info) {
        var slist = this.state.sensors;
        slist.push(sensor_info);
        this.setState({sensors: slist});
    }

    render() {
        return (
            <div>
                {this.state.sensors.map((sensor) => (
                    <SensorCard
                        id={sensor.id}
                        key={sensor.id}
                        socket={this.socket}
                        sensor_info={sensor}
                    />
                ))}
            </div>
        );
    }
}

export default StreamApp;