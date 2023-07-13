import './App.css';
import { Header } from './components/Header'
import { Navbar } from './components/Navbar'
import { Form } from './components/Form'
import {useState} from 'react'
import {useEffect} from 'react'



function App() {

  const [mlTable, setMlTable] = useState(['row1', 'row2'])
  const [showFormWithData, setShowFormWithData] = useState(null)

  useEffect( () => {  fetch('http://127.0.0.1:8000/mlapp/drfApiView', { 'method':'GET' , headers: {'Content-Type': 'application/json'}  } ).then(resp => resp.json()).then(resp => setMlTable(resp)).catch(error => console.log(error))  } , [] )

  const reloadUpdatedMlTableRow = (updatedMlTableRow) => {
    const newMlTable = mlTable.map(formerMlTableRow => {
      if(formerMlTableRow.id === updatedMlTableRow.id) {
        return updatedMlTableRow;
      }
      else {
        return formerMlTableRow;
      }
    })

    setMlTable(newMlTable)
  }


  const loadCreatedMlTableRow = (createdMlTableRow) => {
    const newMlTable = [...mlTable, createdMlTableRow]
    setMlTable(newMlTable)
  }


  const reloadDeletedMlTableRow = (deletedMlTableRow) => {
    const newMlTable = mlTable.filter(formerMlTableRow => {
      if(formerMlTableRow.id === deletedMlTableRow.id) {
        return false
      }
      return true;
    })

    setMlTable(newMlTable)
  }


  return (
    <div>
      <Navbar />
      <Header mlTable = {mlTable} setShowFormWithData = {setShowFormWithData} reloadDeletedMlTableRow = {reloadDeletedMlTableRow}/>
      {showFormWithData ? <Form showFormWithData = {showFormWithData} reloadUpdatedMlTableRow = {reloadUpdatedMlTableRow}
                                loadCreatedMlTableRow = {loadCreatedMlTableRow} /> : null}
    </div>
  );
}

export default App;