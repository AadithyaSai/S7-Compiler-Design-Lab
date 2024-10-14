%{ 
#include <stdio.h> 
#include <ctype.h>
int isVowel(char c) {
	char lc = tolower(c);
	return lc == 'a' || lc == 'e' || lc == 'i' || lc == 'o' || lc == 'u';
}

int vc = 0;
int cc = 0;
%} 

/* Rules Section*/
%% 
[a-zA-Z]	{
				if (isVowel(yytext[0])) vc++; 
				else cc++;
			}
[ \t\n]          /* do nothing */
.                /* do nothing */

%% 

int yywrap(void){} 

int main() 
{
	FILE* inp = fopen("input.txt", "r");

  	yyin = inp;
    yylex(); 
    fclose(inp);
    
    printf("Vowels: %d\n", vc);
    printf("Consonants: %d\n", cc);
    
    return 0; 
} 

