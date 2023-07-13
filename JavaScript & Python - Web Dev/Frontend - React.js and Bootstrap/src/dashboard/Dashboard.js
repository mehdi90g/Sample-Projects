import React from 'react'
import  Charts  from './Charts'


export const Dashboard = () => {

    return (
        <div className="container">
            <br/>
            <h2>
                Data Visualization: Car sales
            </h2>
            <hr/>
            <br/>
            <div>
                 <Charts />
            </div> 
        </div>
    )
}
