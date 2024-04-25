#include <iostream>
#include <string>
using namespace std;

char NOT (char a) {
    if (a == 'T') {
        return 'F';
    }
    else {
        return 'T';
    }
}

char AND (char a, char b) {
    if (a == 'T' && b == 'T') {
        return 'T';
    }
    return 'F';
}

char OR (char a, char b) {
    if (a == 'T' | b == 'T') {
        return 'T';
    }
    return 'F';
}

char NAND (char a, char b) {
    if (a == 'T' && b == 'T') {
        return 'F';
    }
    return 'T';
}

char NOR (char a, char b) {
    if (a == 'T' | b == 'T') {
        return 'F';
    }
    return 'T';
}

bool XOR (bool a, bool b) {
    return a ^ b;
}

void main () {
    string expr;
    cout << "Type the expression:\n";
    cin >> expr;
    string ans = parse(expr);
    cout << "The expression is ", ans;
}

string parse (string expr) {
    string newExpr;
    int length = expr.length() - 1;
    for (int i = 0; i < length; i++) {
        switch(expr[i]) {
            case '&':
                newExpr[-1] = AND(newExpr[-1], expr[i+1]);
                i++;
                break;
            case '|':
                newExpr[-1] = OR(newExpr[-1], expr[i+1]);
                i++;
                break;
            case '!':
                newExpr += NOT(expr[i+1]);
                i++;
                break;
            case '@':
                newExpr[-1] = NAND(newExpr[-1], expr[i+1]);
                i++;
                break;
            case '$':
                newExpr[-1] = NOR(newExpr[-1], expr[i+1]);
                i++;
                break;
            default:
                newExpr += expr[i];
        }
    }
}