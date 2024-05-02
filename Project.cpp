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

int check_symbols(string expr, int i) {
  if ((expr[i - 1] == 'T' || expr[i - 1] == 'F' || expr[i - 1] == ')' || expr[i - 1] == '!') && (expr[i + 1] == 'T' || expr[i + 1] == 'F' || expr[i + 1] == '(' || expr[i + 1] == '!')){
    return 1;
  } else {
    return 0;
  }
}


string parse(string expr) {
    string newExpr;
    unordered_set<char> operations =  {'&', '|', '!', '@', '$'};
    for (int i = 0; i < expr.length(); ++i) {
        if (operations.find(expr[i]) != operations.end()) {
          if (!check_symbols(expr, i)) {
            cout << "The expression is " << expr << "\n";
            cerr << "Error: Invalid symbols adjacent to operation.\n";
            return "";
          }
          switch (expr[i]) {
            case '&':
                newExpr[0] = AND(newExpr[newExpr.length() - 1], parse(expr.substr(i + 1, expr.length()-1))[0]);
                break;
            case '|':
                newExpr[0] = OR(newExpr[newExpr.length() - 1], parse(expr.substr(i + 1, expr.length()-1))[0]);
                break;
            case '!':
                newExpr += NOT(parse(expr.substr(i + 1, expr.length()-1))[0]);
                break;
            case '@':
                newExpr[0] = NAND(newExpr[newExpr.length() - 1], parse(expr.substr(i + 1, expr.length()-1))[0]);
                break;
            case '$':
                newExpr[0] = NOR(newExpr[newExpr.length() - 1], parse(expr.substr(i + 1, expr.length()-1))[0]);
                break;
          }
        }
        else {
            switch (expr[i]) {
                case '(':
                    {
                        int j = i + 1;
                        int level = 1;
                        while (j < expr.length() && level > 0) {
                            if (expr[j] == '(') {
                                level++;
                            } else if (expr[j] == ')') {
                                level--;
                            }
                            j++;
                        }
                        if (level > 0) {
                            cerr << "Error: Missing closing parenthesis." << endl;
                            return "";
                        }
                        string subExpr = expr.substr(i + 1, j - i - 2);
                        string parsedSubExpr = parse(subExpr);
                        newExpr += parsedSubExpr;
                        i = j - 1; // Update index to skip the processed substring
                        break;
                    }
                case ')':
                    cerr << "Error: Missing opening parenthesis." << endl;
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
    cout << ans[0] << "\n";
    return 0;
}