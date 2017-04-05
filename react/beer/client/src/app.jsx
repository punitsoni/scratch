import React, {Component} from 'react';
import MuiThemeProvider from 'material-ui/styles/MuiThemeProvider';
import lightBaseTheme from 'material-ui/styles/baseThemes/lightBaseTheme';
import getMuiTheme from 'material-ui/styles/getMuiTheme';
import AppBar from 'material-ui/AppBar';
import Drawer from 'material-ui/Drawer';
import MenuItem from 'material-ui/MenuItem';
import {Card, CardActions, CardHeader, CardText} from 'material-ui/Card';
import StreamApp from './StreamApp';
import MonitorApp from './MonitorApp';

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

export default App;