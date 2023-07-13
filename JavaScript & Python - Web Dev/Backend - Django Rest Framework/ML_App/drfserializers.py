from rest_framework import serializers
from .models import ML_Table

class ML_Table_Serializer(serializers.ModelSerializer):
    class Meta:
        model = ML_Table
        fields = ['id', 'Dataset_Title', 'Train_Dataset_Upload', 'Test_Dataset_Upload',
                         'Train_Accuracy', 'Validation_Accuracy', 'Test_Accuracy']
