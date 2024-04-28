#include <iostream>
#include <string>
using namespace std;

char NOT(char a) {
    if (a == 'T') {
        return 'F';
    } else {
        return 'T';
    }
}

char AND(char a, char b) {
    if (a == 'T' && b == 'T') {
        return 'T';
    }
    return 'F';
}

char OR(char a, char b) {
    if (a == 'T' || b == 'T') {
        return 'T';
    }
    return 'F';
}

char NAND(char a, char b) {
    if (a == 'T' && b == 'T') {
        return 'F';
    }
    return 'T';
}

char NOR(char a, char b) {
    if (a == 'F' && b == 'F') {
        return 'T';
    }
    return 'F';
}

string parse(string expr) {
    string newExpr;
    for (int i = 0; i < expr.length(); ++i) {
        switch (expr[i]) {
            case '&':
                newExpr[newExpr.length() - 1] = AND(newExpr[newExpr.length() - 1], expr[i + 1]);
                ++i;
                break;
            case '|':
                newExpr[newExpr.length() - 1] = OR(newExpr[newExpr.length() - 1], expr[i + 1]);
                ++i;
                break;
            case '!':
                newExpr += NOT(expr[i + 1]);
                ++i;
                break;
            case '@':
                newExpr[newExpr.length() - 1] = NAND(newExpr[newExpr.length() - 1], expr[i + 1]);
                ++i;
                break;
            case '$':
                newExpr[newExpr.length() - 1] = NOR(newExpr[newExpr.length() - 1], expr[i + 1]);
                ++i;
                break;
            case '(':
            {
                    int j = expr.find(')', i);
                    if (j == string::npos) {
                        cerr << "Error: Missing closing parenthesis.\n";
                        return ""; // Return empty string to indicate failure
                    }
                    // Extract the substring within parentheses and parse it recursively
                    string subExpr = expr.substr(i + 1, j - i - 1);
                    string parsedSubExpr = parse(subExpr);
                    newExpr += parsedSubExpr;
                    i = j; // Update index to skip the processed substring
                    break;
            }
            case ')':
                cerr << "Error: Missing opening parenthesis.\n";
                return "";
            default:
                newExpr += expr[i];
        }
    }
    return newExpr;
}

int main() {
    string expr;
    cout << "Type the expression:\n";
    cin >> expr;
    string ans = parse(expr);
    cout << "The expression is\n";
    cout << ans;
    return 0;
}