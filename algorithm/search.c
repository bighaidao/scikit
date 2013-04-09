#include <stdio.h>
#include <stdlib.h>

//
int binary_search(int *k_a, int l, int h, int target) {
	int mid;
	while (l < h) {
		mid = l + ((h - l) >> 1);
		if (k_a[mid] < target) {
			l = mid + 1;
		} else if (k_a[mid] < target) {
			h = mid - 1;
		} else {
			return mid;
		}

	}
	return -1;
//		binary_search(k_a, l, h, target);

}
