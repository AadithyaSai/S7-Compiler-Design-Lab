#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define KEYWORD_COUNT 6

char* id[256] = {"printf", "scanf"};
int id_size = 2;

int getNextToken(FILE* file, char tok[]);
int isKeyword(char* str); 
int isOperator(char c);
int isSpecial(char c);
int isDelim(char c);
void skipLine(FILE* file);
void addId(char* tok);
int isId(char* tok);

int main() {
	FILE* input = fopen("source.c", "r");
	
	char token[64];
	char c;
	while (getNextToken(input, token)) {
		if (strcmp(token, "//") == 0 || strcmp(token, "#") == 0) {
			c = fgetc(input);
			while (c != EOF && c != '\n')
				c = fgetc(input);
		} else if (strcmp(token, "/*") == 0) {
			while (strcmp(token, "*/") != 0)
				getNextToken(input, token);
		} else {
			if (isKeyword(token)) {
				printf("keyword:\t%s\n", token);
				if (strcmp(token, "int")== 0) {  // TODO: Add more types	
					getNextToken(input, token);
					while (strcmp(token, ";") != 0 && strcmp(token, "(") != 0 && strcmp(token, "=") != 0) {
						if (strcmp(token, ",") != 0) {
							addId(token);
							printf("identifier:\t%s\n", token);	
						}
						getNextToken(input, token);			
					}
				}
			} else if (isId(token)) {
				printf("identifier:\t%s\n", token);	
			} else if (isOperator(token[0])){
				printf("operator:\t%s\n", token);	
			} else if (strcmp(token, "\"") == 0 || (token[0] >= '0' && token[0] <= '9')) {
				if ((token[0] >= '0' && token[0] <= '9')) {
					printf("literal:\t%s\n", token);
				} else {
					printf("literal:\t%s", token);
					getNextToken(input, token);
					while (strcmp(token, "\"") != 0) {
						printf("%s ", token);
						getNextToken(input, token);
					}
					printf("%s\n", token);
				}
			} else {
				//printf("special:\t%s\n", token);	
			}
		}
	}
	
	fclose(input);
	return 0;
}

int isKeyword(char* str) {
	static char* keywords[KEYWORD_COUNT] = {"int", "char", "return", "if", "for", "while"};
	
	for (int i=0; i < KEYWORD_COUNT; i++) {
		if (strcmp(keywords[i], str) == 0) {
			return 1;
		}
	}
	return 0;
}

int getNextToken(FILE* file, char tok[]) {
	int size = 0;
	
	char c = fgetc(file);
	while (c != EOF) {
		if (size != 0) {
			if (isDelim(c)) {
				break;
			} else if (isOperator(c) || isSpecial(c)) {
				ungetc(c, file);
				break;
			}
		}
		if (!isDelim(c)) {		
			tok[size++] = c;
		}
		if (isOperator(c) || isSpecial(c)) {
			break;
		}
		c = fgetc(file);
	}
	tok[size] = '\0';
	
	if (c == EOF) return 0;
	return 1;
}

int isOperator(char c) {
	if (c == '+' || c == '-')  // TODO: Add all ops
		return 1;
	return 0;
}

int isSpecial(char c) {
	if (c == '(' || c == ')' || c == '"' || c == '#' || c == ';')  // TODO: Add everything
		return 1;
	return 0;
}

int isDelim(char c) {
	if (c == ' ' || c == '\t' || c == '\n' || c == '\r')
		return 1;
	return 0;
}

void addId(char* tok) {
	char* new_tok = (char*) malloc(64);
	strcpy(new_tok,tok);
	id[id_size++] = new_tok; 
}

int isId(char* tok) {	
	for (int i = 0; i < id_size; i++)
		if (strcmp(id[i], tok) == 0)
			return 1;
	return 0;
}
