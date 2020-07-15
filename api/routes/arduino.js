const express = require("express");
const router = express.Router();
const mysql = require('mysql2/promise');

//get state and target temperature
router.get('/', async (req, res) => {
    let response = {};

    response.state = state;
    response.temp = temp;

    res.send(response);
})
//post temperature data
router.post("/", async (req, res) => {
    console.log(req.body);
    const temp = req.body.temp;
    let response = {};
    if (temp) {
        try {
            const query = `INSERT INTO datatime (session_id, \`time\`, temperature) VALUES (${session}, CURRENT_TIME, ${temp})`;
            const connection = await mysql.createConnection({
                host: process.env.DB_HOST,
                port: process.env.DB_PORT,
                user: process.env.DB_USER,
                database: process.env.DB,
            });
            const result = await connection.query(query);
            await connection.close();

            response.message = "succes";
            res.send(response);
        } catch (e) {
            console.error(e);
            res.status(500);
            response.message = e;
            res.send(response);
        }
    } else {
        res.status(400);
        response.message = "The query 'temp' must be present";
        res.send(response);
    }
});

module.exports = router;