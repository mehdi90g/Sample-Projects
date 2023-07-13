from django.db import models

# Create your models here.

class ML_Table(models.Model):
    Dataset_Title = models.CharField(max_length=30, null=True)
    # file will be uploaded to MEDIA_ROOT/ upload_to path
    Train_Dataset_Upload = models.FileField(upload_to='Train_Dataset_Uploads/', null=True)
    # or:
    # file will be saved to MEDIA_ROOT/Train_Uploads/2022/11/01
    #Train_Dataset_Upload = models.FileField(upload_to='Train_Dataset_Uploads/%Y/%m/%d/')
    Test_Dataset_Upload = models.FileField(upload_to='Test_Dataset_Uploads/', null=True)
    Train_Accuracy = models.DecimalField(max_digits=5, decimal_places=2, null=True)
    Validation_Accuracy = models.DecimalField(max_digits=5, decimal_places=2, null=True)
    Test_Accuracy = models.DecimalField(max_digits=5, decimal_places=2, null=True)
