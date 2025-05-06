#include<iostream>
#include<omp.h>
#include<limits.h>
using namespace std;

void min_reduction(int arr[], int size){
	int min_value = arr[0];
	
	#pragma omp parallel for reduction(min:min_value)
	
	for(int i=0 ; i<size ; i++){
	   if(arr[i]< min_value){
		
		min_value = arr[i];

		}

	
	}
	cout<<"MIN VALUE IS:"<<min_value<<endl;
	



}
void max_reduction(int arr[],int size){
	int max_value = INT_MIN;
	
	#pragma omp parallel for reduction(max:max_value)
	
	for(int i=0 ; i<size ; i++){
	   if(arr[i]> max_value){
		
		max_value = arr[i];

		}

	
	}
	cout<<"MAX VALUE IS:"<<max_value<<endl;
	



}

void sum_reduction(int arr[], int size){
	int sum= 0;
	
	#pragma omp parallel for reduction(+:sum)
	
	for(int i=0 ; i<size ; i++){
	   sum  += arr[i];
	
	}
	cout<<"Sum VALUE IS:"<<sum<<endl;
	



}

void avg(int arr[],int size){
	int avg =0;
	
	#pragma omp parallel for reduction(+:avg)
	
	for(int i=0 ; i<size ; i++){
	
		avg += arr[i];

		
	
	}
	cout<<"AVG VALUE IS:"<<avg/4<<endl;
	



}


int main(){
	int size = 5;
	int arr[size]={4,5,43,3,67};
	
	min_reduction(arr,size);
	max_reduction(arr,size);
	sum_reduction(arr,size);
	avg(arr,size);

return 0 ;

}
