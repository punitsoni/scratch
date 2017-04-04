import React, {Component} from 'react';
import MuiThemeProvider from 'material-ui/styles/MuiThemeProvider';
import lightBaseTheme from 'material-ui/styles/baseThemes/lightBaseTheme';
import getMuiTheme from 'material-ui/styles/getMuiTheme';
import AppBar from 'material-ui/AppBar';
import io from 'socket.io-client';
import Drawer from 'material-ui/Drawer';
import MenuItem from 'material-ui/MenuItem';
import {Card, CardActions, CardHeader, CardText} from 'material-ui/Card';

import SensorCard from './SensorCard';

const socket = io('http://localhost:8000');

class App extends Component {

    MODE_STREAM = "stream";
    MODE_MONITOR = "monitor";

    constructor(props) {
        super(props);

        this.getMainApp = this.getMainApp.bind(this);
        this.changeMode = this.changeMode.bind(this);

        this.state = {
            mode: this.MODE_STREAM,
            drawer_open: false
        };
    }

    componentDidMount() {
    }

    componentWillUnmount() {
    }

    getMainApp() {
        if (this.state.mode === this.MODE_STREAM) {
            return <StreamApp/>;
        } else {
            return <MonitorApp/>;
        }
    }

    onMainMenuClick = () => this.setState({drawer_open: !this.state.drawer_open});

    drawerClose = () => this.setState({drawer_open: false});

    changeMode(mode) {
        this.setState({mode:mode});
        this.drawerClose();
    }

    render() {
        return (
            <MuiThemeProvider muiTheme={getMuiTheme(lightBaseTheme)}>
                <div>
                    <AppBar title="Sensors"
                            onLeftIconButtonTouchTap={this.onMainMenuClick}
                    />
                    {this.getMainApp()}
                    <Drawer
                        docked={false}
                        width={200}
                        open={this.state.drawer_open}
                        onRequestChange={(open) => this.setState({drawer_open: open})}
                    >
                        <Card zDepth={0}>
                            <div
                                style={{height:"100px", width:"100%", clear:"both"}}>
                            </div>
                        </Card>
                        <MenuItem onTouchTap={() => this.changeMode(this.MODE_STREAM)}>
                            Stream
                        </MenuItem>
                        <MenuItem onTouchTap={() => this.changeMode(this.MODE_MONITOR)}>
                            Monitor
                        </MenuItem>
                    </Drawer>
                </div>
            </MuiThemeProvider>
        );
    }
}

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
        socket.on('sensor_info', this.onSensorInfo);
        socket.on('disconnected', this.onServerDisconnected);
        socket.emit('get_sensors');
    }

    componentWillUnmount() {
        socket.removeListener('sensor_info', this.onSensorInfo);
        socket.removeListener('disconnected', this.onServerDisconnected);
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
                        socket={socket}
                        sensor_info={sensor}
                    />
                ))}
            </div>
        );
    }
}

class MonitorApp extends Component {

    constructor(props) {
        super(props);
        this.state = {
        };
    }

    componentDidMount() {
    }

    componentWillUnmount() {
    }

    render() {
        return (
            <div>
                Hello
            </div>
        );
    }
}


export default App;