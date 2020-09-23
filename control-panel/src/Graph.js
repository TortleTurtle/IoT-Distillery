import React, {Component} from 'react';
import {Line} from 'react-chartjs-2';
import './App.css';

class Graph extends Component{
    constructor(props) {
        super(props);
        this.state = {
            graphData: {}
        }
    }

    componentWillMount(){
        this.getGraphData()
    }

    async getGraphData() {
        console.log("fetching");
        console.log(process.env.BASE_URL);
        const response = await fetch(process.env.REACT_APP_BASE_URL + '/16', {
            method: 'GET',
            headers: {
                'Accept': 'application/json'
            }
        });
        const result = await response.json();
        console.log(result);

        let time = [];
        let temperature = [];
        result.forEach(data => {
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
    }
    

    render() {
        return (
            <div className="collumn" id="graph">
                <Line data={this.state.graphData}/>
            </div>
        );
    }
}

export default Graph;