import React from 'react';

class App extends React.Component {
    constructor() {
        super();
        this.state = {
            "sensors": [],
            "count": 0
        }
        this.setStateHandler = this.setStateHandler.bind(this);
    }

    setStateHandler() {
        var sensors = this.state.sensors;
        sensors.push(this.state.count++);
        this.setState({"sensors": sensors});
    }

    render() {
        return (
            <div>
                <p>Available sensors</p>
                <button onClick={this.setStateHandler}>update</button>
                <p> Count = <span> {this.state.count} </span></p>
                <Sensorlist sensors={this.state.sensors}/>
            </div>
        );
    }
}

class Sensorlist extends React.Component {
    render() {
        return (
            <div>
                <ul>
                    {/* this.props.sensors.map((sensor) => <li> {sensor} </li>) */}
                </ul>
            </div>
        );
    }
}

export default App;