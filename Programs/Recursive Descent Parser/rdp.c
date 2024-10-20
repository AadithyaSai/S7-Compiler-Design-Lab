#include <stdio.h>
#include <stdlib.h>

char* E(char *c);
char* Estar(char *c);
char* T(char *c);
char* Tstar(char *c);
char* F(char *c);

int main() {
	char str[256];
	
	printf("Enter string: ");
	scanf("%s", str);
	
	E(str);
	
	return 0;
}

char* E(char *c) {
	c = T(c);
	c = Estar(c);
	if (*(c) == '\0')
		printf("Accepted\n");
  	else {  	
  		printf("Syntax error\n");
  		exit(0);
  	}
  	
  	return c;
}

char* Estar(char *c) {
  	if (*(c) == '+' || *(c) == '-') {
  	    c++;
  	    c = T(c);
  	    c = Estar(c);
  	}
  	
  	return c;
}

char* T(char *c) {
	c = F(c);
	c = Tstar(c);
	
	return c;
}

char* Tstar(char *c) {
  	if (*(c) == '*' || *(c) == '/') {
  	    c++;
  	    c = F(c); 
  	    c = Tstar(c);
  	}
  	
  	return c;
}

char* F(char *c) {
  	if (*(c) == '(') {
  		c++;
  	    c = E(c);
  	    if (*(c) == ')')
  			c++;
  	    else {
  	    	printf("Syntax error\n");
  	    	exit(0);
  	    }
  	} else if ('0' <= *(c) && '9' >= *(c)) {	
  		c++;
}
  	else {  	
  		printf("Syntax error\n");
  		exit(0);
  	}
  	
  	return c;
}

