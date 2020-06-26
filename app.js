const express = require('express');
const mysql = require('mysql2/promise')
const cors = require('cors');
require('dotenv/config');

//global variables
global.state = "stop"
global.session = undefined;
global.temp = 0;

const app = express();
app.use(cors());

//ping
app.get('/', async (req, res) => {
    let response = {
        online: true
    }
    res.send(response);
});

//admin
const adminRoute = require('./routes/admin');
app.use('/admin', adminRoute);

//arduino
const arduinoRoute = require('./routes/arduino');
app.use('/arduino', arduinoRoute);

app.listen(process.env.PORT)