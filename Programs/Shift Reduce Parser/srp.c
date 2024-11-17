#include <stdio.h>
#include <string.h>

int z = 0, i = 0, j = 0, c = 0;
char a[16], ac[20], stack[15], act[10];

void check();

int main() {
    printf("GRAMMAR is\n E->E+E \n E->E*E \n E->(E) \n E->id\n");
    printf("Enter input string:\n");
    scanf("%s", a);
    c = strlen(a);
    strcpy(act, "SHIFT");
    printf("stack \t input \t action");
    for (i = 0; j < c; i++, j++) {
    	printf("\n$%s\t%s$\t%s", stack, a, act);
        stack[i] = a[j];
        stack[i + 1] = '\0';
        a[j] = ' ';
        check();
    }
    
    printf("\n$%s\t%s$\tDONE\n", stack, a);
	if (strcmp(stack, "E") == 0)
		printf("String Accepted\n");
	else
		printf("String Rejected\n");
}

void check() {
    strcpy(ac, "REDUCE by E");
    for (z = 0; z < c; z++)
        if (stack[z] >= 'a' && stack[z] <= 'z') {
        	printf("\n$%s\t%s$\t%s->id", stack, a, ac);
            stack[z] = 'E';
            check();
        }
    for (z = 0; z < c; z++)
        if (stack[z] == 'E' && stack[z + 1] == '+' && stack[z + 2] == 'E') {
        	printf("\n$%s\t%s$\t%s->E+E", stack, a, ac);
            stack[z] = 'E';
            stack[z + 1] = '\0';
            stack[z + 2] = '\0';
            i = i - 2;
            check();
        }
    for (z = 0; z < c; z++)
        if (stack[z] == 'E' && stack[z + 1] == '*' && stack[z + 2] == 'E') {
        	printf("\n$%s\t%s$\t%s->E*E", stack, a, ac);
            stack[z] = 'E';
            stack[z + 1] = '\0';
            stack[z + 2] = '\0';
            i = i - 2;
            check();
        }
    for (z = 0; z < c; z++)
        if (stack[z] == '(' && stack[z + 1] == 'E' && stack[z + 2] == ')') {
        	printf("\n$%s\t%s$\t%s->(E)", stack, a, ac);
            stack[z] = 'E';
            stack[z + 1] = '\0';
            stack[z + 2] = '\0';
            i = i - 2;
            check();
        }
}
