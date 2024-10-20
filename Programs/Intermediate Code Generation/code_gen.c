#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int i=1, j=0, no=0, tmpch=90;
char str[100], left[15], right[15];

void findopr();
void explore();
void fleft(int);
void fright(int);

struct exp {
    int pos;
    char op;
    int isUnary;
} k[15];

int main() {
    printf("Enter the Expression : ");
    scanf("%s", str);
    printf("The intermediate code:\n");
    findopr();
    explore();
}

void findopr() {
    for (i = 0; str[i] != '\0'; i++) {
        if (str[i] == '(' || str[i] == ')') {
            k[j].pos = i;
            k[j].isUnary=0;
            k[j++].op = str[i];
        }
    }

    for (i = 0; str[i] != '\0'; i++) {
        if (str[i] == '-' && (i == 0 || (str[i-1] == '(' || str[i-1] == '+' || str[i-1] == '-' || str[i-1] == '*' || str[i-1] == '/'))) {
            k[j].pos = i;
            k[j].isUnary=1;
            k[j++].op = '-';
        }
    }
    
    for (i = 0; str[i] != '\0'; i++) {
        if (str[i] == '/' || str[i] == '*') {
            k[j].pos = i;
            k[j].isUnary=0;
            k[j++].op = str[i];
        }
    }
    
    for (i = 0; str[i] != '\0'; i++) {
        if (str[i] == '+') {
            k[j].pos = i;
            k[j].isUnary=0;
            k[j++].op = '+';
        }
    }
    
    for (i = 0; str[i] != '\0'; i++) {
        if (str[i] == '-') {
            if (i == 0 || (str[i-1] == '(' || str[i-1] == '+' || str[i-1] == '-' || str[i-1] == '*' || str[i-1] == '/')) {
                // Unary minus detected (after '(', '+', '-', '*', or '/')
                continue;
            }
            k[j].pos = i;
            k[j].isUnary=0;
            k[j++].op = '-';
        }
    }
}

void explore() {
    i = 0;
    while (k[i].op != '\0') {
        if (k[i].op == '(' || k[i].op == ')') {
            // Skip parentheses
            i++;
            continue;
        }
        if (k[i].isUnary) {
            fright(k[i].pos);
            str[k[i].pos] = tmpch--;
            printf("\t%c := %c %s\t\t", str[k[i].pos], k[i].op, right);
        }
        else{
            fleft(k[i].pos);
            fright(k[i].pos);
            str[k[i].pos] = tmpch--; // Replace the operator with temporary variable
            
            // Print intermediate code
            printf("\t%c := %s %c %s\t\t", str[k[i].pos], left, k[i].op, right);
        }
        printf("\n");
        i++;
    }
    
    fright(-1);
}

void fleft(int x) {
    int w = 0, flag = 0;
    x--;

    while (x != -1 && str[x] != '+' && str[x] != '*' && str[x] != '=' && str[x] != '\0' && str[x] != '-' && str[x] != '/' && str[x] != ':') {
        if (str[x] != '$' && flag == 0) {
            left[w++] = str[x];
            left[w] = '\0';
            str[x] = '$'; // Mark the operand as processed
            flag = 1;
        }
        x--;
    }
}

void fright(int x) {
    int w = 0, flag = 0;
    x++;
    
    while (x != -1 && str[x] != '+' && str[x] != '*' && str[x] != '\0' && str[x] != '=' && str[x] != '-' && str[x] != '/' && str[x] != ':') {
        if (str[x] != '$' && flag == 0) {
            right[w++] = str[x];
            right[w] = '\0';
            str[x] = '$'; // Mark the operand as processed
            flag = 1;
        }
        x++;
    }
}
