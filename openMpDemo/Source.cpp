#include<iostream>
#include"omp.h"

using namespace std;

const int arr_size = 200000000;

int arr[arr_size];

void init_arr();
long long part_sum(int, int, int);
long long part_min(int, int, int);

int main() {
	
	init_arr();

	omp_set_nested(1);
	double t1 = omp_get_wtime();
#pragma omp parallel sections
	{
#pragma omp section
		{
			cout << "min 1 = " << part_min(0, arr_size, 1) << endl;
			cout << "min 2 = " << part_min(0, arr_size, 2) << endl;
			cout << "min 3 = " << part_min(0, arr_size, 3) << endl;
			cout << "min 4 = " << part_min(0, arr_size, 4) << endl;
			cout << "min 8 = " << part_min(0, arr_size, 8) << endl;
			cout << "min 10 = " << part_min(0, arr_size, 10) << endl;
			cout << "min 16 = " << part_min(0, arr_size, 16) << endl;
			cout << "min 32 = " << part_min(0, arr_size, 32) << endl;
		}
		
#pragma omp section
		{
			cout << "sum 1 = " << part_sum(0, arr_size, 1) << endl;
			cout << "sum 2 = " << part_sum(0, arr_size, 2) << endl;
			cout << "sum 3 = " << part_sum(0, arr_size, 3) << endl;
			cout << "sum 4 = " << part_sum(0, arr_size, 4) << endl;
			cout << "sum 8 = " << part_sum(0, arr_size, 8) << endl;
			cout << "sum 10 = " << part_sum(0, arr_size, 10) << endl;
			cout << "sum 16 = " << part_sum(0, arr_size, 16) << endl;
			cout << "sum 32 = " << part_sum(0, arr_size, 32) << endl;
		}
	}
	double t2 = omp_get_wtime();
	
	cout << "Total time - " << t2 - t1 << " seconds" << endl;
	return 0;
}

void init_arr() {
	for (int i = 0; i < arr_size; i++) {
		arr[i] = arr_size - i;
	}

	arr[arr_size / 2] = -100;
}

long long part_sum(int start_index, int finish_index, int num_threads) {
	long long sum = 0;
	double t1 = omp_get_wtime();
#pragma omp parallel for reduction(+:sum) num_threads(num_threads)	
		for (int i = start_index; i < finish_index; i++) {			
			sum += arr[i];
		}
	

	double t2 = omp_get_wtime();

	cout << "sum " << num_threads << " threads worked - " << t2 - t1 << " seconds" <<  endl;

	return sum;
}

long long part_min(int start_index, int finish_index, int num_threads) {
	int min = arr[0];
	double t1 = omp_get_wtime();
#pragma omp parallel for num_threads(num_threads)

	for (int i = start_index; i < finish_index; i++) {

		if (min > arr[i])
		{
#pragma omp critical
			if (min > arr[i])
			{
				min = arr[i];
			}
		}
	}

	double t2 = omp_get_wtime();

	cout << "min " << num_threads << " threads worked - " << t2 - t1 << " seconds" << endl;

	return min;
}