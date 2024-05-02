#include <iostream>
#include <string>
#include <unordered_set>
using namespace std;

unordered_set<char> INNER_OPERATIONS =  {'&', '|', '@', '$'};
unordered_set<char> OUTER_OPERATIONS = {'!', '(', ')'};
unordered_set<char> TRUTH_VALUES = {'T', 'F'};

bool is_inner_operation(char a) {
    return (INNER_OPERATIONS.find(a) != INNER_OPERATIONS.end());
}

bool is_outer_operation(char a) {
    return (OUTER_OPERATIONS.find(a) != OUTER_OPERATIONS.end());
}

bool is_truth_value(char a) {
    return (TRUTH_VALUES.find(a) != TRUTH_VALUES.end());
}

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

bool chars_are_valid(string expr) {
    for (int i = 0; i < expr.length(); ++i) {
        bool is_valid_char = (is_inner_operation(expr[i]) || is_outer_operation(expr[i]) || is_truth_value(expr[i]));
        if (!is_valid_char) {
            cout << "Invalid character at i = " << i << "\n";
            return false;
        }
    }
    cout << "Expression contains valid characters.\n";
    return true;
}

bool parens_are_valid(string expr) {
    int open_count = 0;
    int close_count = 0;
    for (int i = 0; i < expr.length(); ++i) {
        if (expr[i] == '(') {
            open_count++;
        }
        if (expr[i] == ')') {
            close_count++;
        }
        if (close_count > open_count) {
            cout << "Invalid. Extraneous ')' at i = " << i << "\n";
            return false;
        }
    }
    if (close_count != open_count) {
        cout << "Invalid. Expression missing ')'\n";
        return false;
    }
    cout << "Expression contains valid parentheses.\n";
    return true;
}

bool sequence_is_valid(string expr) {
    for (int i = 0; i < expr.length(); ++i) {
        bool is_outer_char = (i == 0 || i == expr.length() - 1 //first or last
            || expr[i - 1] == '(' || expr[i + 1] == ')' //after '(' or before ')'
            || expr[i - 1] == '!') ; //after '!'
        if ((is_outer_char && is_inner_operation(expr[i]))) {
            cout << "Invalid. Outer character is inner operation at i = " << i << "\n";
            return false;
        }
        else if (is_truth_value(expr[i]) &&  is_truth_value(expr[i + 1])) {
            cout << "Invalid. Adjacent truth values at i = " << i << " and i = " << i + 1 << "\n";
            return false;
        }
        else if (is_inner_operation(expr[i]) && is_inner_operation(expr[i + 1])) {
            cout << "Invalid. Adjacent inner operations at i = " << i << " and i = " << i + 1 << "\n";
            return false;
        }
        else if (i == expr.length() - 1 && expr[i] == '!') {
            cout << "Invalid. Expression cannot end in '!'\n";
            return false;
        }
        else if (expr[i] == '(' && expr[i + 1] == ')') {
            cout << "Invalid. Parentheses set must contain a value.\n";
            return false;
        }
        else if (expr[i] == ')' && expr[i + 1] == '(') {
            cout << "Invalid. Missing operator between i = " << i << " and i = " << i + 1 << "\n";
            return false;
        }
    }
    cout << "Expression sequence is valid.\n";
    return true;
}

bool expression_is_valid(string expr) {
    if (chars_are_valid(expr) && parens_are_valid(expr) && sequence_is_valid(expr)) {
        cout << "Expression is valid.\n";
        return true;
    }
    else {
        cout << "Invalid expression.\n";
        return false;
    }
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