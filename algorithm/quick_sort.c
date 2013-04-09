#include <stdio.h>
#include "head.h"
void quick_sort(int *k_a, int low, int high) {
	int i = low;
	int j = high;
	int key = k_a[low];
	while (i < j) {
		while (i < j && key < k_a[j])
			j--;
		if (i < j)
			k_a[i++] = k_a[j]; //j 空了
		while (i < j && key > k_a[i])
			i++;
		if (i < j)
			k_a[j--] = k_a[i];  //i 把j填上
	}
	k_a[i] = key;
	if (low < i - 1)
		quick_sort(k_a, low, i - 1);
	if (i + 1 < high)
		quick_sort(k_a, i + 1, high);
}
int main() {
    puts("初始状态:");
    int k_a[15] = {4, 1, 3, 2, 16, 9, 10, 14, 8, 7};
    int size = 10;
    print(k_a,size);
    quick_sort(k_a,1,10);

    puts("堆排序后:");
    print(k_a,size);
}
