#include <Project.h>
#include <iostream>
#include <string>
#include <math.h>

using namespace std;

void printTable (bool answers[], char vars[]) {
    int variables = sizeof(vars);
    int length = sizeof(answers);
    //Prints a line of all the variables
    for (int i = 0; i < variables; i++) {
        cout << vars[i], "\t";
    }
    // Prints out all the answers
    for (int i = 0; i < length; i++) {
        // Not needed, just for formatting
        if (i%variables == 0) {
            cout << "\n";
        }
        cout << answers[i];
    }
}

void truthTable (string expr) {
    // Finds how many variables there are
    int variables = 0;
    int length = expr.length() - 1;
    for (int i = 0; i < length; i++) {
        if (expr[i] != '&' | '|' | '!' | '@' | '$' | 'T' | 'F') {
            variables++;
        }
    }
    // Initializes array of answers for truth table output
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