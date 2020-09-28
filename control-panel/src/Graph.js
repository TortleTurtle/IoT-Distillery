import React, {Component} from 'react';
import {Line} from 'react-chartjs-2';
import './App.css';

class Graph extends Component{
    constructor(props) {
        super(props);
        this.state = {
            graphData: {},
            currentTemp: 0
        }
        this.getGraphData();
        setInterval( () => this.getGraphData(), 5000);
    }

    async getGraphData() {
        const response = await fetch(`${process.env.REACT_APP_BASE_URL}/${window.session}`, {
            method: 'GET',
            headers: {
                'Accept': 'application/json'
            }
        });
        const result = await response.json();

        let time = [];
        let temperature = [];
        result.forEach(data => {
            time.push(data.time);
            temperature.push(data.temperature);
        });
        let lastTemp = temperature[temperature.length - 1];

        this.setState({
            graphData: {
                labels: time,
                datasets: [{
                    label: "Temperature",
                    data: temperature
                }]
            },
            currentTemp: lastTemp
        });
    }
    

    render() {
        return (
            <div className="collumn" id="graph">
                <Line data={this.state.graphData}/>
            <div>
                <h3>Current Temerature: {this.state.currentTemp}</h3>
                <h3>Target Temperature: {window.targetTemp}</h3>
                <h3>Current State: {String(window.state)}</h3>
                </div>
            </div>
        );
    }
}

export default Graph;