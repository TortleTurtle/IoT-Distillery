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
        const response = await fetch('http://localhost:8000/admin/16');
        const result = await response.json();
        
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