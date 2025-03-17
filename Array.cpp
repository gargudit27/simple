#include "Array.h"

Array::Array() {
	
}
Array::Array(int size)
{
	this->size = size;
	arr = new int[size];
}

void Array::Accept() {
	cout<<"Enter the values of the array: "<<endl;
	for(int i = 0;i<size;i++) {
		cin>>arr[i];
	}
}

void Array::Display() {
	cout<<"The value of the array are: "<<endl;
	for(int i = 0;i<size;i++) {
		cout<<arr[i]<<" "<<endl;
	}
}

void Array::Sort() {
	for(int i = 0;i<size;i++) {
		for(int j = i+1;j<size;j++) {
			if(arr[j]>arr[i]) {
			int temp = arr[j];
			arr[j] = arr[i];
			arr[i] = temp;
		}
	}
	}
}

int Array::findMax() {
	Array::Sort();
	int max = arr[0];
	return max;
}

int Array::findMin() {
	Array::Sort();
	int min = arr[size - 1];
	return min;
}

Array::~Array() {
	cout<<"Destructor is called"<<endl;
}
