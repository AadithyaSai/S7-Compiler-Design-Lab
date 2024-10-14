%{ 
#include <stdio.h> 
#include <ctype.h>
%} 

/* Rules Section*/
%% 
[a-z]	printf("%c", toupper(yytext[0]));

%% 

int yywrap(void){} 

int main() 
{
	FILE* inp = fopen("input.txt", "r");

  	yyin = inp;
    yylex(); 
    fclose(inp);
    
    return 0; 
} 

