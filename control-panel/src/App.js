import React, {Component} from 'react';
import Graph from './Graph';
import Buttons from './Buttons';
import './App.css';
require('dotenv/config');

class App extends Component {
  constructor(props) {
    super(props);

    window.session = 0;
    window.state = false;
    window.targetTemp = 0;
  }

  render() {
    return (
      <div className="App">
        <div className="row">
          <Graph/>
          <Buttons/>
        </div>
      </div>
    );
  }
}

export default App;