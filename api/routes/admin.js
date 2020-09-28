const express = require("express");
const router = express.Router();
const mysql = require('mysql2/promise');
require('dotenv/config');

//get temperature data
router.get('/:id', async (req, res) => {
    const sessionId = req.params.id;
    const query = `SELECT sessions.id, datatime.time, datatime.temperature FROM sessions
                    INNER JOIN datatime ON sessions.id=datatime.session_id
                    WHERE sessions.id = '${sessionId}'`;
    try {
        const connection = await mysql.createConnection({
            host: process.env.DB_HOST,
            port: process.env.DB_PORT,
            user: process.env.DB_USER,
            database: process.env.DB
        });
        const [rows, fields] = await connection.query(query);
        await connection.close();
    
        res.send(rows);
    } catch (e) {
        console.error(e);
        let response = {
            message: e
        }
        res.send(response);
    }
});

//start or stop distilling and set target temperature.
router.put('/', async (req, res) => {
    let response = {};
    //Send back message if no queries are present.
    if (Object.keys(req.query).length < 1) {
      res.status(400);
      response.message = "Use the query 'state' to start or stop distilling. Use temp to set target temperature";
    }
    //set state of the process
    if (req.query.state){
        state = req.query.state;
        response.state = state;
    }
    //set target temperature
    if (req.query.temp) {
        temp = req.query.temp;
        response.temp = temp;
    }
    res.send(response);
});

//create a new distilling session.
router.post('/', async (req, res) => {
    let response = {};

    const connection = await mysql.createConnection({
      host: process.env.DB_HOST,
      port: process.env.DB_PORT,
      user: process.env.DB_USER,
      database: process.env.DB,
    });

    let query = "INSERT INTO sessions (`date`) VALUES (CURRENT_DATE)";
    await connection.query(query);
    query = "SELECT MAX(id) AS id FROM sessions";
    //get last created session
    const [rows, fields] = await connection.query(query);
    session = rows[0].id;
    await connection.close();

    response.session = session;
    
    res.send(response);
});

module.exports = router;