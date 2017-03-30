import React, {Component} from 'react';
import MuiThemeProvider from 'material-ui/styles/MuiThemeProvider';
import Mui from './mui';
import lightBaseTheme from 'material-ui/styles/baseThemes/lightBaseTheme';
import getMuiTheme from 'material-ui/styles/getMuiTheme';

//import ReactDOM from 'react-dom';
//import RaisedButton from 'material-ui/RaisedButton';
import FlatButton from 'material-ui/FlatButton';
import AppBar from 'material-ui/AppBar';
import {Card, CardActions, CardHeader, CardText} from 'material-ui/Card';

class App extends React.Component {

    render() {
        var style = {
            border: "1px solid"
        };

        return (
            <MuiThemeProvider muiTheme={getMuiTheme(lightBaseTheme)}>
            <div>
                <AppBar title="My AppBar" />
                <MyCard></MyCard>
                <MyCard></MyCard>
            </div>
            </MuiThemeProvider>
        );
    }
}

const MyCard = () => (
    <Card>
        <CardHeader
            title="LSM6DS3"
            subtitle="Accelerometer"
        />
        <CardText>
            <h2>This is some card text.</h2>
        </CardText>
        <CardActions>
            <FlatButton label="Start" primary={true}/>
        </CardActions>
    </Card>
);


const FlatButtonExampleSimple = () => (
    <div>
        <FlatButton label="Default" />
        <FlatButton label="Primary" primary={true} />
        <FlatButton label="Secondary" secondary={true} />
        <FlatButton label="Disabled" disabled={true} />
        <br />
        <br />
        <FlatButton label="Full width" fullWidth={true} />
    </div>
);

export default App;