#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void input();
void output();
void constant();
void change(int result, char target[]);

struct expr {
	char op[2], op1[5], op2[5], target[5];
	int flag;
} arr[10];
int n;

int main() {
	input();
	constant();
	output();
}

void input() {
	printf("Enter number of expressions: \n");
	scanf("%d", &n);
	printf("Enter the input: \n");
	for (int i = 0; i < n; i++) {
		scanf("%s %s %s %s", arr[i].op, arr[i].op1, arr[i].op2, arr[i].target);
		arr[i].flag = 0;
	}
}

void output() {
	printf("Optimized code is:\n");
	for (int i = 0; i < n; i++) {
		if (!arr[i].flag)
			printf("%s %s %s %s\n", arr[i].op, arr[i].op1, arr[i].op2, arr[i].target);
	}
}

void constant() {
	for (int i = 0; i < n; i++) {
		if (strcmp(arr[i].op, "=") == 0 || (isdigit(arr[i].op1[0]) && isdigit(arr[i].op2[0]))) {
			int a = atoi(arr[i].op1);
			int b = atoi(arr[i].op2);
			int res;
			switch (arr[i].op[0]) {
			case '+':
				res = a + b;
				break;
			case '-':
				res = a - b;
				break;
			case '*':
				res = a * b;
				break;
			case '/':
				res = a / b;
				break;
			case '=':
				res = a;
				break;
			}
			change(res, arr[i].target);
			arr[i].flag = 1;
		}
	}
}

void change(int result, char target[]) {
	for (int i = 0; i < n; i++) {
		if (strcmp(arr[i].op1, target) == 0)
			sprintf(arr[i].op1, "%d", result);
		if (strcmp(arr[i].op2, target) == 0)
			sprintf(arr[i].op2, "%d", result);
	}
}
