#include <iostream>
#include <string>
#include <unordered_set>
using namespace std;

unordered_set<char> INNER_OPERATIONS =  {'&', '|', '@', '$'};
unordered_set<char> OUTER_OPERATIONS = {'!', '(', ')'};
unordered_set<char> VALUES = {'T', 'F'};

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

string remove_spaces(string expr) {
    string newExpr;
    // go through each character if it is not a space add it to the new string
    for (int i = 0; i < expr.length(); ++i) {
        if (expr[i] != ' ') {
            newExpr += expr[i];
        }
    }
    return newExpr;
}

bool expression_is_valid(string expr) {
    for (int i = 0; i < expr.length(); ++i) {
        bool is_valid_char = ((INNER_OPERATIONS.find(expr[i]) != INNER_OPERATIONS.end()) 
        || (OUTER_OPERATIONS.find(expr[i]) != OUTER_OPERATIONS.end()) 
        || (VALUES.find(expr[i]) != VALUES.end()));
        if (!is_valid_char) {
            cout << "Invalid character at i = " << i << "\n";
            return false;
        }
    }
    cout << "Expression is valid.\n";
    return true;
}

char parse(string expr) {
    cout << "Beginning expression parse.\n";
    return 'T'; //temporary
}

int main() {
    string expr;
    cout << "Type the expression:\n";
    std::getline(std::cin, expr);
    expr = remove_spaces(expr);
    if (expression_is_valid(expr)) {
        /*
        string ans = parse(expr);
        if (ans == "") {
            return 1;
        }
        cout << "The expression is\n";
        cout << ans[0] << "\n";
        return 0;
        */
       char result = parse(expr);
       cout << "Result: " << result << "\n";
       return 0;
    }
    else {
        cout << "Expression is invalid.\n";
        return 1;
    }
}