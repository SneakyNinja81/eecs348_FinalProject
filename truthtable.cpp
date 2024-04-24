#include <iostream>
#include <string>

using namespace std;

void truthTable (string expr) {
    int variables = 0;
    int length = expr.length() - 1;
    for (int i = 0; i < length; i++) {
        if (expr[i] != '&' | '|' | '!' | '@' | '$' | 'T' | 'F') {
            variables++;
        }
    }

    char answers[2*variables];
    for (int i = 0; i < 2*variables; i++) {
        answers[i] = 'F';
    }

    int index = 0;
    for (int i = 0; i < length; i++) {
        if (expr[i] != '&' | '|' | '!' | '@' | '$' | 'T' | 'F') {
            
            expr[i] = 'F';
            if (solve(expr) == TRUE) {
                answers[index] = 'T';
            }
            index++;
            
            expr[i] = 'T';
            if (solve(expr) == TRUE) {
                answers[index] = 'T';
            }
            index++;
        }
    }
    
}