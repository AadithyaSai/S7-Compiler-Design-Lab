#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

char* E(char* expr);
char* Estar(char* expr);
char* T(char* expr);
char* Tstar(char* expr);
char* F(char* expr);

int main() {
    char str[256];
	printf("Enter string: ");
	scanf("%s", str);
	
	char* result = E(str);
	if (*(result) == '\0')
		printf("Accepted\n");
  	else
  		printf("Syntax error\n");
}

char* E(char* expr) {
	expr = T(expr);
	expr = Estar(expr);
  	
  	return expr;
}

char* Estar(char* expr) {
    if (*expr == '+' ) {
        expr++;
    	expr = T(expr);
	    expr = Estar(expr);
    }
    
    return expr;
}

char* T(char* expr) {
    expr = F(expr);
	expr = Tstar(expr);
	
	return expr;
}

char* Tstar(char* expr) {
    if (*expr == '*' ) {
        expr++;
    	expr = F(expr);
	    expr = Tstar(expr);
    }
    
    return expr;
}

char* F(char* expr) {
    if (*expr == '(') {
        expr++;
        expr = E(expr);
        if (*expr == ')') {
            expr++;
            return expr;
        }
        else {
            printf("Syntax error\n");
            exit(1);
        }
    }
    else if (*expr >= 'a' && *expr <= 'z')
        expr++;
    else {
        printf("Syntax error\n");
        exit(1);
    }
    return expr;
}
