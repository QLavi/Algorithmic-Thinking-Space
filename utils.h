#pragma once

#include <stdio.h>
#include <limits.h>
#include <stddef.h>
#include <stdbool.h>

int array_min_index(int arr[], int len) {
	int min = INT_MAX;
	int min_idx = -1;

	for (int i=0; i<len; i++) {
		if (arr[i] < min) {
			min = arr[i];
			min_idx = i;
		}
	}

	return min_idx;
}

void print_array(int arr[], int len) {

	printf("[");
	for (int i=0; i<len; i++) {
		printf("%d", arr[i]);
		if (i < len -1) {
			printf(", ");
		}
	}
	printf("]\n");
}

void print_2darray(int *arr, int r, int c) {
	printf("[");
	for(int i=0; i<r; i++) {
		for (int j=0; j<c; j++) {
			if (i > 0 && j == 0) {
				printf(" ");
			}
			printf("%d", arr[j + i * c]);

			if (j < c - 1) {
				printf(", ");
			}
		}

		if (i < r - 1) {
			printf("\n");
		}
	}
	printf("]\n");
}

bool array_isequal(int a[], int b[], int len) {
	for (int i=0; i<len; i++) {
		if (a[i] != b[i]) {
			return false;
		}
	}

	return true;
}

int mod(int a, int b) {
	if (a >= 0) return a % b;
	return (a % b + b) % b;
}

bool array_isequalwrap(
	int a[],
	int b[],
	int len,
	int start,
	bool from_right) {

	for (int i=0; i<len; i++) {
		int idx = from_right ? i + start : start - i;
		if (a[mod(idx, len)] != b[i]) {
			return false;
		}
	}
	return true;
}