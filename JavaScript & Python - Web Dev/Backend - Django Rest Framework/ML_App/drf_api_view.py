from rest_framework import status
from rest_framework.decorators import api_view
from rest_framework.response import Response
from .models import ML_Table
from .drfserializers import ML_Table_Serializer


@api_view(['GET', 'POST'])
def ML_Table_list_drf_api_view(request):

    if request.method == 'GET':
        serializer = ML_Table_Serializer(ML_Table.objects.all(), many=True)
        return Response(serializer.data)

    elif request.method == 'POST':
        serializer = ML_Table_Serializer(data=request.data)
        if serializer.is_valid():
            serializer.save()
            return Response(serializer.data, status=status.HTTP_201_CREATED)
        return Response(serializer.errors, status=status.HTTP_400_BAD_REQUEST)

@api_view(['GET', 'PUT', 'DELETE'])
def ML_Table_detail_drf_api_view(request, pk):
    try:
        ML_Table_Row = ML_Table.objects.get(id=pk)  # Since in drfserializers.py I used id and not pk, here I put .get(id=pk).
    except ML_Table.DoesNotExist:
        return Response(status=status.HTTP_404_NOT_FOUND)

    if request.method == 'GET':
        serializer = ML_Table_Serializer(ML_Table_Row)
        return Response(serializer.data)

    elif request.method == 'PUT':
        serializer = ML_Table_Serializer(ML_Table_Row, data=request.data)
        if serializer.is_valid():
            serializer.save()
            return Response(serializer.data)
        return Response(serializer.errors, status=status.HTTP_400_BAD_REQUEST)

    elif request.method == 'DELETE':
        ML_Table_Row.delete()
        return Response(status=status.HTTP_204_NO_CONTENT)


