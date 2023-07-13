import React from 'react'
import {useState} from 'react'
import {useEffect} from 'react'
import APIService from '../APIService'


export const Form = (props) => {

    const [Dataset_Title, setDataset_Title] = useState('')
    const [Train_Dataset_Upload, setTrain_Dataset_Upload] = useState('')
    const [Test_Dataset_Upload, setTest_Dataset_Upload] = useState('')
    const [Train_Accuracy, setTrain_Accuracy] = useState('')
    const [Validation_Accuracy, setValidation_Accuracy] = useState('')
    const [Test_Accuracy, setTest_Accuracy] = useState('')


    // Instead of the following useEffect, we could just put props.showFormWithData.Dataset_Title as the initial value:
    // const [Dataset_Title, setDataset_Title] = useState(props.showFormWithData.Dataset_Title ? props.showFormWithData.Dataset_Title : '')
    // I used x ? x : '' since otherwise, when the corresponding value in that specific row of table is null, then
    // it gives error when trying to update the form.
    useEffect(() => {
        setDataset_Title(props.showFormWithData.Dataset_Title ? props.showFormWithData.Dataset_Title : '')
        setTrain_Accuracy(props.showFormWithData.Train_Accuracy ? props.showFormWithData.Train_Accuracy : '')
        setValidation_Accuracy(props.showFormWithData.Validation_Accuracy ? props.showFormWithData.Validation_Accuracy : '')
        setTest_Accuracy(props.showFormWithData.Test_Accuracy ? props.showFormWithData.Test_Accuracy : '')
    }, [props.showFormWithData])


    // 'Update' functionality for a whole row of the database table
    const fullUpdateMlTableRow = () => {
        APIService.fullUpdateMlTableRow(props.showFormWithData.id, Dataset_Title, Train_Dataset_Upload,
            Test_Dataset_Upload, Train_Accuracy, Validation_Accuracy, Test_Accuracy)
        .then(resp => props.reloadUpdatedMlTableRow(resp))
    }

    // 'Create' functionality for a whole new row of the database table
    const fullCreateMlTableRow = () => {
        APIService.fullCreateMlTableRow(
            Dataset_Title, Train_Dataset_Upload, Test_Dataset_Upload,
            Train_Accuracy, Validation_Accuracy, Test_Accuracy)
        .then(resp => props.loadCreatedMlTableRow(resp))
    }


    return (
        <div className="container">
            {props.showFormWithData ? ( 

                <div>
                    <div class="mb-3" >
                        <label for="datasetTitle" class="form-label">Dataset Title</label>
                        <div class="col-sm-3">
                            <input type="text" class="form-control" placeholder="Enter the dataset title." id="datasetTitle" 
                               value={Dataset_Title} onChange={event => setDataset_Title(event.target.value)}/>
                        </div>
                    </div>
                    <div class="mb-3">
                        <label for="trainDataset" class="form-label">Train Dataset</label>
                        <div class="col-sm-3">
                            <input class="form-control" type="file" id="trainDataset" aria-describedby="trainHelp"
                                onChange={ (event) => { setTrain_Dataset_Upload(event.target.files[0]); } }/>
                        </div>
                        <div id="trainHelp" class="form-text">Upload the train dataset in the Excel format (.xlsx file).</div>
                    </div>
                    <div class="mb-3">
                        <label for="testDataset" class="form-label">Test Dataset</label>
                        <div class="col-sm-3">
                            <input class="form-control" type="file" id="testDataset" aria-describedby="testHelp"
                               onChange={(event) => setTest_Dataset_Upload(event.target.files[0])}/>
                        </div>
                        <div id="testHelp" class="form-text">Upload the test dataset in the Excel format (.xlsx file).</div>
                    </div>
                    <div class="mb-3" >
                        <label for="trainAccuracy" class="form-label">Train Accuracy</label>
                        <div class="col-sm-3">
                            <input type="number" class="form-control" min="0" max="100" step="0.01" placeholder="Enter the train accuracy." id="trainAccuracy" aria-describedby="accuracyHelp"
                                value={Train_Accuracy} onChange={event => setTrain_Accuracy(event.target.value)}/>
                        </div>
                        <div id="accuracyHelp" class="form-text">Accuracy must be a number between 0 and 100.</div>
                    </div>
                    <div class="mb-3" >
                        <label for="validationAccuracy" class="form-label">Validation Accuracy</label>
                        <div class="col-sm-3">
                            <input type="number" class="form-control" min="0" max="100" step="0.01" placeholder="Enter the validation accuracy." id="validationAccuracy" aria-describedby="accuracyHelp"
                               value={Validation_Accuracy} onChange={event => setValidation_Accuracy(event.target.value)}/>
                        </div>
                        <div id="accuracyHelp" class="form-text">Accuracy must be a number between 0 and 100.</div>
                    </div>
                    <div class="mb-3" >
                        <label for="testAccuracy" class="form-label">Test Accuracy</label>
                        <div class="col-sm-3">
                            <input type="number" class="form-control" min="0" max="100" step="0.01" placeholder="Enter the test accuracy." id="testAccuracy" aria-describedby="accuracyHelp"
                                value={Test_Accuracy} onChange={event => setTest_Accuracy(event.target.value)}/>
                        </div>
                        <div id="accuracyHelp" class="form-text">Accuracy must be a number between 0 and 100.</div>
                    </div>
                    {
                        props.showFormWithData.id ?
                        <button onClick = {fullUpdateMlTableRow} class="btn btn-outline-success">Update Row of Table</button>
                        :
                        <button onClick = {fullCreateMlTableRow} class="btn btn-outline-success">Create a new Row in Table</button>
                        }
                    <hr className="hr-custom"/>
                    <br/>
                </div>

             ) : null}
        </div>
    )
}
