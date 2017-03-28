import React, { Component } from 'react';
import io from 'socket.io-client';

//let socket = io('http://localhost:8000', {path: '/api/socket.io/'});
let socket = io('http://localhost:8000');

class App extends Component {

    constructor(props) {
        super(props);
        this.handleDate = this.handleDate.bind(this);
        this.handleSensor = this.handleSensor.bind(this);
        this.state = {
            date: {},
            sensors: []
        };
        console.log('App constructed');
    }

    componentDidMount() {
        socket.on('date', this.handleDate);
        socket.on('sensor', this.handleSensor);
    }

    componentWillUnmount() {
        socket.removeListener('date', this.handleDate);
    }

    handleDate(data) {
        this.setState({date: data.date});
    }

    handleSensor(data) {
        var s = this.state.sensors;
        s.push(data.name);
        this.setState({"sensors": s});
    }

    render() {
        return (
            <div className="App">
                <h3> Time on server </h3>
                <div> {this.state.date.toString()} </div>
                <Sensorlist
                    sensors={ this.state.sensors }
                    />
            </div>
        );
    }
}

class Sensorlist extends React.Component {
    render() {
        return (
            <div>
                <h3>Available Sensors</h3>
                <ul>
                    { this.props.sensors.map((sensor) => <li> {sensor} </li>) }
                </ul>
            </div>
        );
    }
}

export default App;
