#include <iostream>
#include <string>
#include <unordered_set>
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

int check_if_symbols_adjacent_to_operation_are_valid(string expr, int i) {
  if ((expr[i - 1] == 'T' || expr[i - 1] == 'F' || expr[i - 1] == ')') && (expr[i + 1] == 'T' || expr[i + 1] == 'F' || expr[i + 1] == '(')){
    return 1;
  } else {
    return 0;
  }
}


string parse(string expr) {
    cout << "Parsing: " << expr << "\n";
    string newExpr;
    unordered_set<char> operations =  {'&', '|', '!', '@', '$'};
    for (int i = 0; i < expr.length(); ++i) {
        cout << "Parsing: " << expr << "\n";
        if (operations.find(expr[i]) != operations.end()) {
          if (!check_if_symbols_adjacent_to_operation_are_valid(expr, i)) {
            cout << "The expression is " << expr << "\n";
            cerr << "Error: Invalid symbols adjacent to operation.\n";
            return "";
          }
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
          }
        }
        else {
          switch (expr[i]) {
            case '(':
            {
                // print ("Found opening parenthesis at index: " + str(i))
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
    }
    return newExpr;
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
int main() {
    string expr;
    cout << "Type the expression:\n";
    std::getline(std::cin, expr);
    expr = remove_spaces(expr);
    string ans = parse(expr);
    if (ans == "") {
        return 1;
    }
    cout << "The expression is\n";
    cout << ans << "\n";
    return 0;
}