import React, {Component} from 'react';
import MuiThemeProvider from 'material-ui/styles/MuiThemeProvider';
//import Mui from './mui';
import lightBaseTheme from 'material-ui/styles/baseThemes/lightBaseTheme';
import getMuiTheme from 'material-ui/styles/getMuiTheme';

//import ReactDOM from 'react-dom';
//import RaisedButton from 'material-ui/RaisedButton';
//import FlatButton from 'material-ui/FlatButton';
import AppBar from 'material-ui/AppBar';
//import {Card, CardActions, CardHeader, CardText} from 'material-ui/Card';
import io from 'socket.io-client';

import SensorCard from './SensorCard';

const socket = io('http://localhost:8000');

class App extends Component {

    constructor(props) {
        super(props);
        this.handleSensorInfo = this.handleSensorInfo.bind(this);

        this.state = {
          sensors: [],
        };
    }

    componentDidMount() {
        socket.on('sensor_info', this.handleSensorInfo);
    }

    componentWillUnmount() {
        socket.removeListener('sensor_info', this.handleSensorInfo);
    }

    handleSensorInfo(sensor_info) {
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