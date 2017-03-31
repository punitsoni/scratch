import React, {Component} from 'react';
import FlatButton from 'material-ui/FlatButton';
import {Card, CardActions, CardHeader, CardText} from 'material-ui/Card';

import injectTapEventPlugin from 'react-tap-event-plugin';

injectTapEventPlugin();

class SensorCard extends Component {
    constructor(props) {
        super(props);

        this.sample_msg_key = 'sensor_sample_' + this.props.id;

        this.handleSensorSample = this.handleSensorSample.bind(this);
        this.onStart = this.onStart.bind(this);

        this.state = {
            data: [0.0, 0.0, 0.0]
        };
    }

    componentDidMount() {
        this.props.socket.on(
            this.sample_msg_key, this.handleSensorSample);
    }

    componentWillUnmount() {
        this.props.socket.removeListener(
            this.sample_msg_key, this.handleSensorSample);
    }

    handleSensorSample(sample) {
        this.setState({"data": sample.data});
    }

    onStart() {
        console.log("start " + this.props.sensor_info.type);
        //this.props.socket.emit('start', {id: this.props.sensor_info.id});
    }

    render() {
        var sensor_name = this.props.sensor_info.name;
        var sensor_type = this.props.sensor_info.type;
        return(
            <Card>
                <CardHeader
                    title={sensor_name}
                    subtitle={sensor_type}
                />
                <CardText>
                    <SensorData data={this.state.data}/>
                </CardText>
                <CardActions>
                    <FlatButton
                        label="Start" primary={true}
                        onTouchTap={this.onStart()}
                    />
                </CardActions>
            </Card>
        );
    }
}

class SensorData extends Component {
    render() {
        var style = {
            display: "inline",
            listStyleType: "none",
            paddingLeft: "10px",
            paddingRight: "40px"
        };
        return (
            <ul style={style}>
                {this.props.data.map((item, idx) => (
                    <li key={idx} style={style}>
                        <span style={{fontSize: "20px"}}>{item}</span>
                    </li>
                ))}
            </ul>
        );
    }
}

export default SensorCard;
