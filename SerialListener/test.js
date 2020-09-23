const SerialPort = require("serialport");
const Readline = require("@serialport/parser-readline");
const port = new SerialPort("COM4", { baudRate: 9600 });
const parser = port.pipe(new Readline("/n"));

const fetch = require("node-fetch");
const url = "http://localhost:8000";

// Read the port data
parser.on("data", function (data) {
  console.log(data);
  postTemperature(url, data);
});

async function postTemperature(url, temp) {
  try {
    const response = await fetch(`${url}/arduino/`, {
      method: "POST",
      headers: {
        "Content-Type": "application/json",
      },
      body: JSON.stringify({
        temp: temp,
      }),
    });

    const json = await response.json();

    console.log(json);
    return json;
  } catch (e) {
    throw e;
  }
}
