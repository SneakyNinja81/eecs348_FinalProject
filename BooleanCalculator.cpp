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

char XOR(char a, char b) {
    if (a != b) {
        return 'T';
    }
    return 'F';
}

string remove_spaces(string expr) {
    string new_expr;
    // go through each character if it is not a space add it to the new string
    for (int i = 0; i < expr.length(); ++i) {
        if (expr[i] != ' ') {
            new_expr += expr[i];
        }
    }
    return new_expr;
}

bool chars_are_valid(string expr) {
    for (int i = 0; i < expr.length(); ++i) {
        bool is_valid_char = (is_inner_operation(expr[i]) || is_outer_operation(expr[i]) || is_truth_value(expr[i]));
        if (!is_valid_char) {
            cout << "Invalid character at i = " << i << "\n";
            return false;
        }
    }
    //cout << "Expression contains valid characters.\n";
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
            cout << "Extraneous ')' at i = " << i << "\n";
            return false;
        }
    }
    if (close_count != open_count) {
        cout << "Missing ')'\n";
        return false;
    }
    //cout << "Expression contains valid parentheses.\n";
    return true;
}

bool sequence_is_valid(string expr) {
    for (int i = 0; i < expr.length(); ++i) {
        bool is_outer_char = (i == 0 || i == expr.length() - 1 //first or last
            || expr[i - 1] == '(' || expr[i + 1] == ')' //after '(' or before ')'
            || expr[i - 1] == '!') ; //after '!'
        if ((is_outer_char && is_inner_operation(expr[i]))) {
            cout << "Outer character is inner operation at i = " << i << "\n";
            return false;
        }
        else if (is_truth_value(expr[i]) &&  is_truth_value(expr[i + 1])) {
            cout << "Adjacent truth values at i = " << i << " and i = " << i + 1 << "\n";
            return false;
        }
        else if (is_inner_operation(expr[i]) && is_inner_operation(expr[i + 1])) {
            cout << "Adjacent inner operations at i = " << i << " and i = " << i + 1 << "\n";
            return false;
        }
        else if (i == expr.length() - 1 && expr[i] == '!') {
            cout << "Expression cannot end in '!'\n";
            return false;
        }
        else if (expr[i] == '(' && expr[i + 1] == ')') {
            cout << "Parentheses set must contain a value.\n";
            return false;
        }
        else if (expr[i] == ')' && expr[i + 1] == '(') {
            cout << "Missing operator between i = " << i << " and i = " << i + 1 << "\n";
            return false;
        }
        else if (expr[i] == '!' && expr[i + 1] == '!') {
            cout << "Consecutive !s at i = " << i << " and i = " << i + 1 << "\n";
            return false;
        }
        else if (is_truth_value(expr[i]) && (expr[i - 1] == ')' || expr[i + 1] == '(')) {
            cout << "Truth value adjacent to outer parenthesis at i = " << i << "\n";
            return false;
        }
    }
    //cout << "Expression sequence is valid.\n";
    return true;
}

bool expression_is_valid(string expr) {
    if (chars_are_valid(expr) && parens_are_valid(expr) && sequence_is_valid(expr)) {
        cout << "Expression is valid.\n";
        return true;
    }
    else {
        //cout << "Invalid expression.\n";
        return false;
    }
}

string parse_nots(string expr) {
    string new_expr = "";
    for (int i = 0; i < expr.length(); ++i) {
        if (expr[i - 1] == '!') {
            if (expr[i] == 'T') {
                new_expr += 'F';
            }
            else if (expr[i] == 'F') {
                new_expr += 'T';
            }
        }
        else {
            new_expr += expr[i];
        }
    }
    string no_not_expr = "";
    for (int i = 0; i < new_expr.length(); ++i) {
        if (new_expr[i] != '!') {
            no_not_expr += new_expr[i];
        }
    }
    cout << "Parsing " << no_not_expr << "\n";
    return no_not_expr;
}

string parse_no_parens(string expr) {
    cout << "Parsing " << expr << "\n";
    string new_expr = expr;
    if (new_expr.find('!') != string::npos) {
        new_expr = parse_nots(new_expr);
    }
    if (new_expr.length() == 1) {
        return new_expr;
    }
    else {
        string leftmost_expr = "";
        switch (new_expr[1]) {
            case '&':
                leftmost_expr = AND(new_expr[0], new_expr[2]);
                break;
            case '|':
                leftmost_expr = OR(new_expr[0], new_expr[2]);
                break;
            case '@':
                leftmost_expr = NAND(new_expr[0], new_expr[2]);
                break;
            case '$':
                leftmost_expr = XOR(new_expr[0], new_expr[2]);
                break;
        }
        new_expr = leftmost_expr + new_expr.substr(3);
        return parse_no_parens(new_expr);
    }
}

string parse_parens(string expr, int index) {
    //cout << "Parsing " << expr << "\n";
    string new_expr = expr;
    int i_paren_right = 0;
    //cout << "i_paren_right set to 0: " << i_paren_right << "\n";
    for (int i = index; i < new_expr.length(); ++i) {
        if (new_expr[i] == ')') {
            i_paren_right = i;
            //cout << "i_paren_right set: " << i_paren_right << "\n";
            break;
        }
    }
    string paren_expr = new_expr.substr(index, i_paren_right - index);
    cout << "\nParentheses expression is " << paren_expr << "\n";
    string before_parens = new_expr.substr(0, index - 1);
    //cout << "Expression before is " << before_parens << "\n";
    string after_parens = new_expr.substr(i_paren_right + 1);
    //cout << "Expression after is " << after_parens << "\n";

    //cout << "2 Parsing " << paren_expr << "\n";
    paren_expr = parse_no_parens(paren_expr);
    new_expr = before_parens + paren_expr + after_parens;
    cout << "\nNew expression is " << new_expr << "\n";

    return new_expr;
}

string parse(string expr, int index) {
    string new_expr = expr;
    if (new_expr.find(')') != string::npos) {
        cout << "Parsing " << new_expr << "\n";
        int i_paren_left = 0;
        //cout << "i_paren_left set to 0: " << i_paren_left << "\n";
        for (int i = 0; i < new_expr.length(); ++i) {
            if (new_expr[i] == '(') {
                i_paren_left = i;
                //cout << "i_paren_left set: " << i_paren_left << "\n";
            }
            if (new_expr[i] == ')') {
                //cout << "i_paren_left passed to parse_parens: " << i_paren_left << "\n";
                new_expr = parse_parens(new_expr, i_paren_left + 1);
                break;
            }
        }
    }
    else {
        new_expr = parse_no_parens(new_expr);
    }
    if (new_expr.length() != 1) {
        //cout << "Recursing with expression: " << new_expr << "\n";
        new_expr = parse(new_expr, 0);
    }

    return new_expr;
}


int main() {
    string expr;
    while (true) {
        cout << "Type a Boolean expression with the following characters:\nTruth values: T, F\nOperators: !, &, |, @, $\nGrouping: (, )\n";
        cout << "Or type X to exit\n\n";
        std::getline(std::cin, expr);
        cout << "\n";
        expr = remove_spaces(expr);
        if (expr == "X") {
            cout << "Exiting...\n\n";
            return 0;
        }
        if (expression_is_valid(expr)) {
        string result = parse(expr, 0);
        cout << "\nResult: " << result << "\n\n\n";
        }
        else {
            cerr << "Expression is invalid.\n\n\n";
        }
    }
}