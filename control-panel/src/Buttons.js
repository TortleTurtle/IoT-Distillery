import React, { Component } from 'react';
import './App.css';

class Buttons extends Component {
    constructor(props){
        super(props);
    }
    
    async startSession(){
        console.log("started the session");
    }
    async stopSession(){
        console.log("stopped the session");
    }
    async newSession(){
        console.log("created a new session");
    }

    render() {
        return (
            <div className='collumn' id='buttons'>
                <div className='button' id='start' onClick={() => this.startSession()}>Start</div>
                <div className='button' id='stop' onClick={() => this.stopSession()}>Stop</div>
                <div className='button' id='new' onClick={() => this.newSession()}>New session</div>
            </div>
        );
    }
}

export default Buttons;