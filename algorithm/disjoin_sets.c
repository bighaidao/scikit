/*
 *并查集
 */

#include <stdio.h>
#include <stdlib.h>
#define Max 1000
int parent[Max];
int rank[Max];

void make_set(int x) {
	parent[x] = x;
	rank[x] = 0;
}
int find(int x) {
	if (x != parent[x])
		parent[x] = find(x);  //精髓
	return parent[x];
}

void union_set(int x, int y) {
	x = find(x);
	y = find(y);
	if (x != y)
		if (rank[x] > rank[y])
			parent[y] = x;
		else if (rank[x] < rank[y])
			parent[x] = y;
		else {
			rank[y]++;
			parent[x] = y;
		}
}
//int main() {
//	int n, m;
//  int i;  int i;
//    return 0;
//}
