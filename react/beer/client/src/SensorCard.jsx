import React, {Component} from 'react';
import FlatButton from 'material-ui/FlatButton';
import {Card, CardActions, CardHeader, CardText} from 'material-ui/Card';

import injectTapEventPlugin from 'react-tap-event-plugin';

injectTapEventPlugin();

class SensorCard extends Component {
    constructor(props) {
        super(props);
        this.sample_msg_key = `sensor_sample_${this.props.id}`;
        this.handleSensorSample = this.handleSensorSample.bind(this);
        this.onButtonClick = this.onButtonClick.bind(this);

        this.state = {
            data: [0.0, 0.0, 0.0],
            is_streaming: false
        };
    }

    componentDidMount() {
        console.log(`key= ${this.sample_msg_key}`);
        this.props.socket.on(this.sample_msg_key, this.handleSensorSample);
    }

    componentWillUnmount() {
        this.props.socket.removeListener(
            this.sample_msg_key, this.handleSensorSample);
    }

    handleSensorSample(sample) {
        this.setState({"data": sample.data});
    }

    onButtonClick() {
        if (this.state.is_streaming) {
            console.log("stop " + this.props.sensor_info.type);
            this.props.socket.emit('stop', {id: this.props.sensor_info.id});
            this.setState({is_streaming: false});
        } else {
            console.log("start " + this.props.sensor_info.type);
            this.props.socket.emit('start', {id: this.props.sensor_info.id});
            this.setState({is_streaming: true});
        }
    }

    render() {
        var sensor_name = this.props.sensor_info.name;
        var sensor_type = this.props.sensor_info.type;
        var button_label = "Start";
        var button_primary = true;
        var button_secondary = false;
        if (this.state.is_streaming) {
            button_label = "Stop";
            button_primary = false;
            button_secondary = true;
        }

        return (
            <Card>
                <CardHeader
                    title={sensor_name}
                    subtitle={sensor_type}
                />
                <CardText style={{padding: "0px"}}>
                    <SensorData
                        data={this.state.data}
                    />
                </CardText>
                <CardActions>
                    <FlatButton
                        label={button_label}
                        primary={button_primary}
                        secondary={button_secondary}
                        onClick={this.onButtonClick}
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
        var ul_style = {
            margin: "1px"
        }
        return (
            <ul style={ul_style}>
                {this.props.data.map((item, idx) => (
                    <li key={idx} style={style}>
                        <span style={{fontSize: "20px"}}>{item.toFixed(4)}</span>
                    </li>
                ))}
            </ul>
        );
    }
}

export default SensorCard;
