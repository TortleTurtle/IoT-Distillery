const SerialPort = require('serialport');
const Delimiter = require('@serialport/parser-delimiter');
//Define serial port here. For me its COM7, standard baudRate is 9600.
const port = new SerialPort('COM7', {baudRate: 9600 });
const parser = port.pipe(new Delimiter({ delimiter: "[" }));

const fetch = require("node-fetch");
const url = "http://localhost:8000";

// Read the port data
parser.on('data', function (data) {
    let string = data.toString();
    console.log(string);
    let splitString = string.split("]");
    console.log(`current temperature: ${splitString[0]}`);
    postTemperature(url, splitString[0]);
    //reply with state and temperature
    getStateTemp();
});

async function postTemperature(url, temp) {
  try {
    const response = await fetch(`${url}/arduino/`, {
      method: "POST",
      headers: {
        "Content-Type": "application/json"
      },
      body: JSON.stringify({
        temp: temp
      }),
    });

    const decodedRes = await response.json();

    console.log(decodedRes);
    return true;
  } catch (e) {
    throw e;
  }
}

//Uses a get request to get the data from the express-API and write it to the serial port.
async function getStateTemp() {
  try {
    const response = await fetch(`${url}/arduino/`, {
      method: "GET",
      headers: {
        "Accept": "application/json"
      }
    });

    const decodRes = await response.json();
    console.log(decodRes);

    //form data into a string so it can be send over serial.
    const string = `<${decodRes.state}, ${decodRes.temp}>`;
    console.log(string);

    //send to arduino via serial.
    port.write(string);
  } catch (e) {
    throw e;
  }
}