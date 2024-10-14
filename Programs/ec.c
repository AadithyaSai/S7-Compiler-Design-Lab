#include <stdio.h>

// Find epsilon closure using dfs

int et[100][100];
int visited[100];

void dfs(int v, int n);
void reset_visited(int size);

int main() {
	int ns, nt;
	printf("Enter number of states: ");
	scanf("%d", &ns);
	printf("Enter number of transitions: ");
	scanf("%d", &nt);
	printf("Enter transitions\n");
	int m, n;
	char sym;
	for (int i = 1; i <= nt; i++) {
		scanf("%d %c %d", &m, &sym, &n);
		if (sym == 'e') {
			et[m][n] = 1;
		}
	}
	for (int i = 1; i <= ns; i++) {
		printf("Epsilon Closure of state %d: { ", i);
		reset_visited(ns);
		dfs(i, ns);
		for (int j = 1; j <= ns; j++) {
			if (visited[j]) {
				printf("%d ", j);
			}
		}
		printf("}\n");
	}
}

void dfs(int v, int n) {
	visited[v] = 1;
	for (int i = 1; i <= n; i++) {
		if (!visited[i] && et[v][i]) {
			dfs(i, n);	
		}
	}
}

void reset_visited(int size) {
	for (int i = 1; i <= size; i++) {
		visited[i] = 0;
	}
}

