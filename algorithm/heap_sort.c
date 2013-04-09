#include <stdio.h>

#define lson (idx<<1)
#define rson (lson+1)

int i;

void swap(int *x, int *y) {
	int temp = 0;
	temp = *x;
	*x = *y;
	*y = temp;
}
/**
 * 就是一个数组
 * 构建  i 2i 2i+1 比较 ，选出最大 (i<size/2)
 * 不停的调整顺序
 *
 */
inline void max_heap_mdf(int *k_a, int idx, int size) {

	int max_id = idx;
	if (lson < size && k_a[lson] > k_a[idx]) {
		max_id = lson;
	}
	if (rson < size && k_a[rson] > k_a[idx]) {

		if(k_a[lson]>k_a[rson])
		max_id = lson;
		else  max_id = rson;
	}
//递归构建 大堆
	if (max_id != idx) {
		swap(&k_a[idx], &k_a[max_id]);
		max_heap_mdf(k_a, max_id, size);
	}

}

void build_max_heap(int *k_a, int size) {
	for (i = size >> 1; i >= 1; --i) {
//		printf("%d \n",i);
		max_heap_mdf(k_a, i, size);
	}
}

void heap_sort(int *k_a, int size) {

	build_max_heap(k_a, size);
	for (i = size; i >= 1; --i) {

		swap(&k_a[1], &k_a[i]); //k_a[1] keep the max value  change and sort
		max_heap_mdf(k_a, 1, i - 1);

//		print(k_a, size);
	}

}

//int main() {
//    puts("初始状态:");
//    int k_a[15] = {0, 4, 1, 3, 2, 16, 9, 10, 14, 8, 7};
//    int size = 10;
//    print(k_a,size);
//
//    heap_sort(k_a,size);
//
//    puts("堆排序后:");
//    print(k_a,size);
//}
