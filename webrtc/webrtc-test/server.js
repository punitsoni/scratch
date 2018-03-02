const fs = require('fs')
const https = require('https')
const express = require('express')
const app = express()
const PORT = 3000

app.use(express.static('public'))

//app.get('/', (req, res) => res.send('Hello World!'))

https.createServer({
    key: fs.readFileSync('key.pem'),
    cert: fs.readFileSync('cert.pem'),
    passphrase: "abc123"
}, app).listen(PORT,
    () => console.log('Example app listening on port 3000!'))

//app.listen(3000, () => console.log('Example app listening on port 3000!'))