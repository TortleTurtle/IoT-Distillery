//require the node-fetch function
const fetch = require("node-fetch");
const url = "http://localhost:8000";
const temp = 21.25;
async function postTemperature(url, temp) {
  
    console.log(temp);

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

    const json = await response.json();

    console.log(json);

    return json;
  } catch (e) {
    throw e;
  }
}

postTemperature(url, temp);