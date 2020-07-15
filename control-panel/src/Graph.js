import React, {Component} from 'react';
import {Line} from 'react-chartjs-2';
import './App.css';


class Graph extends Component{
    constructor(props) {
        super(props);
        this.state = {
            graphData: this.props.data
        }
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