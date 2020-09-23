const express = require('express');
const cors = require('cors');
const bodyParser = require('body-parser');
require('dotenv/config');

//global variables
global.state = false;
global.session = 16;
global.temp = 0;

const app = express();
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: true }));
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