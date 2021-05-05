import React, { Component } from 'react';
import './App.css';

class Buttons extends Component {
    constructor(props) {
        super(props);
        this.state = {
            targetTemp: 0
        }
        this.updateInput = this.updateInput.bind(this);
    }
    
    async startSession() {
        console.log("starting the session");
        const response = await fetch(`${process.env.REACT_APP_BASE_URL}/?state=1`, {
            method: "PUT",
            headers: {
                "Accept": "application/json"
            }
        });
        const result = await response.json();
        window.state = result.state;
        console.log(window.state);
    }

    async stopSession() {
        console.log("stopped the session");
        const response = await fetch(`${process.env.REACT_APP_BASE_URL}/?state=0`, {
            method: "PUT",
            headers: {
              "Accept": "application/json",
            },
          });
        const result = await response.json();
        window.state = result.state;
        console.log(window.state);
    }

    async newSession() {
        console.log("creating new session");
        const response = await fetch(process.env.REACT_APP_BASE_URL, {
          method: "POST",
          headers: {
            Accept: "application/json",
          },
        });

        const result = await response.json();
        window.session = result.session;

        console.log(window.session);
    }

    async setTemperature() {
        const response = await fetch(`${process.env.REACT_APP_BASE_URL}/?temp=${this.state.targetTemp}` , {
            method: "PUT",
            headers: {
                "Accept": "application/json"
            }
        });

        const result = await response.json();
        window.targetTemp = result.temp;

        console.log(window.targetTemp);
    }

    async updateInput(e) {
        await this.setState({targetTemp: e.target.value});
        console.log(this.state.targetTemp);
    }

    render() {
        return (
            <div className='collumn' id='buttons'>
                <div className='button' id='start' onClick={() => this.startSession()}>Start</div>
                <div className='button' id='stop' onClick={() => this.stopSession()}>Stop</div>
                <div className='button' id='new' onClick={() => this.newSession()}>New session</div>
                <div>

                </div>
                <input className='tempInput' type="number" step="0.1" onChange={this.updateInput}></input>
                <div className='button' id='temp' onClick={() => this.setTemperature()}>Set target Temperature</div>
            </div>
        );
    }
}

export default Buttons;