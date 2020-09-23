import React, {Component} from 'react';
import Graph from './Graph';
import Buttons from './Buttons';
import './App.css';
require('dotenv/config');

class App extends Component {
  constructor(props) {
    super(props);

    this.state = {
      session: null,
      state: null,
    }
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