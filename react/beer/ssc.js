'use strict';

const net = require('net');

class Connection {
    constructor(connect_cb) {
        this.socket = net.connect({port:5000}, () => {
            console.log(`connection ${Connection.next_id}`);
            connect_cb();
            Connection.next_id++;
        });
        this.socket.on('error', (error) => {
           console.log(error.toString());
        });
    }

    send_request(data) {
        console.log('sending request');
        this.socket.write(data);
    }

    on(event, cb) {
        if (event === 'event') {
            this.socket.on('data', (data) => {
                // decode packet
                cb('ggg');
            });
        }
    }
}

Connection.next_id = 0;

const ssc = {
    connect: (cb) => {
        return new Connection(cb);
    }
};

let conn = ssc.connect(() => {
    console.log('connected');
    conn.send_request('yyy');
});

conn.on('event', (data) => {
    console.log(`event: ${data}`);
});

export default ssc;