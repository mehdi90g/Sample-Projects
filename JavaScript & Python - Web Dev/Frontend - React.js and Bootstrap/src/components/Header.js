import React from 'react'
import APIService from '../APIService'

export const Header = (props) => {

    // The variable (function) updateRow below is to notify the parent file App.js that which row of the table is clicked and to be modified.
    const setShowFormWithData = (mltablerow) => { props.setShowFormWithData(mltablerow) }
    const setShowEmptyForm = () => {props.setShowFormWithData(
        {Dataset_Title:'', Train_Accuracy:'', Validation_Accuracy:'', Test_Accuracy:''}) }
    
    const deleteMlTableRow = (mlTableRow) => {
            APIService.deleteMlTableRow(mlTableRow.id)
            .then(() => props.reloadDeletedMlTableRow(mlTableRow))
            // .catch(error => console.log(error))      
    }
    
    

    return (
        <div className="container">
            <br/>
            <h2>
                Machine Learning Database
            </h2>
            <br/>
            <p align="justify">
                The database stores Train and Test datasets of a Machine Learning task, its title, ID, and its Training, Validation, and Test accuracies.
                Using this interface, it is also possible to perform CRUD operations on the database which is stored on the server.
            </p>
            <br/>
            <div className="container">
                <button type="button" className="btn btn-success" onClick={setShowEmptyForm}>
                    Create a New Row in Database Table
                </button>
            </div>
            <br/>
            <hr className="hr-custom"/>
            {/* for the following map function I also used the instruction in https://stackoverflow.com/questions/52219852/two-children-with-the-same-key-in-react */}
            {props.mlTable && props.mlTable.map((mlTableRow,id) => { return (
            <div className="container" key = {id}>
                <h2> {mlTableRow.id} </h2>
                <p> {mlTableRow.Dataset_Title} </p>
                <p> {mlTableRow.Train_Dataset_Upload} </p> 
                <p> {mlTableRow.Test_Dataset_Upload} </p>
                <p> {mlTableRow.Train_Accuracy} </p>
                <p> {mlTableRow.Validation_Accuracy} </p>
                <p> {mlTableRow.Test_Accuracy} </p>
                <div className="row">
                    <div className="col-md-1">
                        <button type="button" className="btn btn-info" onClick={() => setShowFormWithData(mlTableRow)}>Update</button>
                    </div>
                    <div className="col">
                        <button type="button" className="btn btn-danger" onClick={() => deleteMlTableRow(mlTableRow)}>Delete</button>
                    </div>
                </div>
                <hr className="hr-style5"/>
            </div> )
            })}
            <br/>

        </div>
    )
}
