#include <stdio.h>
#include <stdlib.h>
int min(int a, int b, int c) {
	if (a < b) {
		if (a < c) {
			return a;
		} else
			return c;
	} else {
		if (b < c) {
			return b;
		} else
			return c;
	}
}
/**
 *
 *算法过程
http://www.cnblogs.com/ivanyb/archive/2011/11/25/2263356.html
 str1或str2的长度为0返回另一个字符串的长度。 if(str1.length==0) return str2.length; if(str2.length==0) return str1.length;
 初始化(n+1)*(m+1)的矩阵d，并让第一行和列的值从0开始增长。
 扫描两字符串（n*m级的），如果：str1[i] == str2[j]，用temp记录它，为0。否则temp记为1。然后在矩阵d[i,j]赋于d[i-1,j]+1 、d[i,j-1]+1、d[i-1,j-1]+temp三者的最小值。
 扫描完后，返回矩阵的最后一个值d[n][m]即是它们的距离。
 计算相似度公式：1-它们的距离/两个字符串长度的最大值。
 *
 */
int edit_distance(const char* str1, const char *str2) {
	int n = strlen(str1)+1, m = strlen(str2)+1;
	int **a = malloc(sizeof(int) * (n ));
	int j = 0, i = 0, temp1, temp2;
	for (; j < m; j++)
		a[j] = malloc(sizeof(int) * (m ));

	for (j = 0; j < n; j++)
		a[j][0] = j;
	for (j = 0; j < m; j++)
		a[0][j] = j;

	for (i = 1; i < n; i++)
		for (j = 1; j < m; j++) {
			if (str1[i-1] == str2[j-1]) {
				a[i][j] = min(a[i - 1][j] + 1, a[i][j - 1] + 1,
						a[i - 1][j - 1]);
			} else {
				a[i][j] = min(a[i - 1][j] + 1, a[i][j - 1] + 1,
						a[i - 1][j - 1] + 1);
			}
		}
	return a[i-1][j-1];
}

int main(int argc, char **argv) {
	int dis=edit_distance("ivan1","ivan22");
	printf("%d \n",dis);
	return 0;
}


