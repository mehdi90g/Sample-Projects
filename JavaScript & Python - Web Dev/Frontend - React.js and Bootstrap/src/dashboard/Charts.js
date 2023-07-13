import React, { Component } from 'react'
import Chart from 'chart.js/auto';

export default class Charts extends Component {
   

	chartRef = React.createRef();

	componentDidMount() {
		const chartContext = this.chartRef.current.getContext("2d");
		
		new Chart(chartContext, {
			type: "line",
			data: {
				labels: ["Mon.", "Tues.", "Wed.", "Thurs.", "Fri.", "Sat.", "Sun."],
				datasets: [{ 
					data: [70,45,100,105,95,85,80],
					label: "Total",
					borderColor: "#05b034",
					backgroundColor: "#036e20",
					fill: false,
				}, { 
					data: [10,5,20,30,25,15,20],
					label: "Ford",
					borderColor: "#00b3d6",
					backgroundColor: "#036b80",
					fill: false,
				}, { 
					data: [30,25,50,40,30,60,35],
					label: "BMW",
					borderColor: "#ede500",
					backgroundColor:"#ada702",
					fill: false,
				}, { 
					data: [20,15,30,35,40,10,25],
					label: "Tesla",
					borderColor: "#fa3605",
					backgroundColor:"#ba2702",
					fill: false,
				}
				]
			},
		});
	}
	render() {
		return (
			<div className="container">
				<canvas
				id="myChart"
				ref={this.chartRef}
				/>
			</div>
			)
	}


}



