const SerialPort = require('serialport');
const Delimiter = require('@serialport/parser-delimiter');
const port = new SerialPort('COM4', {baudRate: 9600 });
const parser = port.pipe(new Delimiter({ delimiter: "[" }));

const fetch = require("node-fetch");
const url = "http://localhost:8000";

// Read the port data
parser.on('data', function (data) {
    let string = data.toString();
    let splitString = string.split("]");
    console.log(`current temperature: ${splitString[0]}`);
    postTemperature(url, splitString[0]);
});

//set an interval to keep updating the state and target temperature.
setInterval( () => getStateTemp(), 2000); //2 seconds

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
    parser.write(string);
  } catch (e) {
    throw e;
  }
}