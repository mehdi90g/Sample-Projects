export default class APIService {

    static fullUpdateMlTableRow(mlTableRow_id, dataTitle, trainData, testData, trainAcc, validAcc, testAcc) {
		const data = new FormData();
        data.append('Dataset_Title', dataTitle);
		data.append('Train_Dataset_Upload', trainData);
        data.append('Test_Dataset_Upload', testData);
		data.append('Train_Accuracy', trainAcc);
		data.append('Validation_Accuracy', validAcc);
		data.append('Test_Accuracy', testAcc);
		return fetch(`http://127.0.0.1:8000/mlapp/drfApiView/${mlTableRow_id}`, {
			method: 'PUT',
			body: data
		    })
            .then(response => response.json())
            // .then(result => {
            // console.log('Success:', result);
            // })
            // .catch(error => {
            // console.error('Error:', error);
            // });
	}

    static fullCreateMlTableRow(dataTitle, trainData, testData, trainAcc, validAcc, testAcc) {
		const data = new FormData();
        data.append('Dataset_Title', dataTitle);
		data.append('Train_Dataset_Upload', trainData);
        data.append('Test_Dataset_Upload', testData);
		data.append('Train_Accuracy', trainAcc);
		data.append('Validation_Accuracy', validAcc);
		data.append('Test_Accuracy', testAcc);
		return fetch('http://127.0.0.1:8000/mlapp/drfApiView/', {
			method: 'POST',
			body: data
		    })
            .then(response => response.json())
            // .then(result => {
            // console.log('Success:', result);
            // })
            // .catch(error => {
            // console.error('Error:', error);
            // });
	}

    static deleteMlTableRow(mlTableRow_id) {
        return fetch(`http://127.0.0.1:8000/mlapp/drfApiView/${mlTableRow_id}`, {
          'method':'DELETE',
          headers: {
              'Content-Type':'application/json'
            } 
       }) 
    }


}