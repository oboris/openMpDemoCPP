#include<iostream>
#include"omp.h"

using namespace std;

const int arr_size = 200000000;

int arr[arr_size];

void init_arr();
long long part_sum(int, int, int);

int main() {
	
	init_arr();

	cout << part_sum(0, arr_size, 1) << endl;
	cout << part_sum(0, arr_size, 2) << endl;
	cout << part_sum(0, arr_size, 3) << endl;
	cout << part_sum(0, arr_size, 4) << endl;
	cout << part_sum(0, arr_size, 8) << endl;
	cout << part_sum(0, arr_size, 10) << endl;
	cout << part_sum(0, arr_size, 16) << endl;
	cout << part_sum(0, arr_size, 32) << endl;

	return 0;
}

void init_arr() {
	for (int i = 0; i < arr_size; i++) {
		arr[i] = i + 1;
	}
}

long long part_sum(int start_index, int finish_index, int num_threads) {
	long long sum = 0;
	
	double t1 = omp_get_wtime();
#pragma omp parallel num_threads(num_threads)
	{
#pragma omp for reduction(+:sum)
		for (int i = start_index; i < finish_index; i++) {
			sum += arr[i];
		}
	}

	double t2 = omp_get_wtime();

	cout << num_threads << " threads worked - " << t2 - t1 << " seconds" << endl;

	return sum;
}