#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int sample_str(const char *source, const char *target, int pos) {

	int i = 0, j = 0;//assert source and target
	while (i < strlen(source) && j < strlen(target)) {
		if (source[i + j] == target[j]) {
			j++;
		} else {
			i++;
			j = 0;
		}
	}
	if (j == strlen(target)) {
		return i + j;
	}
//	printf("%d %d \n",source[i], target[j]);
	return 0;

}

int * kmp_next(const char *target) {
	if (target == NULL ) {
		return NULL ;
	}
	int i = 0, j = -1, len = strlen(target);

	int * next = malloc(len * sizeof(int));
	next[i] = j;
	for (; i < len;) {
		while (j >= 0 && target[i] != target[j])
			j = next[j];
		i++;
		j++;
		next[i] = j; //比较的是当前字符，算出的是下一个字符不等时的情况
	}
	return next;
}

int kmp_search(int *next, const char *source, const char *target) {
	int i = 0, j = 0, n = strlen(source), t = strlen(target);

	while (i < n) {
		while (j > 0 && source[i] != target[j]) {
			j = next[j];

		}
		i++;
		j++;
		if (j == t) {
			printf("%d \n", j);
			return 1;
		}

	}
	return -1;
}
//int main(int argc, char **argv) {
//
//	const char *s = "helloworld";
//	const char *target = "hello";
//	const char *target1 = "his";
//	int * next = kmp_next(target);
//	int k = 0;
//	while (k < strlen(target)) {
//		printf("%d \t", next[k]);
//		k++;
//	}
//
//	printf("%d \n", kmp_search(next, s, target));
////	printf("%d \n", sample_str(s, target1, 0));
//}

