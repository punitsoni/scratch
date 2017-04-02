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
        scoket.
        socket.on('sensor', this.handleSensor);
    }

    componentWillUnmount() {
        socket.removeListener('date', this.handleDate);
    }

    handleDate(data) {
        this.setState({date: data.date});
    }

    handleSensor(sensor) {
        var slist = this.state.sensors;
        slist.push(sensor);
        this.setState({"sensors": slist});
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
                {
                    this.props.sensors.map((sensor) => {
                        return(
                            <SensorItem
                                key={sensor.id.toString()}
                                name={sensor.name}
                                datatype={sensor.datatype}
                                value={"value"}
                            />
                        );
                    })
                }
            </div>
        );
    }
}

class SensorItem extends React.Component {
    render() {
        return (
            <div className="well well-sm">
                <h4>{ this.props.name }</h4>
                <button type="button" className="btn btn-success">start</button>
                <p>{this.props.datatype}</p>
                <p>value = {this.props.value}</p>
                <hr/>
            </div>
        );
    }
}

export default App;
