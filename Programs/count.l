%{ 
#include<stdio.h> 
#include<string.h> 

int lines = 0;
int words = 0;
int chars = 0; 
%} 
  
/* Rules Section*/
%% 
[\n]      { lines++; chars+=yyleng; }
[^\t\n ]+ { words++; chars+=yyleng; }
[ ]       {}

%% 

int yywrap(void){} 

int main() 
{
	FILE* inp = fopen("input.txt", "r");

  	yyin = inp;
    yylex(); 
    fclose(inp);
    
    printf("Number of lines: %d\n", lines);
    printf("Number of words: %d\n", words);
    printf("Number of characters: %d\n", chars);
    return 0; 
} 

