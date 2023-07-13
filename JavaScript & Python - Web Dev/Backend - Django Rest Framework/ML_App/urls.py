from django.urls import path

from . import views

from . import drf_api_view


urlpatterns = [
    path('drfApiView/', drf_api_view.ML_Table_list_drf_api_view, name='ML_Table_list_drf_api_view'),
    path('drfApiView/<int:pk>', drf_api_view.ML_Table_detail_drf_api_view, name='ML_Table_detail_drf_api_view'),
]

