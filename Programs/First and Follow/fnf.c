#include <stdio.h>

// C program to find first and follow sets of a grammar

typedef struct production {
    char lhs;
    char rhs[10];
} Production;

typedef struct NonTerminal {
    char nonTerminal;
    int first[255];
    int follow[255];
} NonTerminal;

int isNonTerminal(char c);
int find(char c, NonTerminal arr[], int n);
void findFirst(char c, Production prods[], int n, int first[]);
void findFollow(char c, Production prods[], int n, int follow[]);
void display(int arr[], int n);

int main() {
    int n;
    printf("Enter the number of productions: ");
    scanf("%d", &n);

    Production prods[n];
    printf("Enter the productions: (Enter as A -> aBc)\n");
    for (int i = 0; i < n; i++) {
        scanf(" %c -> %s", &prods[i].lhs, prods[i].rhs);
    }
    
    NonTerminal nonTerminals[10];
    int nonTerminalCount = 0;
    for (int i = 0; i < n; i++) {
        if (!find(prods[i].lhs, nonTerminals, nonTerminalCount)) {
            nonTerminals[nonTerminalCount].nonTerminal = prods[i].lhs;
            nonTerminalCount++;
        }
        for (int j = 0; prods[i].rhs[j] != '\0'; j++) {
            if (isNonTerminal(prods[i].rhs[j]) && !find(prods[i].rhs[j], nonTerminals, nonTerminalCount)) {
                nonTerminals[nonTerminalCount].nonTerminal = prods[i].rhs[j];
                nonTerminalCount++;
            }
        }
    }

    for (int i = 0; i < nonTerminalCount; i++) {
        printf("First of %c: ", nonTerminals[i].nonTerminal);
        findFirst(nonTerminals[i].nonTerminal, prods, n, nonTerminals[i].first);
        display(nonTerminals[i].first, 255);
    }
    
    for (int i = 0; i < nonTerminalCount; i++) {
        printf("Follow of %c: ", nonTerminals[i].nonTerminal);
        if (i == 0) {
            nonTerminals[i].follow[(int)'$'] = 1;
        }
        findFollow(nonTerminals[i].nonTerminal, prods, n, nonTerminals[i].follow);
        display(nonTerminals[i].follow, 255);
    }
    return 0;
}

int isNonTerminal(char c) {
    return c >= 'A' && c <= 'Z';
}

int find(char c, NonTerminal arr[], int n) {
    for (int i = 0; i < n; i++) {
        if (arr[i].nonTerminal == c) {
            return 1;
        }
    }
    return 0;
}

void findFirst(char c, Production prods[], int n, int first[]) {
    for (int i = 0; i < n; i++) {
        if (prods[i].lhs == c) {
            if (!isNonTerminal(prods[i].rhs[0])) {
                first[(int)prods[i].rhs[0]] = 1;
            } else {
                if (isNonTerminal(prods[i].rhs[0]) && prods[i].rhs[0] != c) {
                    findFirst(prods[i].rhs[0], prods, n, first);
                }
            }
        }
    }
}

void findFollow(char c, Production prods[], int n, int follow[]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; prods[i].rhs[j] != '\0'; j++) {
            if (prods[i].rhs[j] == c) {
                if (prods[i].rhs[j+1] == '\0') {
                    if (prods[i].lhs == prods[0].lhs) {
                        follow[(int)'$'] = 1;                        
                    }
                    findFollow(prods[i].lhs, prods, n, follow);
                } else {
                    if (!isNonTerminal(prods[i].rhs[j+1])) {
                        follow[(int)prods[i].rhs[j+1]] = 1;
                    } else {
                        findFirst(prods[i].rhs[j+1], prods, n, follow);
                    }
                }
            }
        }
    }
}

void display(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        if (arr[i] != 0) {
            printf("%c ", i);
        }
    }
    printf("\n");
}