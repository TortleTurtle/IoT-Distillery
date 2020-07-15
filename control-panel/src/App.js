import React, {Component} from 'react';
import Graph from './Graph';
import './App.css';

class App extends Component {
  constructor(props) {
    super(props);

    this.state = {
      graphData: {}
    }
  }
  componentWillMount() {
    this.getGraphData();
  }

  async getGraphData() {
    console.log("Fetching data");
    const response = await fetch('http://localhost:8000/admin/16');
    const result = await response.json();
    console.log(result);

    let time = [];
    let temperature = []; 
    result.forEach(data => {
      console.log(data);
      time.push(data.time);
      temperature.push(data.temperature);
    });

    this.setState({
      graphData: {
        labels: time,
        datasets: [{
          label: "Temperature",
          data: temperature
        }]
      }
    });

    console.log(time);
  }

  render() {
    return (
      <div className="App">
        <div className="row">
          <Graph data={this.state.graphData}/>
        </div>
      </div>
    );
  }
}

export default App;
