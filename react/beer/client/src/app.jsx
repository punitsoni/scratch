import React, {Component} from 'react';
import MuiThemeProvider from 'material-ui/styles/MuiThemeProvider';
import lightBaseTheme from 'material-ui/styles/baseThemes/lightBaseTheme';
import getMuiTheme from 'material-ui/styles/getMuiTheme';
import AppBar from 'material-ui/AppBar';
import io from 'socket.io-client';
import SensorCard from './SensorCard';

const socket = io('http://localhost:8000');

class App extends Component {

    constructor(props) {
        super(props);
        this.onSensorInfo = this.onSensorInfo.bind(this);
        this.onServerDisconnected = this.onServerDisconnected.bind(this);

        this.state = {
          sensors: [],
        };
    }

    componentDidMount() {
        socket.on('sensor_info', this.onSensorInfo);
        socket.on('disconnected', this.onServerDisconnected);
        socket.emit('get_sensors');
    }

    componentWillUnmount() {
        socket.removeListener('sensor_info', this.onSensorInfo);
        socket.removeListener('disconnected', this.onServerDisconnected);
    }

    onServerDisconnected() {
        console.log('server disconnected');
        this.setState({sensors:[]});
    }

    onSensorInfo(sensor_info) {
        var slist = this.state.sensors;
        slist.push(sensor_info);
        this.setState({sensors: slist});
    }

    render() {
        return (
            <MuiThemeProvider muiTheme={getMuiTheme(lightBaseTheme)}>
                <div>
                    <AppBar title="Sensors"/>
                    {this.state.sensors.map((sensor) => (
                        <SensorCard
                            id={sensor.id}
                            key={sensor.id}
                            socket={socket}
                            sensor_info={sensor}
                        />
                    ))}
                </div>
            </MuiThemeProvider>
        );
    }
}


export default App;