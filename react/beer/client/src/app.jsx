import React, { Component } from 'react';
//import './App.css';
//import logo from './logo.svg';
import io from 'socket.io-client';

let socket = io.connect();

class App extends Component {

    constructor(props) {
        super(props);
        this.handleDate = this.handleDate.bind(this);
        this.state = {
            date: {}
        };
        console.log('App constructed');
    }

    componentDidMount() {
        socket.on('date', this.handleDate);
    }

    componentWillUnmount() {
        socket.removeListener('date', this.handleDate);
    }

    handleDate(data) {
        this.setState({date: data.date});
    }

    render() {
        return (
            <div className="App">
                <div id="date">date = {this.state.date.toString()}</div>
            </div>
        );
    }
}

export default App;
